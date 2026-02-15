import numpy as np
import torch as t
import torch.nn as nn


class InputData:
    def __init__(self, train, train_labels, test, test_labels):
        self.train = train
        self.train_labels = train_labels
        self.test = test
        self.test_labels = test_labels


class Config:
    def __init__(self, model, loss, optimizer, epochs, input_data):
        self.model = model
        self.loss = loss
        self.optimizer = optimizer
        self.epochs = epochs
        self.inp = input_data

def train(config) -> t.tensor:

    model = config.model
    optimizer = config.optimizer
    loss = config.loss
    train_data = config.inp.train
    train_labels = config.inp.train_labels
    epochs = config.epochs

    for epoch in range(int(epochs + 1)):
        optimizer.zero_grad()
        out = model(train_data)
        error = loss(out, train_labels)
        error.backward()
        optimizer.step()
        if (epoch % (epochs / 10) == 0):
            print(f"EPOCH: {epoch}\tERROR: {error.item():.4f}")

    return out


def compare_results(label, out) -> None:
    print(f">{58*'='}<")
    print("label\tout\tdelta")
    for i in range(len(label)):
        lbl_val = float(label[i].detach())
        out_val = float(out[i].detach())
        delta = abs(lbl_val - out_val)
        print(f"{lbl_val:.3f}\t{out_val:.3f}\t{delta:.3f}")
    print(f">{58*'='}<\n\n")
