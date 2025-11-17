import numpy as np
def relu(x):
    return max(0, x)

def relu(x):
    return [max(0, x[i]) for i in range(len(x))]

inp = np.array([
    [15, 10],
    [15, 15],
    [15, 20],
    [25, 10]
])
    
true_prediction = np.array([[10, 20, 15, 20]]).T

layer_hid1_size = 4
layer_hid2_size = 4
layer_in_size = len(inp[0])
layer_out_size = len(true_prediction[0])

weights_hid1 = 2 * np.random.random((layer_in_size, layer_hid1_size)) - 1
weights_hid2 = 2 * np.random.random((layer_hid1_size, layer_hid2_size)) - 1
weights_out = 2 * np.random.random((layer_hid2_size, layer_out_size)) - 1

prediction_hid1 = relu(np.dot(inp[0], weights_hid1))
print(prediction_hid1)
prediction_hid2 = relu(np.dot(prediction_hid1, weights_hid2))
prediction = prediction_hid2.dot(weights_out)
print(prediction)
