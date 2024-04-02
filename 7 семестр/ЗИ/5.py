from crypto import *
import hashlib
import math
import random
import sys

vote_options = {
    'Да': 0,
    'Нет': 1,
    'Воздержался': 2
}

class Server:
    def __init__(self):
        self.blanks = set()
        P, Q = generate_prime(1 << 1023, (1 << 1024) - 1), generate_prime(1 << 1023, (1 << 1024) - 1)

        self.N = P * Q
        phi = (P - 1) * (Q - 1)
        self._C, self.d = gen_c_d(phi)
        self.voted = set()
    def _sha(n):
        return int.from_bytes(
            hashlib.sha3_224(n.to_bytes(math.ceil(n.bit_length() / 8), byteorder=sys.byteorder)).digest(),
            byteorder=sys.byteorder
    )


    def __get_blank(self, name: str, _h: int) -> int:
        if name in self.voted:
            raise Exception(f'{name} уже голосовал')
        self.voted.add(name)
        return pow(_h, self._C, self.N)


    def receive_vote(self, name, vote_num):
        n = (random.getrandbits(1024) << 1024) | vote_num
        r = gen_mutually_prime(self.N)
        h = Server._sha(n)
        _h = (h * pow(r, self.d, self.N)) % self.N

        _s = self.__get_blank(name, _h)

        s = (_s * inverse(r, self.N)) % self.N

        if Server._sha(n) == pow(s, self.d, self.N):
            print(f'Бланк <{str(n)[:5]}..., {str(s)[:5]}...> одобрен')
            self.blanks.add((n, s))
        else:
            print(f'Бланк <{str(n)[:5]}..., {str(s)[:5]}...> отклонён')
            print(Server._sha(n))
            print(pow(s, self.d, self.N))


    def get_blanks(self):
        return self.blanks.copy()


# Create an instance of the Server class
server = Server()

# Example votes
server.receive_vote('Alice', vote_options['Да'])
server.receive_vote('Bob', vote_options['Нет'])
server.receive_vote('Alice', vote_options['Нет'])
