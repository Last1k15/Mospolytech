class SGD(object):
    def __init__(self, weights, learning_rate = 0.01):
        self.weights = weights
        self.learning_rate = learning_rate

    def step(self):
        for weight in self.weights:
            weight.data -= weight.grad.data * self.learning_rate
            weight.grad.data *= 0
