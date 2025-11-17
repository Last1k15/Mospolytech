from keras.src.datasets import mnist
import numpy as np

def relu(x):
    return (x > 0) * x 


def reluderiv(x):
    return x > 0


def generate_weights(PIXELS_PER_IMAGE, HIDDEN_SIZE, DIGITS_NUM):
    weight_hid = 0.2 * np.random.random((PIXELS_PER_IMAGE, HIDDEN_SIZE)) - 0.1
    weight_out = 0.2 * np.random.random((HIDDEN_SIZE, DIGITS_NUM)) - 0.1
    weights = [weight_hid, weight_out]
    return weights


def do_magic(train_images, train_labels, weights, learning_rate, epoch_n):

    weight_hid = weights[0].copy()
    weight_out = weights[1].copy()

    for i in range(EPOCH_N):
        correct_answers = 0
        for j in range(len(train_images)):
            layer_in = train_images[j : (j + 1)]
            layer_hid = relu(np.dot(layer_in, weight_hid))
            layer_out = np.dot(layer_hid, weight_out)

            correct_answers += int(np.argmax(layer_out) == np.argmax(train_labels[j : (j + 1)]))

            layer_out_delta = layer_out - train_labels[j : (j + 1)]
            layer_hid_delta = layer_out_delta.dot(weight_out.T) * reluderiv(layer_hid)

            weight_out -= LEARNING_RATE * layer_hid.T.dot(layer_out_delta)
            weight_hid -= LEARNING_RATE * layer_in.T.dot(layer_hid_delta)
        if i % 10 == 0:
            acc = correct_answers * 100 / len(train_images)
            print(f"Epoch {i}: Accuracy: {acc:.2f}%")

TRAIN_IMAGES_COUNT = 1000
TEST_IMAGES_COUNT = 1000
PIXELS_PER_IMAGE = 28 * 28
DIGITS_NUM = 10

(x_train, y_train), (x_test, y_test) = mnist.load_data()

train_images = x_train[0 : TRAIN_IMAGES_COUNT].reshape(TRAIN_IMAGES_COUNT, PIXELS_PER_IMAGE) / 255
train_labels = y_train[0 : TRAIN_IMAGES_COUNT]

test_images = x_test[0 : TEST_IMAGES_COUNT].reshape(TEST_IMAGES_COUNT, PIXELS_PER_IMAGE) / 255
test_labels = y_test[0 : TEST_IMAGES_COUNT]

one_hot_labels_train = np.zeros((len(train_labels), DIGITS_NUM))
for j in range(len(train_labels)):
    one_hot_labels_train[j][train_labels[j]] = 1

one_hot_labels_test = np.zeros((len(test_labels), DIGITS_NUM))
for i,j in enumerate(test_labels):
    one_hot_labels_test[i][j] = 1
    test_labels = one_hot_labels_test

np.random.seed(123)

HIDDEN_SIZE = 50
LEARNING_RATE = 0.01
EPOCH_N = 100


def check_diff_hidden_sizes(HIDDEN_SIZE_LIMIT):
    for hs in range(1, HIDDEN_SIZE_LIMIT):
        weights = generate_weights(PIXELS_PER_IMAGE, hs, DIGITS_NUM).copy()
        print(f"{hs = }")
        do_magic(train_images, one_hot_labels_train, weights, LEARNING_RATE, EPOCH_N)


HIDDEN_SIZE_LIMIT = 10
check_diff_hidden_sizes(HIDDEN_SIZE_LIMIT)
