import numpy as np
from ex1_tensor import *
from ex1_layer import *
from ex1_SGD import *
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
])


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
epochs = 10000

for epoch in range(epochs):
    predictions = model.forward(x)
    error = loss.forward(predictions, y) # Using temp square sum leading to it's dealloc, leading to no creators
    error.backward(Tensor(np.ones_like(error.data))) # Due to sum's returned tensor having no creators match-case block is ignored, leading to missing grad update
    sgd.step()

    if epoch % 1000 == 0:
        print(f"Epoch: {epoch}, Error: {error}")


def predict(inp):
    output_layer = model.forward(inp)
    return np.argmax(output_layer.data)

for inp in x:
    print("------------------------------------")
    print(f"Предсказанная цифра для {inp}:", predict(Tensor([inp])))
