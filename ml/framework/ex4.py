import numpy as np
from tensor import *
from layers import *
from sgd import *
from nn_usage import *

np.random.seed(0)

train_inputs = Tensor([
    [1,2,3],
    [2,4,5],
    [4,3,3],
    [2,3,5], 
    [7,2,2],
], autograd=True)


train_labels = Tensor([
    [6],
    [40],
    [36],
    [30],
    [28],
], autograd=True)

test_inputs = Tensor([
    [3,4,5]
], autograd=True)

test_labels = Tensor([
    [60]
], autograd=True)

input_size = len(train_inputs.data[0])
hidden_size = 30
output_size = len(train_labels.data[0])

train_config = Config(
        Sequential([
            Linear(input_size, hidden_size),
            Relu(),
            Linear(hidden_size, output_size)
        ]),
        RMSELoss(),
        [train_inputs, train_labels],
        [3000, 1e-4]
)

test_config = train_config.__copy__()
test_config.inputs = test_inputs
test_config.outputs = test_labels

ERR_TARGET = 1e-3
EPOCH_CEIL = 6000
DELTA_FLOOR = 1e-6

trainPlus(train_config, ERR_TARGET, DELTA_FLOOR)
test(test_config)
