import torch as t
import torchvision as tv
import numpy as np
import matplotlib.pyplot as plt

from util import *
from model import *

############################## SETUP ##############################
reviewConfig = ReviewConfig(
    filepath="../reviews_preprocessed.csv",
    train_len=0.6,
    test_len=0.5,
    seq_len=256,
    common_bs=128,

    train_n=1,
    test_n=1,
    check_n=1,
)

data = get_review_data(reviewConfig)

modelConfig = ModelConfig(
    vocabulary_size=data.vocabulary_size,
    embedding_size=256,
    hidden_size=256,
    lstm_layers=4,
    lstm_dropout=0.25
)

model = MyModel(modelConfig)

mainConfig = MainConfig(
        model=model,
        loss=t.nn.BCELoss(),
        optimizer=t.optim.Adam(
            model.parameters(),
            lr=1e-3,
        ),
        epochs=10,
        data=data,
        output_name="myModel.pth",
)

############################## TRAIN-TEST-CHECK ##############################
train(mainConfig)

mainConfig.model.load_state_dict(t.load(mainConfig.output_name))

test_results = t.tensor([1 if x >= 0.5 else 0 for x in mainConfig.model(mainConfig.data.test.x)], dtype=t.float64)
compare_results(test_results, mainConfig.data.test.y)

check_results = t.tensor([1 if x >= 0.5 else 0 for x in mainConfig.model(mainConfig.data.check.x)], dtype=t.float64)
compare_results(check_results, mainConfig.data.check.y)
