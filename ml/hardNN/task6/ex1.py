import numpy as np
from math import log2, ceil

np.random.seed()

def relu(x):
    return np.maximum(0, x)

def relu_deriv(x):
    return x > 0

def sigmoid(x):
    return 1/(1+np.exp(-x))

def sigmoid_deriv(x):
    return x*(1-x)

def tanh(x):
    return (2 * sigmoid(2 * x) - 1)

def tanh_deriv(x):
    return (1 - x ** 2)

def softmax(x):
    exp = np.exp(x)
    return exp / np.sum(exp, axis=1, keepdims=True)


MAX_NUM = 15
max_bin = ceil(log2(MAX_NUM))

x = np.zeros((MAX_NUM + 1, max_bin))
for i in range(MAX_NUM + 1):
    bin_repres = list(format(i, f"#0{max_bin + 2}b")[2:])
    x[i] = bin_repres

y = np.zeros((MAX_NUM + 1, MAX_NUM + 1))
for i in range(len(y)):
    y[i][i] = 1
input_size = len(x[0]) 
hidden_size = 10 
output_size = len(y[0])

weight_hid = np.random.uniform(size=(input_size, hidden_size))
weight_out = np.random.uniform(size=(hidden_size, output_size))
weights = [weight_hid, weight_out] 

learning_rate = 0.1
epochs = 5000

def train(weights):
    weight_hid = weights[0].copy()
    weight_out = weights[1].copy()

    for epoch in range(1, epochs + 1):
        layer_hid = relu(np.dot(x, weight_hid))
        layer_out = softmax(np.dot(layer_hid, weight_out))
        error = (layer_out - y) ** 2

        layer_out_delta = (layer_out - y) / len(layer_out)
        layer_hidden_delta = layer_out_delta.dot(weight_out.T) * relu_deriv(layer_hid)

        weight_out -= layer_hid.T.dot(layer_out_delta) * learning_rate
        weight_hid -= x.T.dot(layer_hidden_delta) * learning_rate

        if epoch % 1000 == 0:
            error = np.mean(error)
            print(f"Epoch: {epoch}, Error: {error}")

    return [weight_hid, weight_out]

def predict(inp, weights):
    weight_hid = weights[0].copy()
    weight_out = weights[1].copy()

    layer_hid = relu(inp.dot(weight_hid))
    layer_out = softmax(layer_hid.dot(weight_out))

    print(layer_out)

    return np.argmax(layer_out)


weights = train(weights)
for inp in x:
    print(f"\n>{'='*40}<\n")
    prediction = predict(np.array([inp]), weights)
    print(f"Predicted digit: ", prediction)
