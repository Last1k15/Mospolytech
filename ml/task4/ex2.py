import numpy as np

def neural_networks(inp, weights):
    return inp.dot(weights)

def get_error(true_prediction, prediction):
    return (true_prediction - prediction) ** 2

def do_magic(inp, weights, true_prediction, learning_rate, iter_n):
    shrinkPrint = iter_n > 100
    shrinkStep = iter_n / 10
    shrinkCounter = 0
    for i in range(iter_n + 1):
        prediction = neural_networks(inp, weights)

        if (prediction > 1e10):
            raise ArithmeticError("To infinity and beyond!")

        error = get_error(true_prediction, prediction)
        
        if not shrinkPrint or (shrinkPrint and shrinkCounter % shrinkStep) == 0:
            print("i: %s, Prediction: %s, Weights: %s, Error: %s" %(i, prediction, weights, error))
        shrinkCounter += 1

        delta = (prediction - true_prediction) * inp * learning_rate
        weights -= delta
    print('\n')

INP = np.array([150, 40])
WEIGHTS = np.array([0.2, 0.3])
TRUE_PREDICTION = 1
LEARNING_RATE = 0.00001
ITER_N = 10

print("LEARNING_RATE DIFF")
try:
    print(f"{LEARNING_RATE = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTION, LEARNING_RATE, ITER_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

try:
    LEARNING_RATE = 0.0001
    print(f"{LEARNING_RATE = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTION, LEARNING_RATE, ITER_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

try:
    LEARNING_RATE = 0.001
    print(f"{LEARNING_RATE = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTION, LEARNING_RATE, ITER_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

INP = np.array([150, 40])
WEIGHTS = np.array([0.2, 0.3])
TRUE_PREDICTION = 1
LEARNING_RATE = 0.00001
ITER_N = 10

print("ITER_N DIFF")
try:
    print(f"{ITER_N = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTION, LEARNING_RATE, ITER_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

try:
    ITER_N = 1000
    print(f"{ITER_N = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTION, LEARNING_RATE, ITER_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass
