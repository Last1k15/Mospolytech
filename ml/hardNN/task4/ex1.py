from keras.src.datasets import mnist
import numpy as np

np.random.seed(123)

train_images_count = 1000
test_images_count = 10000
pixels_per_image = 28 * 28
digits_num = 10

def relu(x):
    return np.maximum(0, x)

def reluderiv(x):
    return x > 0

def encode_labels(input_labels):
    encoded_labels = np.zeros((len(input_labels), digits_num))
    for i,lbl in enumerate(input_labels):
        encoded_labels[i][lbl] = 1
    return encoded_labels



(x_train, y_train), (x_test, y_test) = mnist.load_data()

train_images = x_train[0 : train_images_count].reshape(train_images_count, pixels_per_image) / 255
train_labels = y_train[0 : train_images_count]

test_images = x_test[0 : test_images_count].reshape(test_images_count, pixels_per_image) / 255
test_labels = y_test[0 : test_images_count]

test_labels = encode_labels(test_labels)
train_labels = encode_labels(train_labels)

hidden_size = 50
learning_rate = 0.01
epoch_n = 100


def do_magic(prob):

    weight_hid = 0.2 * np.random.random((pixels_per_image, hidden_size)) - 0.1
    weight_out = 0.2 * np.random.random((hidden_size, digits_num)) - 0.1

    for e in range(epoch_n + 1):
        correct_answers = 0
        for img in range(len(train_images)):
            train_image = train_images[img].reshape(1,-1)
            train_label = train_labels[img].reshape(1,-1)

            layer_in = train_image

            layer_hid = relu(np.dot(layer_in, weight_hid))
            dropout_mask = np.random.binomial(1, prob, layer_hid.shape)
            # dropout_mask = np.random.randint(2, size = layer_hid.shape)
            layer_hid *= dropout_mask * 2

            layer_out = np.dot(layer_hid, weight_out)

            correct_answers += int(np.argmax(layer_out) == np.argmax(train_label))

            layer_out_delta = layer_out - train_label
            layer_hid_delta = layer_out_delta.dot(weight_out.T) * reluderiv(layer_hid) * dropout_mask

            weight_out -= layer_hid.T.dot(layer_out_delta) * learning_rate
            weight_hid -= layer_in.T.dot(layer_hid_delta) * learning_rate

        if (e % 20 == 0):
            print(f"epoch: {e}")
            print(f"accuracy: {(correct_answers * 100 / len(train_images)):.2f}")

def check_diff_masks(PROB_LIMIT, PROB_STEP):
    if (PROB_LIMIT > 1):
        raise ValueError("PROB_LIMIT cannot be greater than 1")
    for prob in np.arange(0, PROB_LIMIT, PROB_STEP):
        print(f"\n>{'='*100}<\n")
        print(f"{prob = }")
        do_magic(prob)

PROB_LIMIT = 1
PROB_STEP = 0.1
check_diff_masks(PROB_LIMIT, PROB_STEP)
