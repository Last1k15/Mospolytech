import numpy as np
from layers import *
from sgd import *

np.random.seed(0)

inp = Tensor([[2,3],[5,10]], autograd=True)
true_predictions = Tensor([[5],[15]], autograd=True)

model = Sequential([Linear(2, 2), Linear(2, 1)])
sgd = SGD(model.get_params(), 0.001)
num_epochs = 1000

loss = MSELoss()

for i in range(num_epochs):
    predictions = model.forward(inp)
    error = loss.forward(predictions, true_predictions)
    error.backward(Tensor(np.ones_like(error.data)))
    sgd.step()
    print("Error:", error)
print(model.forward(Tensor([[0,-3], [4,8]])))
