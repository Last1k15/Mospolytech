import numpy as np

def neural_networks(inp, weights):
    return inp * weights

def get_error(true_prediction, prediction):
    return (true_prediction - prediction) ** 2

def do_magic(inp, weights, true_prediction, learning_rate, iter_n):

    shrinkPrint = iter_n > 50
    shrinkStep = iter_n / 10
    shrinkCounter = 0

    for i in range(ITER_N):

        prediction = neural_networks(inp, weights)
        if any(prediction) > 1e10:
            raise ArithmeticError("To infinity and beyond!")

        error = get_error(true_prediction, prediction)

        if not shrinkPrint or (shrinkPrint and shrinkCounter % shrinkStep) == 0:
            print("i: %s, Prediction: %s, Weights: %s, Error: %s" %(i, prediction, weights, error))
        shrinkCounter += 1

        delta = (prediction - true_prediction) * inp * learning_rate
        weights = weights - delta
    print("\n")

INP = 150
WEIGHTS = np.array([0.2, 0.3])
TRUE_PREDICTIONS = np.array([50, 120])
LEARNING_RATE = 0.00001
ITER_N = 70

print("INP DIFF")
try:
    print(f"\n{INP = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, ITER_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

try:
    INP = 200
    print(f"\n{INP = }")
    do_magic(INP, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, ITER_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass
