def neuralNetwork(inputData, weights, OUT_COUNT):
    prediction = [0] * OUT_COUNT;
    for i in range(OUT_COUNT):
        prediction[i] = sum([inputData[j] * weights[i][j] for j in range(len(inputData))])
    return prediction

w1 = w2 = 0
weight1 = [w1, w2, 0.7]
weight2 = [w1, w2, 0.7]
weight3 = [w1, w2, 0.34]
weight4 = [w1, w2, 0.1]
weights = [weight1, weight2, weight3, weight4]

inputData = [50, 165, 45]


OUT_COUNT = 4

for i in range(100):
    for j in range(100):
        w1 = i/100
        w2 = j/100
        if (w1 * inputData[0] == w2 * inputData[1]):
            print(f"{w1,w2} = {w1 * inputData[0]} = {w2 * inputData[1]}")


out = neuralNetwork(inputData, weights, OUT_COUNT)
print(out)
