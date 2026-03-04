from dataclasses import dataclass
import torch as t
import torch.nn as nn

@dataclass
class Config:
    x : t.tensor
    y : t.tensor
    bs_n : int = 1
    bs : int = None

    def __post_init__(self):
        if self.bs is None:
            self.bs = len(self.x)


@dataclass
class InputData:
    train : Config
    test : Config
    

@dataclass
class MainConfig:
    model : any
    loss : any
    optimizer : any
    epochs : int
    data : Config
    output_name : str


def train(mc : MainConfig):

    def get_accuracy(out, label) -> float:
        total_guess = 0
        for i in range(len(label)):
            total_guess += (out[i] == label[i])
        total_guess = total_guess / len(label)
        return (total_guess * 100)


    model = mc.model
    optimizer = mc.optimizer
    loss = mc.loss
    train_data = mc.data.train.x
    train_labels = mc.data.train.y
    epochs = mc.epochs
    batch_size = mc.data.train.bs
    model_output_name = mc.output_name

    best_acc = 0
    out_list = []

    BATCH_N = int(len(train_data) / batch_size)

    for epoch in range(int(epochs + 1)):
        for batch in range(BATCH_N):
            s = batch * batch_size
            e = s + batch_size

            train_batch = train_data[s:e] 
            train_labels_batch = train_labels[s:e]

            optimizer.zero_grad()
            out_batch = model(train_batch)
            out_batch = out_batch.squeeze(1).to(dtype=t.float64)
            error = loss(out_batch, train_labels_batch)
            error.backward()
            optimizer.step()
            out_list.append(out_batch)

        out = t.cat(out_list, dim=0)
        out = t.tensor([1 if x >= 0.5 else 0 for x in out], dtype=t.float64)
        out_list.clear()

        acc = get_accuracy(out, train_labels)
        if (acc > best_acc):
            best_acc = acc
            t.save(model.state_dict(), model_output_name)

        if (epoch % (epochs / 10) == 0):
            print(f"EPOCH: {epoch}\tERROR: {error.item():.4f}\tACC: {best_acc:.2f}%")


def compare_results(out, label) -> None:
    print(f">{58*'='}<")
    print("label\tout\tguessed")

    total_guess = 0

    for i in range(len(label)):
        lbl_val = float(label[i].detach())
        out_val = float(out[i].detach())
        delta = abs(lbl_val - out_val)
        guessed = int(lbl_val) == int(out_val)
        total_guess += guessed
        print(f"{lbl_val:.3f}\t{out_val:.3f}\t{guessed}")

    total_guess = int(total_guess / len(label) * 100)
    print(f"\ntotal_guess: {total_guess}%")
    print(f">{58*'='}<\n\n")


