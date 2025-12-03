from ex1_tensor import *

class Layer:
    def __init__(self):
        self.params = []

    def get_params(self):
        return self.params

class Linear(Layer):
    def __init__(self, input_count, output_count):
        super().__init__()
        weight = np.random.randn(input_count, output_count) * np.sqrt(2.0/input_count) # Xavier
        self.weight = Tensor(weight, autograd=True)
        self.bias = Tensor(np.zeros(output_count),autograd=True)
        self.params.append(self.weight)
        self.params.append(self.bias)


    def forward(self, inp):
        return inp.dot(self.weight) + self.bias.expand(0, len(inp.data))

class Sequential(Layer):
    def __init__(self, layers):
        super().__init__()
        self.layers = layers


    def add(self, layer):
        self.layerd.append(layer)


    def forward(self, inp):
        for layer in self.layers:
            inp = layer.forward(inp)
        return inp

    def get_params(self):
        params = []
        for layer in self.layers:
            params += layer.get_params()
        return params


class Sigmoid(Layer):
    def __init__(self):
        super().__init__()

    def forward(self, inp):
        return inp.sigmoid()


class Tanh(Layer):

    def __init__(self):
        super().__init__()
    def forward(self, inp):
        return inp.tanh()


class MSELoss(Layer):
    def __init__(self):
        super().__init__()

    def forward(self, prediction, true_prediction):
        square_diff = ((prediction - true_prediction) * (prediction - true_prediction))
        error = Tensor(square_diff.data,autograd=True).__sum__(0)
        error.data *= 0
        return error


class Softmax(Layer):
    def __init__(self):
        super().__init__()

    def forward(self, inp):
        return inp.softmax()
