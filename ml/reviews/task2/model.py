from dataclasses import dataclass
import torch as t
import torch.nn as nn
import torch.nn.functional as f
from util import InputData, Config


@dataclass
class ModelConfig:
    vocabulary_size : int
    embedding_size : int
    hidden_size : int
    lstm_layers : int
    lstm_dropout : int


class MyModel(nn.Module):
    def __init__(self, mc : ModelConfig):
        super().__init__()
        self.emb = nn.Embedding(mc.vocabulary_size, mc.embedding_size)
        self.lstm = nn.LSTM(
                input_size=mc.embedding_size,
                hidden_size=mc.hidden_size,
                num_layers=mc.lstm_layers,
                dropout=mc.lstm_dropout,
                batch_first=True
        )
        self.dropout = nn.Dropout(0.3)
        self.fc = nn.Linear(mc.hidden_size, 1)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x) -> t.tensor:
        out = x.long()
        out = self.emb(out)
        out = self.lstm(out)[0]
        out = out[:, -1, :]
        out = self.dropout(out)
        out = self.fc(out)
        out = self.sigmoid(out)
        return out
