def neuralNetwork_verbose(inputData, weights):
    prediction = 0
    verbose_list = []
    for i in range(len(inputData)):
        curValue = inputData[i] * weights[i] 
        verbose_list.append(curValue)
        prediction += curValue
    return prediction, verbose_list

weights = [0.2, 0.1]
inputData = [50, 165]

out = neuralNetwork_verbose(inputData, weights)

print(out[0], out[1], sep="\n")

