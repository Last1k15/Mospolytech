import numpy as np
import torch as t
import torch.nn as nn
from util import InputData

class MyModel(nn.Module):
    def __init__(self, input_size, hidden_size1, hidden_size2, hidden_size3, output_size):
        super().__init__()
        self.fc1 = nn.Linear(input_size, hidden_size1)
        self.fc2 = nn.Linear(hidden_size1, hidden_size2)
        self.fc3 = nn.Linear(hidden_size2, hidden_size3)
        self.fc4 = nn.Linear(hidden_size3, output_size)

        self.relu = nn.ReLU()
        self.sigmoid = nn.Sigmoid()

    def forward(self, x) -> t.tensor:
        out = self.fc1(x)
        out = self.relu(out)
        out = self.fc2(out)
        out = self.relu(out)
        out = self.fc3(out)
        out = self.relu(out)
        out = self.fc4(out)
        out = self.sigmoid(out)
        return out


class MyInputData(InputData):
    def __init__(self, train, test):
        super().__init__(
                train,
                t.tensor([max(d) > 7 for d in train], dtype=t.float32).unsqueeze(1),
                test,
                t.tensor([max(d) > 7 for d in test], dtype=t.float32).unsqueeze(1)
        )


