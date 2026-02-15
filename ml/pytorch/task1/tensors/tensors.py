import numpy as np
import torch as t
import torch.nn as nn

t1, t2 = t.randn(3, 3), t.randn(3, 3)
print(
        "t1 = ",
        t1, 
        "t2 = ",
        t2, 
        "(t1 + t2) = ",
        (t1 + t2), 
        "(t1 * t2) = ",
        (t1 * t2), 
        "t2^T = ",
        t.transpose(t2, 0, 1), 
        "med(t1) = ",
        t.median(t1),
        "med(t2) = ",
        t.median(t2),
        "max(t1) = ",
        t.max(t1),
        "max(t2) = ",
        t.max(t2),
        sep="\n\n"
)
