import numpy as np
from tensor import *
from layers import *
from sgd import *
np.random.seed(0)

x = Tensor([
    [0,0,0,0], # 0
    [0,0,0,1], # 1
    [0,0,1,0], # 2
    [0,0,1,1], # 3
    [0,1,0,0], # 4
    [0,1,0,1], # 5
    [0,1,1,0], # 6
    [0,1,1,1], # 7
    [1,0,0,0], # 8
    [1,0,0,1]  # 9
], autograd=True)


y = Tensor([
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
], autograd=True)

model = Sequential([Linear(4,15), Sigmoid(), Linear(15,10), Softmax()])
sgd = SGD(model.get_params(), 0.01)
loss = MSELoss()
epochs = 1000

for epoch in range(epochs):
    predictions = model.forward(x)
    error = loss.forward(predictions, y)
    error.backward(Tensor(np.ones_like(error.data)))
    sgd.step()

    if epoch % 1000 == 0:
        print(f"Epoch: {epoch}, Error: {error}")


def predict(inp):
    output_layer = model.forward(inp)
    return np.argmax(output_layer.data)

for inp in x.data:
    print("------------------------------------")
    print(f"Predicted digit {inp}:", predict(Tensor([inp])))
