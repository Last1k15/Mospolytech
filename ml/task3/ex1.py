import numpy as np

def neural_networks(inp, weights):
    return inp.dot(weights)

prediction = neural_networks(np.array([150,40]), [0.1, 0.3])
true_prediction = 50
def get_error(true_prediction, prediction):
    return (true_prediction - prediction) ** 2

LIMIT = 0.001
for w1 in range(10):
    for w2 in range(10):
        prediction = neural_networks(np.array([150,40]), [w1/10, w2/10])
        errorValue = get_error(true_prediction, prediction)
        if (errorValue < LIMIT):
            print(f"({w1/10}, {w2/10})=err({errorValue})")
 
