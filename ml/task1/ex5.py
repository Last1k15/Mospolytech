def neuralNetwork(inputData, weights, H_COUNT, OUT_COUNT):
    prediction_h = [0] * H_COUNT
    for curHidden in range(H_COUNT):
        for curInput in range(len(inputData)):
            prediction_h[curHidden] += inputData[curInput] * weights[0][curHidden][curInput]

    print(f"{prediction_h = }")

    prediction = [0] * OUT_COUNT
    for curOut in range(OUT_COUNT):
        for curHidden in range(H_COUNT):
            prediction[curOut] += prediction_h[curHidden] * weights[1][curOut][curHidden]

    return prediction

H_COUNT = 2
OUT_COUNT = 2

w1 = w2 = 0

weight_out1 = [0.4, 0.1]
weight_out2 = [0.3, 0.1]
weight_out = [weight_out1, weight_out2]


inputData = [23, 45]

over = False
for i in range(100):
    if over: 
        break
    for j in range(100):
        w1 = i/100
        w2 = j/100
        if (w1 * inputData[0] > 5 and w2 * inputData[1] > 5):
            print(f"{(w1,w2) = }")
            over = True
            break

weight_h1 = [w1, w2]
weight_h2 = [w1, w2]
weight_h = [weight_h1, weight_h2]

weights = [weight_h, weight_out]

out = neuralNetwork(inputData, weights, H_COUNT, OUT_COUNT)
print(out)
