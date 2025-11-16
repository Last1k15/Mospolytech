import numpy as np

def neural_networks(inp, weight):
    return inp * weight

def get_error(true_prediction, prediction):
    return (true_prediction - prediction) ** 2

def do_magic(true_prediction, inp, weight, LEARN_ITER):
    iterNeeded = 0
    for i in range(LEARN_ITER):
        prediction = neural_networks(inp, weight)
        error = get_error(true_prediction, prediction)
        print(f"{prediction = }\t{error = }")
        delta = (prediction - true_prediction) * inp
        weight = weight - delta
        iterNeeded += 1
    print("\n")

INP = 0.9
WEIGHT = 0.2
LEARN_ITER = 10
TRUE_PREDICTION = 0.2

# При увеличении true_prediction ошибка увеличивается
print("WEIGHT DIFF")
print(f"{WEIGHT = }")
do_magic(TRUE_PREDICTION, INP, WEIGHT, LEARN_ITER)
WEIGHT = 0.9
print(f"{WEIGHT = }")
do_magic(TRUE_PREDICTION, INP, WEIGHT, LEARN_ITER)

INP = 0.9
WEIGHT = 0.2
LEARN_ITER = 10
TRUE_PREDICTION = 0.2

# При увеличении INP мы "проскакиваем" искомое значение и уходим в бесконечность
print("INP DIFF")
print(f"{INP = }")
do_magic(TRUE_PREDICTION, INP, WEIGHT, LEARN_ITER)
INP = 90
print(f"{INP = }")
do_magic(TRUE_PREDICTION, INP, WEIGHT, LEARN_ITER)

INP = 0.9
WEIGHT = 0.2
LEARN_ITER = 10
TRUE_PREDICTION = 0.2

# При увеличении true_prediction ошибка увеличивается
print("TRUE_PREDICTION DIFF")
print(f"{TRUE_PREDICTION = }")
do_magic(TRUE_PREDICTION, INP, WEIGHT, LEARN_ITER)
TRUE_PREDICTION = 200
print(f"{TRUE_PREDICTION = }")
do_magic(TRUE_PREDICTION, INP, WEIGHT, LEARN_ITER)

INP = 0.9
WEIGHT = 0.2
LEARN_ITER = 10
TRUE_PREDICTION = 0.2

# При увеличении ITER_N ошибка уменьшается
print("LEARN_ITER DIFF")
print(f"{LEARN_ITER = }")
do_magic(TRUE_PREDICTION, INP, WEIGHT, LEARN_ITER)
LEARN_ITER = 100
print("{LEARN_ITER = }")
do_magic(TRUE_PREDICTION, INP, WEIGHT, LEARN_ITER)
