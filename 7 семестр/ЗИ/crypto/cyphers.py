from .functions import *
import json
from math import gcd

keys = {}

def get_coprime(num: int) -> int:
    res = random.getrandbits(1024)
    while gcd(num, res) != 1:
        res = random.getrandbits(1024)
    return res


def generate_c_d(p: int) -> int:
    c = generate_prime(1, 10 ** 8)
    gcd, d, _ = euclid(c, p)
    assert gcd == 1
    while d < 0:
        d += p
    return c, d


def shamir_encode(m: bytearray) -> list:
    keys['shamir'] = []
    res = list()

    p = generate_prime(1 << 8, 10 ** 9)
    Ca, Da = generate_c_d(p - 1)
    Cb, Db = generate_c_d(p - 1)

    for part in m:
        x1 = pow(part, Ca, p)
        x2 = pow(x1, Cb, p)
        x3 = pow(x2, Da, p)
        res.append(x3)

    keys['shamir'].append({'p': p, 'Ca': Ca, 'Da': Da, 'Cb': Cb, 'Db': Db})
    return res


def shamir_decode(x3: list) -> list:
    res = list()
    with open('keys.json') as keys_file:
        data = json.load(keys_file)
        for key in data['shamir']:
            p = key['p']
            Db = key['Db']

    for part in x3:
        x4 = pow(part, Db, p)
        res.append(x4)
    return res


def elgamal_encode(m: bytearray) -> list:
    keys['Elgamal'] = []
    res = list()

    g = 0
    while True:
        q = generate_prime(10 ** 2, 10 ** 9)
        p = 2 * q + 1
        if is_prime(p) and is_prime(q):
            break

    while pow(g, q, p) != 1:
        g = random.randint(1, p - 1)

    x = random.randint(1, p)
    y = pow(g, x, p)

    k = random.randint(1, p - 1)

    a = pow(g, k, p)
    for m_part in m:
        b = m_part * pow(y, k, p)
        res.append(b)

    keys['Elgamal'].append({'g': g, 'p': p, 'x': x, 'y': y, 'k': k, 'a': a})
    return res


def elgamal_decode(b: list) -> list:
    res = list()
    with open('keys.json') as keys_file:
        data = json.load(keys_file)
        for key in data['Elgamal']:
            p = key['p']
            x = key['x']
            a = key['a']

    for el in b:
        res.append(el * pow(a, p - 1 - x, p) % p)
    return res


def vernam_encode(m: bytearray) -> list:
    keys['vernam'] = []

    codes = [random.randint(0, 255) for _ in range(len(m))]

    keys['vernam'].append(codes)
    return [m[i] ^ codes[i] for i in range(len(m))]


def vernam_decode(m: list) -> list:
    with open('keys.json') as keys_file:
        data = json.load(keys_file)
        codes = data['vernam'][0]

    return [m[i] ^ codes[i] for i in range(len(m))]


def rsa_encode(m: bytearray) -> list:
    keys['rsa'] = []
    res = list()

    p = generate_prime(10 ** 2, 10 ** 9)
    q = generate_prime(10 ** 2, 10 ** 9)

    n = p * q

    phi = (p - 1) * (q - 1)

    d = get_coprime(phi)
    c = euclid(d, phi)[1]


    p2 = generate_prime(10 ** 2, 10 ** 9)
    q2 = generate_prime(10 ** 2, 10 ** 9)

    n2 = p2 * q2

    phi2 = (p2 - 1) * (q2 - 1)

    d2 = get_coprime(phi2)
    c2 = euclid(d2, phi2)[1]

    if c < 0:
        c += phi

    for m_part in m:
        e = pow(pow(m_part, c2, n2), d, n)
        res.append(e)
    keys['rsa'].append({'p': p, 'q': q, 'n': n, 'phi': phi, 'd': d, 'c': c, 'd2' : d2, 'c2' : c2, 'n2' : n2, 'phi2' : phi2 })
    return res


def rsa_decode(e: list) -> list:
    res = list()
    with open('keys.json') as keys_file:
        data = json.load(keys_file)
        for key in data['rsa']:
            n = key['n']
            c = key['c']
            d2 = key['d2']
            n2 = key['n2']

    for el in e:
        u = pow(el, c, n)
        w = pow(u, d2, n2)
        res.append(w)
    return res
