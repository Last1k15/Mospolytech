import numpy as np
np.random.seed(42)


def relu(x):
    for row in x:
        for col in range(len(row)):
            if row[col] < 0:
                row[col] = 0
    return x


def reluderiv(x): 
    return x > 0


def generate_weights(layer_in_size, layer_hid_size, layer_out_size):

    weights_hid = 2 * np.random.random((layer_in_size, layer_hid_size)) - 1
    weights_out = np.random.random((layer_hid_size, layer_out_size))

    weights = [weights_hid, weights_out]

    return weights


def do_magic(inp, weights, true_predictions, learning_rate, epoch_n, needPrint):

    weights_hid = weights[0].copy()
    weights_out = weights[1].copy()

    for epoch in range(epoch_n):
        layer_out_error = 0
        for current in range(len(inp)):

            layer_in = inp[current : (current+1)]
            layer_hid = relu(np.dot(layer_in, weights_hid))
            layer_out = relu(layer_hid.dot(weights_out))

            layer_true_prediction = true_predictions[current : (current+1)]
            layer_out_error += np.sum((layer_out - layer_true_prediction) ** 2) 

            layer_out_delta = (layer_true_prediction - layer_out)
            layer_hid_delta = layer_out_delta.dot(weights_out.T) * reluderiv(layer_hid)

            weights_out += learning_rate * layer_hid.T.dot(layer_out_delta)
            weights_hid += learning_rate * layer_in.T.dot(layer_hid_delta)

            if needPrint:
                print("Predictions: %s, True predictions: %s" %(layer_out, layer_true_prediction))

        if needPrint:
            print("Errors: %.4f" % layer_out_error)

    return np.mean(layer_out_error)


def find_best_hid_size(LAYER_HID_SIZE_LIMIT):

    best_error_median = 1e10
    best_layer_hid_size = 0

    for cur_layer_hid_size in range(1, LAYER_HID_SIZE_LIMIT):

        cur_weights = generate_weights(LAYER_IN_SIZE, cur_layer_hid_size, LAYER_OUT_SIZE)
        cur_error_median = do_magic(INP, cur_weights, TRUE_PREDICTIONS, LEARNING_RATE, EPOCH_N, False)

        if cur_error_median < best_error_median:
            best_error_median = cur_error_median
            best_layer_hid_size = cur_layer_hid_size
    return best_layer_hid_size


def check_diff_learning_rates(LEARNING_RATE_DIVIDER_POWER_LIMIT):
    for cur_learning_rate_divider_power in range(1, LEARNING_RATE_DIVIDER_POWER_LIMIT):
        cur_learning_rate = 1 / 10 ** cur_learning_rate_divider_power
        cur_error_median = do_magic(INP, WEIGHTS, TRUE_PREDICTIONS, cur_learning_rate, EPOCH_N, False)
        print(f"{cur_learning_rate = } ==> {cur_error_median = }")


def check_diff_epochs(EPOCH_N_LIMIT):
    EPOCH_N_START = int(EPOCH_N_LIMIT / 100)

    for cur_epoch_n in range(EPOCH_N_START, EPOCH_N_LIMIT, 100):

        cur_error_median = do_magic(INP, WEIGHTS,  TRUE_PREDICTIONS, LEARNING_RATE, cur_epoch_n, False)
        print(f"{cur_epoch_n = } ==> {cur_error_median = }")


INP = np.array([
[15, 10],
[15, 15],
[15, 20],
[25, 10]
])

TRUE_PREDICTIONS = np.array([[10, 20, 15, 20]]).T

LAYER_IN_SIZE = len(INP[0])
LAYER_HID_SIZE = 3
LAYER_OUT_SIZE = len(TRUE_PREDICTIONS[0])

WEIGHTS = generate_weights(LAYER_IN_SIZE, LAYER_HID_SIZE, LAYER_OUT_SIZE)

LEARNING_RATE = 1e-8
EPOCH_N = 1000

# find optimal layer_hid_size  
LAYER_HID_SIZE_LIMIT = 10
best_layer_hid_size = find_best_hid_size(LAYER_HID_SIZE_LIMIT)
optimized_weights = generate_weights(LAYER_IN_SIZE, best_layer_hid_size, LAYER_OUT_SIZE)
do_magic(INP, optimized_weights, TRUE_PREDICTIONS, LEARNING_RATE, EPOCH_N, True)
print(f"{best_layer_hid_size = }")

# check how changing learning_rate affects the result
LEARNING_RATE_DIVIDER_POWER_LIMIT = 7
check_diff_learning_rates(LEARNING_RATE_DIVIDER_POWER_LIMIT)

# check how changing epochs affects the result
EPOCH_N_LIMIT = 5000
check_diff_epochs(EPOCH_N_LIMIT)

