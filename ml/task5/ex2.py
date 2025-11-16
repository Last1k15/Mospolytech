import numpy as np

def neural_networks(inps, weights):
    return inps.dot(weights)

def get_error(true_prediction, prediction):
    return (prediction - true_prediction) ** 2

def get_error_RMSE(true_prediction, prediction):
    return np.sqrt(np.mean((true_prediction - prediction) ** 2))

def do_magic(inp, weights, true_predictions, learning_rate, epochs, printTemporaries):

    shrinkPrint = epochs * len(inp) > 100
    shrinkStep = epochs * len(inp) / 10

    error = 0
    error_pack = np.array([])

    printThisTime = False

    for epoch in range(epochs):

        error = 0
        error_pack = np.array([])

        delta = 0
        printThisTime = not shrinkPrint or (shrinkPrint and epoch % shrinkStep == 0)

        for current in range(len(inp)):

            true_prediction = true_predictions[current]
            prediction = neural_networks(inp[current], weights)
            if (prediction > 1e10):
                raise ArithmeticError("To infinity and beyond!")

            error = get_error_RMSE(true_prediction, prediction)
            error_pack = np.append(error_pack, error)

            delta += (prediction - true_prediction) * inp[current] * learning_rate

            if printTemporaries and printThisTime:
                print(f"Prediction: {prediction}, true_prediction: {true_prediction}, Weights: {weights}, Error: {error}")

        delta_median = delta / len(inp)
        weights -= delta_median

    return error_pack 

INPS = np.array([
    [10,5],
    [0,-5],
    [2,6]
])
WEIGHTS = np.array([0.5, 0.3])
TRUE_PREDICTIONS = np.array([15,-5,8])
LEARNING_RATE = 1e-3
EPOCH_N = 1000


def find_Best(inp, weights, true_predictions, epoch_limit, learning_divider_limit):

    EPOCH_N_START = 50
    EPOCH_N_STEP = 50

    min_error_median = 1e10
    best_weights = np.array([])

    for cur_epoch_n in range(EPOCH_N_START, epoch_limit, EPOCH_N_STEP):
        for cur_learning_rate_divider in range(1, learning_divider_limit):
            
            cur_learning_rate = 1 / 10 ** cur_learning_rate_divider

            cur_error = np.array([])
            cur_weights = np.array(weights)

            try:
                result = do_magic(inp, cur_weights, true_predictions, cur_learning_rate, cur_epoch_n, False)
                cur_error = result
            except ArithmeticError as e:
                continue

            cur_error_median = np.mean(cur_error)
            if (cur_error_median < min_error_median):
                min_error_median = cur_error_median
                best_weights = cur_weights

    return best_weights

EPOCH_LIMIT = 500
LEARNING_DIVIDER_LIMIT = 6

stable_weights = find_Best(INPS, WEIGHTS, TRUE_PREDICTIONS, EPOCH_LIMIT, LEARNING_DIVIDER_LIMIT)
print(f"{stable_weights = }")
do_magic(INPS, WEIGHTS, TRUE_PREDICTIONS, LEARNING_RATE, EPOCH_N, True)

TEST_INP = np.array([[10,22], [1,-3]])
print(neural_networks(TEST_INP[0], stable_weights))
print(neural_networks(TEST_INP[1], stable_weights))
