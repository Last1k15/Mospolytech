def neuralNetwork_verbose(inputData, weight):
    prediction = sum([inputData[i] * weight[i] for i in range(len(inputData))])
    return prediction

inputSet1 = [150, 40]
inputSet2 = [80, 60]
inputData = [inputSet1, inputSet2]

weight1 = [0.3, 0.4]
weight2 = [0.2, 0.4]
weights = [weight1, weight2]

INPUT_DATA = [150,160,120,130,140]
WEIGHT_DATA = 0.3
BIAS = 10

for CUR_INPUT_DATA in INPUT_DATA:
    out = neuralNetwork_verbose(CUR_INPUT_DATA, WEIGHT_DATA, BIAS)
    print(out)
