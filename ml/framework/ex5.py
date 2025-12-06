import numpy as np
from layers import *
from tensor import *
from sgd import *
from nn_usage import *

np.random.seed(1)

train_inputs = Tensor([
    [150,40],
    [195,100],
    [155,45],
    [140,35], 
    [170,80],
], autograd=True)

train_labels = Tensor([
    [1,0],
    [0,1],
    [1,0],
    [1,0],
    [0,1],
],autograd=True)

test_inputs = Tensor([
    [196, 120],
    [140, 40],
    [180, 90],
    [120, 35],
], autograd=True)

test_labels = Tensor([
    [0, 1],
    [1, 0],
    [0, 1],
    [1, 0],
],autograd=True)

input_size = len(train_inputs.data[0])
hidden_size = 15
output_size = len(train_labels.data[0])

train_config = Config(
        Sequential([
            Linear(input_size, hidden_size), 
            Relu(), 
            Linear(hidden_size, output_size), 
            Softmax()
        ]),
        MSELoss(),
        [train_inputs, train_labels],
        [10, 1e-4]
)

test_config = train_config.__copy__()
test_config.inputs = test_inputs
test_config.outputs = test_labels

ERR_TARGET = 1e-3
DELTA_FLOOR = 1e-6
trainPlus(train_config, ERR_TARGET, DELTA_FLOOR)
test(test_config)
