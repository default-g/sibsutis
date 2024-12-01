
from .terminal import Terminal


class Epsilon(Terminal):

    def __init__(self):
        super().__init__("epsilon")

    def to_text(self) -> str:
        return "epsilon"
