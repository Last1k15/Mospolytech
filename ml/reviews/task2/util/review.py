import re
import torch as t
import numpy as np 
import pandas as pd
from .nn import InputData, Config
from collections import Counter
from dataclasses import dataclass
from torch.utils.data import TensorDataset, DataLoader

@dataclass
class ReviewConfig():
    filepath : str
    seq_len : int
    train_n : int
    test_n : int
    check_n : int
    train_len : int
    test_len : int
    common_bs : int

@dataclass
class MyInputData(InputData):
    check : Config
    vocabulary_size : int


def formatReview(raw):
    reviews = re.sub(r"[\'\[]", r'', "".join(raw)).split("]")[:-1]
    reviews = [review.split(", ") for review in reviews]
    return reviews


def get_review_data(rc : ReviewConfig) -> InputData:

    def makeWritable(*args):
        for arg in args:
            arg.setflags(write=1)

    def getLoaderData(iter, N):
        images = []
        labels = []
        for i in range(N):
            image_batch, label_batch = next(iter)
            images.append(image_batch)
            labels.append(label_batch)
        images = t.cat(images, dim=0).to(dtype=t.float64)
        labels = t.cat(labels, dim=0).to(dtype=t.float64)
        return images, labels


    data = pd.read_csv(rc.filepath)
    reviews = formatReview(data.review.values)
    labels = data.label.to_numpy()

    all_words = [word for review in reviews for word in review]
    counter = Counter(all_words)
    vocabulary = sorted(counter, key=counter.get, reverse=True)

    int2word = dict(enumerate(vocabulary, 1))
    int2word[0] = "PAD"
    word2int = {word : id for id, word in int2word.items()}

    reviews_enc = [[word2int[word] for word in review] for review in reviews]

    reviews_padding = np.full((len(reviews_enc), rc.seq_len), word2int['PAD'], dtype=int)
    for i, row in enumerate(reviews_enc):
        reviews_padding[i, :len(row)] = np.array(row)[:rc.seq_len]

    train_last_index = int(len(reviews_padding) * rc.train_len)
    train_x, remainder_x = reviews_padding[:train_last_index], reviews_padding[train_last_index:]
    train_y, remainder_y = labels[:train_last_index], labels[train_last_index:]
    test_last_index = int(len(remainder_x) * rc.test_len)

    test_x = remainder_x[:test_last_index]
    test_y = remainder_y[:test_last_index]

    check_x = remainder_x[test_last_index:]
    check_y = remainder_y[test_last_index:]

    makeWritable(
            train_x,
            train_y,
            test_x,
            test_y,
            check_x,
            check_y
    )

    train_dataset = TensorDataset(t.from_numpy(train_x), t.from_numpy(train_y))
    test_dataset = TensorDataset(t.from_numpy(test_x), t.from_numpy(test_y))
    check_dataset = TensorDataset(t.from_numpy(check_x), t.from_numpy(check_y))

    train_loader = DataLoader(train_dataset, shuffle=True, batch_size=rc.common_bs)
    test_loader = DataLoader(test_dataset, shuffle=True, batch_size=rc.common_bs)
    check_loader = DataLoader(check_dataset, shuffle=True, batch_size=rc.common_bs)

    train, train_labels = getLoaderData(iter(train_loader), rc.train_n)
    test, test_labels = getLoaderData(iter(test_loader), rc.test_n)
    check, check_labels = getLoaderData(iter(check_loader), rc.check_n)

    return MyInputData(
                Config(train, train_labels),
                Config(test, test_labels),
                Config(check, check_labels),
                len(word2int)
            )
