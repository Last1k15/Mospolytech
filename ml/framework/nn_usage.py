from sgd import *
from tensor import *
from layers import * 


class Config:
    def __init__(self, model, error_manager, io_list, extra_list = None):
        self.model = model
        self.learning_rate = extra_list[1]
        self.sgd = SGD(self.model.get_params(), self.learning_rate)

        self.error_manager = error_manager
        self.epochs = extra_list[0]

        self.inputs = io_list[0]
        self.outputs = io_list[1]

    def __copy__(self):
        new_instance = self.__class__.__new__(self.__class__)
        new_instance.model = self.model
        new_instance.learning_rate = self.learning_rate
        new_instance.error_manager = self.error_manager
        new_instance.epochs = self.epochs
        new_instance.inputs = self.inputs
        new_instance.outputs = self.outputs
        new_instance.sgd = SGD(new_instance.model.get_params(), new_instance.learning_rate)
        return new_instance


def trainPlus(config: Config, error_requirement = 1e-3, delta_floor = 1e-6):
    error_median = 1e13
    error_median_prev = 1e13
    epoch = 1
    end_reason = "ERROR_REQUIREMENT"

    while (error_median > error_requirement):
        predictions = config.model.forward(config.inputs)
        error = config.error_manager.forward(predictions, config.outputs)
        error.backward(Tensor(np.ones_like(error.data)))
        config.sgd.step()

        error_median_prev = error_median
        error_median = np.mean(error.data)
        delta = abs(error_median_prev - error_median)

        if (error_median > 1e15):
            end_reason = "ERROR_CEIL"
            break

        if (delta < delta_floor):
            end_reason = "DELTA_FLOOR"
            break

        if ((epoch + 1) > config.epochs):
            end_reason = "EPOCH_CEIL"
            break

        if epoch % 1000 == 0:
            print(f"EPOCH: {epoch} ERROR: {error_median} Δ(ERR): {delta}")

        epoch += 1

    print('-'*50)
    print(f"END REASON: {end_reason}")
    print(f"EPOCH: {epoch} ERROR: {error_median} Δ(ERR): {delta}")
    print('-'*50, '\n')


def train(config: Config):
    for epoch in range(1, config.epochs + 1):
        predictions = config.model.forward(config.inputs)
        error = config.error_manager.forward(predictions, config.outputs)
        error.backward(Tensor(np.ones_like(error.data)))
        config.sgd.step()

        if epoch % (config.epochs / 10) == 0:
            print(f"Epoch: {epoch}, Error: {error}")


def test(config: Config):
    predictions = config.model.forward(config.inputs)
    for i in range(len(config.outputs.data)):
        prediction = predictions.data[i]
        expected = config.outputs.data[i]
        print(f"Prediction: {prediction}\nExpected: {expected}")

# def trainPlus(error_requirement = 1e-3, epoch_ceil = 1e4, delta_floor = 1e-6):
#     error_median = 1e13
#     error_median_prev = 1e13
#     epoch = 1
#
#     while (error_median > error_requirement):
#         predictions = model.forward(train_inputs)
#         error = loss.forward(predictions, train_labels)
#         error.backward(Tensor(np.ones_like(error.data)))
#         sgd.step()
#
#         epoch += 1
#         error_median_prev = error_median
#         error_median = np.mean(error.data)
#         delta = abs(error_median_prev - error_median)
#
#         if (delta < delta_floor):
#             break
#
#         if epoch > epoch_ceil:
#             raise OverflowError("\nEPOCH EXCEEDED LIMIT\n")
#
#         if (error_median > 1e15):
#             raise OverflowError(f"\nERROR EXCEEDED LIMIT - {error_median}\n")
#
#         if epoch % 10 == 0:
#             print(f"Epoch: {epoch} Error: {error_median} Δ(ERR): {delta}")
#
#     print('-'*50)
#     print(f"Epoch: {epoch}, Error: {error_median} Δ: {delta}")
#     print('-'*50, '\n')
#
# def train():
#     for epoch in range(1, EPOCHS + 1):
#         predictions = model.forward(train_inputs)
#         error = loss.forward(predictions, train_labels)
#         error.backward(Tensor(np.ones_like(error.data)))
#         sgd.step()
#
#         if epoch % (EPOCHS / 10) == 0:
#             print(f"Epoch: {epoch}, Error: {error}")
#
# def test(test_inputs, test_labels):
#     predictions = model.forward(test_inputs)
#     for i in range(len(test_labels.data)):
#         prediction = predictions.data[i]
#         expected = test_labels.data[i]
#         print(f"Prediction: {prediction}\nExpected: {expected}")
