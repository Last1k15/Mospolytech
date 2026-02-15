############################## IMPORT ##############################
import numpy as np
import torch as t
import torch.nn as nn

from util import *
from spec import *

############################## CONFIG ##############################
INPUT_SIZE = 2
HIDDEN_SIZE = 200
OUTPUT_SIZE = 1
LEARNING_RATE = 1e-3
EPOCHS = 2e4

TRAIN_N = 100
TEST_N = 10

MODEL_OUTPUT_NAME = "mult_model.pth"


############################## SETUP ##############################
myModel = MyModel(
    INPUT_SIZE,
    HIDDEN_SIZE,
    OUTPUT_SIZE
)

config = Config(
    myModel,
    nn.MSELoss(),
    t.optim.SGD(myModel.parameters(), lr=LEARNING_RATE),
    EPOCHS,
    MyInputData(
        t.randint(0, 10, (TRAIN_N, INPUT_SIZE), dtype=t.float32),
        t.randint(0, 10, (TEST_N, INPUT_SIZE), dtype=t.float32),
    )
)


############################## TRAIN ##############################
train_results = train(config)
print("TRAIN RESULTS")
compare_results(config.inp.train_labels, train_results)


############################## TEST ##############################
test_results = config.model(config.inp.test)
print("TEST RESULTS")
compare_results(config.inp.test_labels, test_results)


############################## SAVE & LOAD ##############################
t.save(config.model.state_dict(), MODEL_OUTPUT_NAME)
config.model.load_state_dict(t.load(MODEL_OUTPUT_NAME))


############################## TEST2 ##############################
test_results_again = config.model(config.inp.test)
print("TEST RESULTS #2")
compare_results(config.inp.test_labels, test_results_again)

