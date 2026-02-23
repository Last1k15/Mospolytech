import torch as t
import torch.nn as nn
import torch.nn.functional as f

class MyModel(nn.Module):

    class SizeTracker():
        def __init__(self, initSize : int):
            self.size = initSize
            self.last_out_channels = None


        def updateSize(self, layer) -> None:
            if isinstance(layer, nn.Conv2d):
                self.size = ((self.size - layer.kernel_size[0] + 2*layer.padding[0]) / layer.stride[0] + 1)
                self.last_out_channels = layer.out_channels

            elif isinstance(layer, nn.MaxPool2d):
                self.size /= 2


        def getSize(self) -> int:
            return int(self.size * self.size * self.last_out_channels)


    def __init__(self):
        super().__init__()

        st = self.SizeTracker(32)
        self.conv1 = nn.Conv2d(in_channels=3, out_channels=12, kernel_size=3, stride=1, padding=1)
        self.bn1 = nn.BatchNorm2d(12)
        st.updateSize(self.conv1)
        
        self.pool2 = nn.MaxPool2d(kernel_size=2, stride=2)
        st.updateSize(self.pool2)

        self.conv3 = nn.Conv2d(in_channels=12, out_channels=24, kernel_size=3, stride=1, padding=1)
        self.bn3 = nn.BatchNorm2d(24)
        st.updateSize(self.conv3)


        self.linearSize = st.getSize()
        self.fc4 = nn.Linear(self.linearSize, 10)


    def convStep(self, inp, conv, bn):
        return f.relu(bn(conv(inp)))


    def forward(self, x) -> t.tensor:
        out = x
        out = self.convStep(out, self.conv1, self.bn1)
        out = self.pool2(out)
        out = self.convStep(out, self.conv3, self.bn3)
        out = out.view(-1, self.linearSize)
        out = self.fc4(out)
        return out
