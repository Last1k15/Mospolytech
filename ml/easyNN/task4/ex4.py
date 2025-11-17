import numpy as np

def neural_networks(inps, weigths):
    return inps.dot(weigths)

def get_error(true_prediction, prediction):
    return (true_prediction - prediction) ** 2

def do_magic(inps, weights, true_predictions, learning_rate, iter_n):
    shrinkPrint = iter_n * len(inps) > 100
    shrinkStep = iter_n * len(inps)  / 10
    for i in range(iter_n):
        prediction = neural_networks(inps, weights)

        if any(prediction) > 1e10:
            raise ArithmeticError("To infinity and beyond!")

        error = get_error(true_predictions, prediction)

        if not shrinkPrint or (shrinkPrint and i % shrinkStep == 0):
            print("%s: Prediction: %s, Weights: %s, Error: %s" %(i, prediction, weights, error))

        delta = (prediction - true_predictions) * inps * learning_rate
        weights = weights - delta

INPS = np.array([150, 40])
WEIGHTS = np.array([[0.2, 0.3],[0.5, 0.7]]).T
TRUE_PREDICTIONS = np.array([50, 120])
LEARNING_RATE = 0.00001
ITER_N = 70

print("TRUE_PREDICTION DIFF")

try:
    print(f"\n{TRUE_PREDICTIONS = }")
    do_magic(INPS, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, ITER_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass

try:
    TRUE_PREDICTIONS = np.array([70,90])
    print(f"\n{TRUE_PREDICTIONS = }")
    do_magic(INPS, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, ITER_N)
except ArithmeticError as e:
    print(f"{e}\n")
    pass
