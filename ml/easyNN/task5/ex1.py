import numpy as np

def neural_networks(inp, weights):
    return inp.dot(weights)

def get_error(true_prediction, prediction):
    return (prediction - true_prediction) ** 2

def get_error_RMSE(true_prediction, prediction):
    return np.sqrt(np.mean((true_prediction - prediction) ** 2))

def do_magic(inp, weights, true_predictions, learning_rate, epochs):
    shrinkPrint = epochs * len(inp) > 100
    shrinkStep = epochs * len(inp) / 10
    for epoch in range(epochs):
        error = 0
        delta = 0
        for current in range(len(inp)):
            current_inp = inp[current]
            true_prediction = true_predictions[current]

            prediction = neural_networks(current_inp, weights)
            if (prediction > 1e10):
                raise ArithmeticError("To infinity and beyond!")

            error += get_error_RMSE(true_prediction, prediction)

            curIter = epoch * len(inp) + current
            if not shrinkPrint or (shrinkPrint and curIter % shrinkStep == 0):
                print("Prediction: %.10f, True_prediction: %.10f, Weights: %s, Errors: %s" %(prediction, true_prediction, weights, error))

            delta += (prediction - true_prediction) * current_inp * learning_rate

        delta_median = delta / len(inp)
        weights -= delta_median
        if any(weights > 1) or any(weights < 0):
            raise ArithmeticError(f"Out of range weights ->{weights - delta_median}")

    print("-------------------")


INP = np.array([
[150, 40],
[140, 35],
[155, 45],
[185, 95],
[145, 40],
[195, 100],
[180, 95],
[170, 80],
[160, 90],
])

WEIGHTS = np.array([0.2,0.3])
TRUE_PREDICTIONS = np.array([0,0,0,100,0,100,100,100,100])
LEARNING_RATE = 1e-7
EPOCH_N = 50

print("LEARNING_RATE DIFF")

try:
    print(f"{LEARNING_RATE = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, EPOCH_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

try:
    LEARNING_RATE = 0.001
    print(f"{LEARNING_RATE = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, EPOCH_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

LEARNING_RATE = 0.00001
EPOCH_N = 50

print("EPOCH_N DIFF")
try:
    print(f"{EPOCH_N = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, EPOCH_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

try:
    EPOCH_N = 100
    print(f"{EPOCH_N = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, EPOCH_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

try:
    EPOCH_N = 10000
    print(f"{EPOCH_N = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, EPOCH_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass
