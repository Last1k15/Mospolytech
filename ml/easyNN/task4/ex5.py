import numpy as np

def neural_networks(inp, weights):
    return inp.dot(weights)

# def get_error(true_prediction, prediction):
#     return (true_prediction - prediction) ** 2;

def get_error(true_prediction, prediction):
    return np.sqrt(np.mean((true_prediction - prediction) ** 2))

def do_magic(inps, weights, true_predictions, learning_rate, iter_n):
    shrinkPrint = iter_n * len(inps) > 100
    shrinkStep = iter_n * len(inps) / 10
    for i in range(iter_n):
        error = 0
        for j in range(len(inps)):
            current = inps[j]
            true_prediction = true_predictions[j]

            prediction = neural_networks(current, weights)
            if prediction > 1e10:
                raise ArithmeticError("To infinity and beyond!")

            error += get_error(true_prediction, prediction)
            if not shrinkPrint or (shrinkPrint and (i*len(inps)+j) % shrinkStep == 0):
                print("%s: Prediction: %.10f, Weights: %s, true_prediction: %.10f, Errors: %.10f" % ((i*len(inps)+j),prediction, weights, true_prediction, error))
            delta = (prediction - true_prediction) * current * learning_rate
            weights = weights - delta
    print("------------------")

INPS = np.array([
    [150,40],
    [170,80],
    [160,90]
])

WEIGHTS = np.array([0.2, 0.3])
TRUE_PREDICTIONS = np.array([50, 120, 140]);
LEARNING_RATE = 0.00001
ITER_N = 700

print("EPOCH DIFF")

print(f"{ITER_N = }")
do_magic(INPS, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, ITER_N)

ITER_N = 100
print(f"{ITER_N = }")
do_magic(INPS, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, ITER_N)
