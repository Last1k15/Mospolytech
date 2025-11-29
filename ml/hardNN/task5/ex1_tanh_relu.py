import numpy as np
np.random.seed(1)
x = np.array([[0,0],[0,1],[1,0],[1,1]])
y = np.array([[0],[1],[1],[0]])

input_size = len(x[0])
hidden_size = 12
output_size = len(y[0])

weight_hid = np.random.uniform(size=(input_size, hidden_size))
weight_out = np.random.uniform(size=(hidden_size, output_size))
weights = [weight_hid, weight_out] 

learning_rate = 0.1
epochs = 10000

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

def train(weights):
    weight_hid = weights[0].copy()
    weight_out = weights[1].copy()

    for epoch in range(epochs):
        layer_hid = relu(np.dot(x, weight_hid))
        layer_out = tanh(np.dot(layer_hid, weight_out))
        error = (layer_out - y) ** 2

        layer_out_delta = (layer_out - y) * tanh_deriv(layer_out)
        layer_hidden_delta = layer_out_delta.dot(weight_out.T) * relu_deriv(layer_hid)

        weight_out -= layer_hid.T.dot(layer_out_delta) * learning_rate
        weight_hid -= x.T.dot(layer_hidden_delta) * learning_rate

        if epoch % 1000 == 0:
            error = np.mean(error)
            print(f"Epoch: {epoch}, Error: {error}")

    return [weight_hid, weight_out]

def neural_network(inp, weights):
    weight_hid = weights[0]
    weight_out = weights[1]
    layer_hid = relu(inp.dot(weight_hid))
    layer_out = tanh(layer_hid.dot(weight_out))
    return layer_out

new_input = np.array([[0,0]])
print(weights)
weights = train(weights)

print("Prediction:\t", neural_network(new_input, weights))
