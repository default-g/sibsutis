
from .variable import Variable
from .terminal import Terminal


def to_variable(given):
    if isinstance(given, Variable):
        return given
    return Variable(given)


def to_terminal(given):
    if isinstance(given, Terminal):
        return given
    return Terminal(given)
