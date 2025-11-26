from keras.src.datasets import mnist
import numpy as np


np.random.seed(123)

TRAIN_IMAGES_COUNT = 1000
TEST_IMAGES_COUNT = 1000
PIXELS_PER_IMAGE = 28 * 28
DIGITS_NUM = 10

HIDDEN_SIZE = 50
LEARNING_RATE = 1e-2
EPOCH_N = 50


def relu(x):
    return np.maximum(0, x)


def reluderiv(x):
    return x > 0


def generate_weights(PIXELS_PER_IMAGE, HIDDEN_SIZE, DIGITS_NUM):
    weight_hid = 0.2 * np.random.random((PIXELS_PER_IMAGE, HIDDEN_SIZE)) - 0.1
    weight_out = 0.2 * np.random.random((HIDDEN_SIZE, DIGITS_NUM)) - 0.1
    weights = [weight_hid, weight_out]
    return weights


def encode_labels(input_labels):
    encoded_labels = np.zeros((len(train_labels), DIGITS_NUM))
    for i, lbl in enumerate(input_labels):
        encoded_labels[i][lbl] = 1
    return encoded_labels


def do_magic(train_images, train_labels, weights, learning_rate, epoch_n):

    weight_hid = weights[0].copy()
    weight_out = weights[1].copy()

    for ep in range(EPOCH_N + 1):
        correct_answers = 0
        for img in range(len(train_images)):

            # [1,2,3] ==> [[1,2,3]]
            train_image = train_images[img].reshape(1, -1)
            train_label = train_labels[img].reshape(1, -1)

            layer_in = train_image
            layer_hid = relu(np.dot(layer_in, weight_hid))
            layer_out = np.dot(layer_hid, weight_out)

            correct_answers += int(np.argmax(layer_out) == np.argmax(train_label))

            layer_out_delta = layer_out - train_label
            layer_hid_delta = layer_out_delta.dot(weight_out.T) * reluderiv(layer_hid)

            weight_out -= layer_hid.T.dot(layer_out_delta) * LEARNING_RATE
            weight_hid -= layer_in.T.dot(layer_hid_delta) * LEARNING_RATE

        if (ep % 10 == 0):
            print(f"Epoch {ep}: Accuracy: {correct_answers * 100 / len(train_images):.2f}%")


def check_diff_hidden_sizes(HIDDEN_SIZE_LIMIT):
    for hs in range(1, HIDDEN_SIZE_LIMIT):
        weights = generate_weights(PIXELS_PER_IMAGE, hs, DIGITS_NUM).copy()
        print(f"Hidden Size = {hs}:")
        do_magic(train_images, train_labels, weights, LEARNING_RATE, EPOCH_N)



(x_train, y_train), (x_test, y_test) = mnist.load_data()

train_images = x_train[0 : TRAIN_IMAGES_COUNT].reshape(TRAIN_IMAGES_COUNT, PIXELS_PER_IMAGE) / 255
train_labels = y_train[0 : TRAIN_IMAGES_COUNT]

test_images = x_test[0 : TEST_IMAGES_COUNT].reshape(TEST_IMAGES_COUNT, PIXELS_PER_IMAGE) / 255
test_labels = y_test[0 : TEST_IMAGES_COUNT]

# [[4,...] ==> [[0,0,0,0,1,0,0,0,0,0], ...]]
train_labels = encode_labels(train_labels)
test_labels = encode_labels(test_labels)

HIDDEN_SIZE_LIMIT = 10
check_diff_hidden_sizes(HIDDEN_SIZE_LIMIT)
