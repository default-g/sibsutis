from .cfg_object import CFGObject


class Terminal(CFGObject):  # pylint: disable=too-few-public-methods

    def __eq__(self, other):
        return isinstance(other, Terminal) and self.value == other.value

    def __repr__(self):
        return "Terminal(" + str(self.value) + ")"

    def __hash__(self):
        if self._hash is None:
            self._hash = hash(self.value)
        return self._hash

    def to_text(self) -> str:
        text = str(self._value)
        if text and text[0].isupper():
            return '_' + text 
        return text
