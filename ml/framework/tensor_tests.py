from tensor import Tensor

def test_mul():
    print(f"\n>{'='*25}|MUL|{'='*25}<\n")
    a_1 = Tensor([1,2,3], autograd=True)
    a_2 = Tensor([4,5,6], autograd=True)
    a_mult = a_1 * a_2
    a_mult.backward(Tensor([4,5,3]))
    print(a_mult.grad)
    print(a_1.grad)
    print(a_2.grad)

def test_id():
    print(f"\n>{'='*25}|ID|{'='*25}<\n")
    a_1 = Tensor([1,2,3], autograd=True)
    a_2 = Tensor([4,5,6], autograd=True)
    a_3 = Tensor([7,8,9], autograd=True)
    print(a_1.id, a_2.id, a_3.id)

def test_add():
    print(f"\n>{'='*25}|ADD|{'='*25}<\n")
    a_1 = Tensor([1,2,3], autograd=True)
    a_2 = Tensor([1,2,3], autograd=True)
    a_3 = Tensor([1,2,3], autograd=True)
    a_add_1 = a_1 + a_2
    a_add_2 = a_2 + a_3
    a_add_3 = a_add_1 + a_add_2
    a_add_3.backward(Tensor([4,5,3]))
    print(a_2.grad)

def test_sub():
    print(f"\n>{'='*25}|SUB|{'='*25}<\n")
    a_1 = Tensor([1,2,3], autograd=True)
    a_2 = Tensor([1,2,3], autograd=True)
    a_3 = Tensor([1,2,3], autograd=True)
    a_sub_1 = a_1 - a_2
    a_sub_2 = a_2 - a_3
    a_add_3 = a_sub_1 + a_sub_2
    a_add_3.backward(Tensor([4,5,3]))
    print(a_1.grad)
    print(a_2.grad)
    print(a_3.grad)

def test_neg():
    print(f"\n>{'='*25}|NEG|{'='*25}<\n")
    a_1 = Tensor([1,2,3], autograd=True)
    a_2 = Tensor([4,5,6], autograd=True)
    a_3 = Tensor([9,8,7], autograd=True)

    a_add_1 = a_1 + (-a_2)
    a_add_2 = a_2 + a_3
    print(a_add_1 + a_add_2)

def test_expand():
    print(f"\n>{'='*25}|EXPAND|{'='*25}<\n")
    a_1 = Tensor([[1,2,3], [4,5,6]], autograd=True)
    a_2 = a_1.__sum__(0)

    print(a_2)
    print(a_2.expand(0,3))

    a_1 = Tensor([[1,2,3], [4,5,6]])
    a_2 = a_1.__sum__(0)
    print('\n', a_2, a_2.data.shape)
    print(a_2.expand(1,2))
    print(a_2.data.shape)

def test_dot():
    print(f"\n>{'='*25}|DOT|{'='*25}<\n")
    a_1 = Tensor([[1,2,3], [4,5,6]], autograd=True)
    a_2 = Tensor([[2,3],[2,3],[2,3]], autograd=True)
    a_3 = a_1.dot(a_2)
    print(a_3)

    a_3.backward(Tensor([1,4]))
    print(a_1.grad)

def test_transpose():
    print(f"\n>{'='*25}|TRANSPOSE|{'='*25}<\n")
    a_1 = Tensor([[1,2,3], [4,5,6]], autograd=True)
    a_2 = Tensor([[2,3],[2,3],[2,3]], autograd=True)
    print(a_2)
    print(a_1)
    print(a_1.transpose())
    print(a_2.transpose())

def test_sigmoid():
    print(f"\n>{'='*25}|SIGMOID|{'='*25}<\n")
    a_1 = Tensor([[1,2,3], [4,5,6]], autograd=True)
    a_3 = a_1.sigmoid()
    a_3.backward(Tensor([4,5,10]))
    print(a_3)
    print(a_1.grad)

def test_tanh():
    print(f"\n>{'='*25}|TANH|{'='*25}<\n")
    a_2 = Tensor([[2,3,4],[2,3,5]], autograd=True)
    a_3 = a_2.tanh()
    a_3.backward(Tensor([4,5,10]))

    print(a_3)
    print(a_2.grad)

def test_all():
    test_add()
    test_id()
    test_neg()
    test_sub()
    test_mul()
    test_expand()
    test_dot()
    test_transpose()
    test_sigmoid()
    test_tanh()

