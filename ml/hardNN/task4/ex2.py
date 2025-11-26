from keras.src.datasets import mnist
import numpy as np

np.random.seed(123)

TRAIN_IMAGES_COUNT = 1000
TEST_IMAGES_COUNT = 10000
PIXELS_PER_IMAGE = 28 * 28
DIGITS_NUM = 10
BATCH_SIZE = 50

HIDDEN_SIZE = 50
LEARNING_RATE = 0.01
EPOCH_N = 100


def relu(x):
    return np.maximum(0, x)


def reluderiv(x):
    return x > 0


def encode_labels(input_labels):
    encoded_labels = np.zeros((len(input_labels), DIGITS_NUM))
    for i,lbl in enumerate(input_labels):
        encoded_labels[i][lbl] = 1
    return encoded_labels


def do_magic(epoch_n, learning_rate, hidden_size):
    weight_hid = 0.2 * np.random.random((PIXELS_PER_IMAGE, hidden_size)) - 0.1
    weight_out = 0.2 * np.random.random((hidden_size, DIGITS_NUM)) - 0.1

    for e in range(1, epoch_n + 1):
        correct_answers = 0
        batch_n = int(len(train_images) / BATCH_SIZE)
        for batch_i in range(batch_n):
            batch_start = BATCH_SIZE * batch_i
            batch_end = BATCH_SIZE * (batch_i + 1)
            train_batch = train_images[batch_start : batch_end]

            layer_in = train_batch
            layer_hid = relu(np.dot(layer_in, weight_hid))
            dropout_mask = np.random.randint(2, size = layer_hid.shape)
            layer_hid *= dropout_mask * 2
            layer_out = np.dot(layer_hid, weight_out)

            for img in range(BATCH_SIZE):
                batch_labels = train_labels[batch_start + img : (batch_end + img + 1)]
                correct_answers += int(np.argmax(layer_out[img:img+1]) == np.argmax(batch_labels))

            layer_out_delta = (layer_out - train_labels[batch_start:batch_end])/BATCH_SIZE
            layer_hid_delta = layer_out_delta.dot(weight_out.T) * reluderiv(layer_hid) * dropout_mask

            weight_out -= layer_hid.T.dot(layer_out_delta) * learning_rate
            weight_hid -= layer_in.T.dot(layer_hid_delta) * learning_rate
        acc = (correct_answers * 100 / len(train_images))
        # if (e % (epoch_n / 5) == 0):
        #     print(f"epoch: {e}")
        #     print(f"accuracy: {acc:.2f}")
    return acc


def check_diff_learning_rate(LEARNING_RATE_LIMIT):
    print(f"\n>{'='*100}<\n")
    for lr_k in range(1, LEARNING_RATE_LIMIT):
        lr = 1 / 10 ** lr_k
        acc = do_magic(EPOCH_N, lr, HIDDEN_SIZE)
        print(f"{lr = }\t{acc = }")


def find_best_epoch_n(EPOCH_N_LIMIT):
    best_epoch_n = 0
    best_acc = 0
    print(f"\n>{'='*100}<\n")
    for epoch_n in range(100, EPOCH_N_LIMIT + 1, 100):
        acc = do_magic(epoch_n, LEARNING_RATE, HIDDEN_SIZE)
        print(f"{epoch_n = }\tacc = {acc}")
        if (acc > best_acc):
            best_acc = acc
            best_epoch_n = epoch_n
    print(f"{best_epoch_n = }\t{best_acc = }")


def find_best_hidden_size(HIDDEN_SIZE_LIMIT):
    best_hs = 0
    best_acc = 0
    for hs in range(10, HIDDEN_SIZE_LIMIT + 1, 10):
        acc = do_magic(EPOCH_N, LEARNING_RATE, hs)
        print(f"{hs = }\t{acc = }")
        if (acc > best_acc):
            best_acc = acc
            best_hs = hs
    print(f"{best_hs = }\t{best_acc = }")


(x_train, y_train), (x_test, y_test) = mnist.load_data()

train_images = x_train[0 : TRAIN_IMAGES_COUNT].reshape(TRAIN_IMAGES_COUNT, PIXELS_PER_IMAGE) / 255
train_labels = y_train[0 : TRAIN_IMAGES_COUNT]

test_images = x_test[0 : TEST_IMAGES_COUNT].reshape(TEST_IMAGES_COUNT, PIXELS_PER_IMAGE) / 255
test_labels = y_test[0 : TEST_IMAGES_COUNT]

test_labels = encode_labels(test_labels)
train_labels = encode_labels(train_labels)

# LEARNING_RATE_LIMIT = 8
# check_diff_learning_rate(LEARNING_RATE_LIMIT)

# EPOCH_N_LIMIT = 2000
# find_best_epoch_n(EPOCH_N_LIMIT)

# best_hs = 450 best_acc = 88.7
HIDDEN_SIZE_LIMIT = 50
find_best_hidden_size(HIDDEN_SIZE_LIMIT)
