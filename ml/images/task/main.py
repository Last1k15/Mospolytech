import torch as t
import torchvision as tv
import numpy as np
import matplotlib.pyplot as plt

from util import *
from spec import *

############################## SETUP ##############################
cifarConfig = CifarConfig(
        root="./saved",
        train_batch_size=20,
        test_batch_size=20,
        train_n=100,
        test_n=3
)


model=MyModel()
config = Config(
        model=model,
        loss=t.nn.CrossEntropyLoss(),
        optimizer=t.optim.Adam(model.parameters(), lr=1e-6, weight_decay=1e-4),
        epochs=4e3,
        inp=get_cifar_data(cifarConfig),
        batch_size=cifarConfig.train_batch_size,
        model_output_name="myModel.pth"
)


############################## TRAIN & TEST ##############################
train(config)
config.model.load_state_dict(t.load(config.model_output_name))
test_results = t.max(config.model(config.inp.test), 1)[1]
compare_results(test_results, config.inp.test_labels)


############################## VISUAL ##############################
images = config.inp.test
images = tv.utils.make_grid(images)
images = images / 2 + 0.5
plt.imshow(np.transpose(images.numpy(), (1,2,0)))
plt.show()
