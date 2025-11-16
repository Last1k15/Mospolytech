'''
    Напишите по памяти код из урока "Упрощение кода с помощью NumPy".
    Добавьте еще один скрытый слой к нейросети. Создайте третий набор весов weights_h_3 = [0.6, 0.2] и weights_out_3 = [0.7, 0.4]. 
    Добавьте его в переменные weights_h и weights_out. Измените функцию neural_network так, чтобы она работала с этим третьим слоем.
    Замените списки с фиксированными весами на массивы numpy, причём с генерацией случайных значений в них.
'''
import numpy as np
def neuralNetwork(inputData, weights):
    prediction_h = inputData.dot(weights[0])
    prediction_h = inputData.dot(weights[1])
    prediction_h = inputData * weights[2]
    prediction = prediction_h.dot(weights[3])
    return prediction

'''
[i][h0]    [h2][o]
       [h1]
[i][h0]    [h2][o]
'''

weight_h01 = np.random.rand(2) # [0.4, 0.1]
weight_h02 = np.random.rand(2) # [0.3, 0.2]
weight_h0 = np.array([weight_h01, weight_h02]).T

weight_h1 = np.random.rand(2) # [0.6, 0.2]
weight_h2 = np.random.rand(2) # [0.7, 0.4]

weight_out1 = np.random.rand(2) # [0.4, 0.1]
weight_out2 = np.random.rand(2) # [0.3, 0.1]
weight_out = np.array([weight_out1, weight_out2]).T

weights = [weight_h0, weight_h1, weight_h2, weight_out]

inputData = np.array([23, 45])
out = neuralNetwork(inputData, weights)
print(out)

