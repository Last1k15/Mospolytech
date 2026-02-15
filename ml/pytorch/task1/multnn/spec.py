import numpy as np
import torch as t
import torch.nn as nn
from util import InputData

class MyModel(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super().__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        out = self.fc1(x)
        out = self.relu(out)
        out = self.fc2(out)
        return out

class MyInputData(InputData):
    def __init__(self, train_data, test_data):
        super().__init__(
            train_data,
            t.tensor([[d[0]*d[1]] for d in train_data]),
            test_data,
            t.tensor([[d[0]*d[1]] for d in test_data])
        )
