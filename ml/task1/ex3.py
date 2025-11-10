def neuralNetwork(inputData, weight):
    prediction = [inputData * weight[i] for i in range(len(weight))]
    return prediction

inputValue = 4

w1 = w2 = 0
out = [0,0]
while out[0] < 0.5: 
    w1 += 0.1
    out = neuralNetwork(inputValue, [w1, w2])

while out[1] < 0.5: 
    w2 += 0.1
    out = neuralNetwork(inputValue, [w1, w2])

print(f"{w1,w2} = {out}")
