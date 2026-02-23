from torchvision.datasets import CIFAR10
import torchvision.transforms as tr
from torch.utils.data import DataLoader
from torch import cat

from .nn import InputData

############################## EXTERN ##############################
class CifarConfig():
    def __init__(self, root : str, train_batch_size : int, test_batch_size : int, train_n : int, test_n : int):
        self.root = root
        self.train_batch_size = train_batch_size
        self.test_batch_size = test_batch_size
        self.train_n = train_n
        self.test_n = test_n


def get_cifar_data(config : CifarConfig) -> InputData:

    ROOT = config.root
    TRAIN_BATCH_SIZE = config.train_batch_size
    TEST_BATCH_SIZE = config.test_batch_size
    TRAIN_N = config.train_n
    TEST_N = config.test_n

    tranformations = tr.Compose([
            tr.ToTensor(),
            tr.Normalize(
                (0.5, 0.5, 0.5),
                (0.5, 0.5, 0.5)
            )
    ])

    train_set = CIFAR10(
            train=True,
            transform=tranformations,
            root=ROOT,
            download=True
    )

    train_data_loader = DataLoader(
            train_set,
            batch_size=TRAIN_BATCH_SIZE,
            shuffle=True
    )

    test_set = CIFAR10(
            train=False,
            transform=tranformations,
            root=ROOT,
            download=True
    )

    test_data_loader = DataLoader(
            test_set,
            batch_size=TEST_BATCH_SIZE,
            shuffle=False
    )
    


    trainIter = iter(train_data_loader)
    testIter = iter(test_data_loader)

    train_images, train_labels = getLoaderData(trainIter, TRAIN_N)
    test_images, test_labels = getLoaderData(testIter, TEST_N)

    return InputData(train_images, train_labels, test_images, test_labels)


############################## STATIC ##############################
def getLoaderData(iter, N):
    images = []
    labels = []
    for i in range(N):
        image_batch, label_batch = next(iter)
        images.append(image_batch)
        labels.append(label_batch)
    images = cat(images, dim=0)
    labels = cat(labels, dim=0)
    return images, labels
