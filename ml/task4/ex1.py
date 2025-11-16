import numpy as np

def neural_networks(inp, weight):
    return inp * weight

def get_error(true_prediction, prediction):
    return (true_prediction - prediction) ** 2

def do_magic(inp, weight, true_prediction, learning_rate, ITER_N):
    error = 100
    for i in range(ITER_N):
        prediction = neural_networks(inp, weight)
        error = get_error(true_prediction, prediction)
        print("Prediction: %.10f, Weight: %.5f, Error: %.20f" %(prediction, weight, error))
        delta = (prediction - true_prediction) * inp * learning_rate
        weight -= delta
    print("\n")
    return error 

INP = 30
WEIGHT = 0.2
TRUE_PREDICTION = 70
LEARNING_RATE = 0.001
ITER_N = 10

# Увеличение LEARNING_RATE уменьшает погрешность
print("LEARNING_RATE DIFF")
print(f"{LEARNING_RATE = }")
do_magic(INP, WEIGHT, TRUE_PREDICTION, LEARNING_RATE, ITER_N)

LEARNING_RATE = 0.01
print(f"{LEARNING_RATE = }")
do_magic(INP, WEIGHT, TRUE_PREDICTION, LEARNING_RATE, ITER_N)

LEARNING_RATE = 0.1
print(f"{LEARNING_RATE = }")
do_magic(INP, WEIGHT, TRUE_PREDICTION, LEARNING_RATE, ITER_N)

INP = 30
WEIGHT = 0.2
TRUE_PREDICTION = 70
LEARNING_RATE = 0.001
ITER_N = 10

# Увеличение ITER_N уменьшает погрешность
print("ITER_N DIFF")
print(f"{ITER_N = }")
do_magic(INP, WEIGHT, TRUE_PREDICTION, LEARNING_RATE, ITER_N)

ITER_N = 100
print(f"{ITER_N = }")
do_magic(INP, WEIGHT, TRUE_PREDICTION, LEARNING_RATE, ITER_N)

INP = 30
WEIGHT = 0.2
TRUE_PREDICTION = 70
LEARNING_RATE = 0.001
ITER_N = 1

current_error = do_magic(INP, WEIGHT, TRUE_PREDICTION, LEARNING_RATE, ITER_N)
while current_error > 0.0:
    ITER_N += 1
    current_error = do_magic(INP, WEIGHT, TRUE_PREDICTION, LEARNING_RATE, ITER_N)
print(f"{ITER_N = }")
