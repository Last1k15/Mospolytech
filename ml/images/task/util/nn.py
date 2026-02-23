import torch as t

############################## EXTERN ##############################
class InputData:
    def __init__(self, train, train_labels, test, test_labels):
        self.train = train
        self.train_labels = train_labels
        self.test = test
        self.test_labels = test_labels


class Config:
    def __init__(self, model, loss, optimizer, epochs, inp, batch_size, model_output_name):
        self.model = model
        self.loss = loss
        self.optimizer = optimizer
        self.epochs = epochs
        self.inp = inp
        self.batch_size = batch_size
        self.model_output_name = model_output_name


def train(config):

    model = config.model
    optimizer = config.optimizer
    loss = config.loss
    train_data = config.inp.train
    train_labels = config.inp.train_labels
    epochs = config.epochs
    batch_size = config.batch_size
    model_output_name = config.model_output_name

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
            error = loss(out_batch, train_labels_batch)
            error.backward()
            optimizer.step()
            out_list.append(out_batch)

        out = t.max(t.cat(out_list, dim=0), 1)[1]
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


############################## STATIC ##############################
def get_accuracy(out, label) -> float:
    total_guess = 0
    for i in range(len(label)):
        total_guess += (out[i] == label[i])
    total_guess = total_guess / len(label)
    return (total_guess * 100)


