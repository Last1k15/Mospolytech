from tests import *
from tensor import *
from sgd import *

np.random.seed(1)

def train(inp, weights, true_predictions, sgd, epochs):
    weights_hid = weights[:-1]
    weight_out = weights[-1]

    for e in range(epochs):
        predictions = inp.dot(weights_hid[0]).relu()
        for i in range(1, len(weights_hid)):
            predictions += predictions.dot(weights[i]).relu()
        predictions = predictions.dot(weight_out)

        error = (predictions - true_predictions) * (predictions - true_predictions)
        error.backward(Tensor(np.ones_like(error.data)))
        sgd.step()

def test(test_inputs, weights, true_predictions):
    weights_hid = weights[:-1]
    weight_out = weights[-1]

    acc_med = 0

    predictions = test_inputs.dot(weights_hid[0]).relu()
    for i in range(1, len(weights_hid)):
        predictions += predictions.dot(weights_hid[i]).relu()
    predictions = predictions.dot(weight_out)

    for i in range(len(true_predictions.data)):
        prediction = predictions.data[i][0]
        true_prediction = true_predictions.data[i][0]

        max_v = max(prediction, true_prediction)
        min_v = min(prediction, true_prediction)
        acc = min_v * 100 / max_v
        acc_med += acc

        print(f"Prediction: {prediction:.2f}\nExpected: {true_prediction:.2f}\nAccuracy: {acc:.2f}%\n")
    acc_med = acc_med / len(true_predictions.data)
    return acc_med



def benchmark(inputs, true_predictions, common_data, count = 1):
    hidden_size, learning_rate, epochs = common_data
    train_input, test_input = inputs
    train_true_predictions, test_true_predictions = true_predictions

    input_size = len(train_input.data[0])
    output_size = len(train_true_predictions.data[0])

    acc_med = 0

    for c in range(1, count + 1):
        print(f"\n>{'='*100}<\n")
        print(f"{c = }\n")

        weights = [
            Tensor(np.random.rand(input_size,hidden_size),autograd=True),
            Tensor(np.random.rand(hidden_size,output_size),autograd=True)
        ]

        sgd = SGD(weights, learning_rate)
        train(train_input, weights, train_true_predictions, sgd, epochs)

        acc_med += test(test_input, weights, test_true_predictions)
    return acc_med / count


train_input = Tensor([
    [2,3,5], 
    [2,4,6],
],autograd=True)
train_true_predictions = Tensor([
    [30], 
    [48],
],autograd=True)

test_input = Tensor([
    [9,3,1],
    [3,5,4]
],autograd=True)

test_true_predictions = Tensor([
    [27],
    [60]
],autograd=True)

inputs = [train_input, test_input]
true_predictions = [train_true_predictions, test_true_predictions]

hidden_size = 20
learning_rate = 1e-4
epochs = 1000
common_data = [hidden_size, learning_rate, epochs]

repeats = 1
acc_med = benchmark(inputs, true_predictions, common_data, repeats)
# test_all()
