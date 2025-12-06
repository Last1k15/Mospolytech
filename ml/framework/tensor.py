import numpy as np
class Tensor:
    ############################################
    ### STATIC
    free_id = 0

    ############################################
    ### CONSTRUCTORS

    def __init__(self, data, creators = None, operation_on_creation = None, autograd=False, id=None):
        self.id = id
        self.autograd = autograd
        self.data = np.array(data)
        self.creators = creators
        self.operation_on_creation = operation_on_creation

        self.children = {}
        self.grad = None

        if id is None:
            self.id = Tensor.free_id
            Tensor.free_id += 1

        if creators is None:
            return

        for creator in creators:
            existence_known = (self.id in creator.children)
            creator.children[self.id] = (creator.children[self.id] + 1) if existence_known else 1


    ############################################
    ### MAGIC_METHODS


    ##################
    # OPERATORS 

    def __add__(self, other):
        if self.autograd and other.autograd:
            return Tensor((self.data + other.data),[self,other],"+",True)
        return Tensor(self.data + other.data) 


    def __neg__(self):
        if self.autograd:
            return Tensor(self.data * -1, [self], "-1", True)
        return Tensor(self.data * -1)


    def __sub__(self, other):
        if self.autograd and other.autograd:
            return Tensor(self.data - other.data, [self, other], "-", True)
        return Tensor(self.data - other.data)


    def __mul__(self, other):
        if self.autograd and other.autograd:
            return Tensor(self.data * other.data, [self, other], "*", True)
        return Tensor(self.data * other.data)

    def __gt__(self, other):
        return self.data.__gt__(other.data)

    # ?
    def __pow__(self, power):
        if self.autograd:
            return Tensor(self.data ** power, [self], "**", True)
        return Tensor(self.data ** power)


    def __sum__(self, axis):
        if self.autograd:
            return Tensor(self.data.sum(axis), [self], "sum_"+str(axis), True)
        return Tensor(self.data.sum(axis))


    ##################
    # CONVERT 

    def __str__(self):
        return str(self.data.__str__())
    

    def __repr__(self):
        return str(self.data.__repr__())

    def __int___(self):
        return int(self.data.__int__())

    ############################################
    ### ACIVATION_FUNC

    def relu(self):
        new_data = np.maximum(0, self.data)
        if self.autograd:
            return Tensor(new_data, [self], "relu", True)
        return Tensor(new_data)


    def sigmoid(self):
        new_data = 1/(1+np.exp(-self.data))
        if self.autograd:
            return Tensor(new_data, [self], "sigmoid", True)
        return Tensor(new_data)


    def tanh(self):
        new_data = np.tanh(self.data)
        if self.autograd:
            return Tensor(new_data, [self], "tanh", True)
        return Tensor(new_data)

    def softmax(self):
        new_data = np.exp(self.data)
        new_data /= np.sum(new_data, axis=1, keepdims=True)
        if self.autograd:
            return Tensor(new_data, [self], "softmax", True)
        return Tensor(new_data)

    ############################################
    ### UTILITY

    def expand(self, axis, count_copies):
        transpose = list(range(0,len(self.data.shape)))
        transpose.insert(axis, len(self.data.shape))
        expand_shape = list(self.data.shape) + [count_copies]
        expand_data = self.data.repeat(count_copies).reshape(expand_shape)
        expand_data = expand_data.transpose(transpose)

        if self.autograd:
            return Tensor(expand_data,[self],"expand_"+str(axis),True)
        return Tensor(expand_data)

    def dot(self, other):
        if self.autograd and other.autograd:
            return Tensor(self.data.dot(other.data), [self,other], "dot",True)
        return Tensor(self.data.dot(other.data))

    def transpose(self):
        data = self.data.transpose()
        if self.autograd:
            return Tensor(data, [self], "transpose",True)
        return Tensor(data)

    def got_children_grads(self):
        for id in self.children:
            if self.children[id] != 0:
                return False
        return True

    def backward(self, grad=None, grad_children=None):
        if self.autograd:
            grad = Tensor(np.ones_like(self.data)) if grad is None else grad
            if (grad_children is not None) and (self.children[grad_children.id] > 0):
                self.children[grad_children.id] -= 1

        self.grad = grad if self.grad is None else (self.grad + grad)

        grads_checked = (grad_children is None) or self.got_children_grads()
        ready_to_continue = (self.creators is not None) and grads_checked 

        if ready_to_continue:
            action = ""
            axis = -1
            if '_' in self.operation_on_creation:
                action, axis = self.operation_on_creation.split('_')
                axis = int(axis)
            else: 
                action = self.operation_on_creation

            match action:

                ##################
                # UNARY

                case "-1":
                    self.creators[0].backward(self.grad.__neg__(), self)


                case "transpose":
                    self.creators[0].backward(self.grad.transpose(), self)


                case "sum":
                        self.creators[0].backward(self.grad.expand(axis, self.creators[0].data.shape[axis]), self)
                    

                ##################
                # BINARY
                    
                case "+":
                    self.creators[0].backward(self.grad, self)
                    self.creators[1].backward(self.grad, self)


                case "-":
                    self.creators[0].backward(self.grad, self)
                    self.creators[1].backward(self.grad.__neg__(), self)


                case "expand":
                    self.creators[0].backward(self.grad.__sum__(axis), self)

                case "*":
                    self.creators[0].backward(self.grad * self.creators[1], self)
                    self.creators[1].backward(self.grad * self.creators[0], self)


                case "**":
                    self.creators[0](self.grad , self)
                    self.creators[1](self.grad, self)


                case "dot":
                    self.creators[0].backward(self.grad.dot(self.creators[1].transpose()),self)
                    self.creators[1].backward(self.grad.transpose().dot(self.creators[0]).transpose(),self)

                ##################
                # ACTIVATION_FUNC

                case "relu":
                    self.creators[0].backward(self.grad * (self > np.zeros(self.grad.data.shape)), self)


                case "sigmoid":
                    self.creators[0].backward(self.grad * (self * (Tensor(np.ones_like(self.grad.data)) - self)) , self)


                case "tanh":
                    self.creators[0].backward(self.grad * (Tensor(np.ones_like(self.grad.data)) - self * self), self)

                case "softmax":
                    self.creators[0].backward(Tensor(self.grad.data), self)
