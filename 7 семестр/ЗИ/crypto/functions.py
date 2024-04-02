import math
import os
import random
import sys
import struct

def fast_pow(base: int, power: int, mod: int = None):
    result = 1

    if mod:
        base %= mod
        result %= mod  # Для правильного вычисления, когда показатель равен 0, а модуль отрицателен

    while power:
        if power % 2 == 1:
            result = (result * base) % mod if mod else result * base

        base = (base * base) % mod if mod else base * base
        power //= 2

    return result


def euclid(a: int, b: int):
    if a < b:
        a, b = b, a

    u = [a, 1, 0]
    v = [b, 0, 1]
    while v[0] != 0:
        q = u[0] // v[0]
        t = [
            u[0] % v[0],
            u[1] - q * v[1],
            u[2] - q * v[2],
        ]
        u, v = v, t
    return u


def extgcd(a: int, b: int) -> tuple:
    if a <= 0 or b <= 0:
        raise ValueError("Числа могут быть только натуральными")
    # if a < b:
    #     a, b = b, a  # Ломает алгоритм
    u1, u2, u3 = a, 1, 0
    v1, v2, v3 = b, 0, 1
    while v1:
        q = u1 // v1
        t1, t2, t3 = u1 % v1, u2 - q * v2, u3 - q * v3
        u1, u2, u3 = v1, v2, v3
        v1, v2, v3 = t1, t2, t3
    return u1, u2, u3


def is_prime(n, trials=8):
    """
    Miller-Rabin primality test.

    A return value of False means n is certainly not prime. A return value of
    True means n is very likely a prime.
    """
    if n != int(n):
        return False
    n = int(n)
    # Miller-Rabin test for prime
    if n == 0 or n == 1 or n == 4 or n == 6 or n == 8 or n == 9:
        return False

    if n == 2 or n == 3 or n == 5 or n == 7:
        return True
    s = 0
    d = n - 1
    while d % 2 == 0:
        d >>= 1
        s += 1
    assert (2 ** s * d == n - 1)

    def trial_composite(a):
        if pow(a, d, n) == 1:
            return False
        for i in range(s):
            if pow(a, 2 ** i * d, n) == n - 1:
                return False
        return True

    for i in range(trials):  # number of trials
        a = random.randrange(2, n)
        if trial_composite(a):
            return False

    return True


def generate_prime(a: int, b: int):
    number = 0
    while not is_prime(number):
        number = random.randint(a, b)
    return number


def generate_common_key():
    # Alice's secret
    a = generate_prime(1, fast_pow(10, 9))

    # Bob's secret
    b = generate_prime(1, fast_pow(10, 9))

    # Generating p
    p = generate_prime(1, fast_pow(10, 9))

    # Generating g
    g = generate_prime(1, p - 1)

    q = (p - 1) / 2
    # Calculating q
    while not is_prime(q):
        p = generate_prime(1, fast_pow(10, 9))
        q = (p - 1) / 2

    while fast_pow(g, q, p) == 1:
        g = generate_prime(1, p - 1)

    def calculate_open_key(secret, g, p):
        return fast_pow(g, secret, p)

    # Alice's open key
    open_key_A = calculate_open_key(a, g, p)

    # Bob's open key
    open_key_B = calculate_open_key(b, g, p)

    def calculate_common_key(other_open_key, secret, p):
        return fast_pow(other_open_key, secret, p)

    # Generating common keys
    common_key_A = calculate_common_key(open_key_B, a, p)
    common_key_B = calculate_common_key(open_key_A, b, p)

    # Comparing
    assert common_key_A == common_key_B

    return common_key_A


def baby_step_giant_step(g, h, p):
    n = math.ceil(math.sqrt(p))
    baby_steps = {}

    for i in range(n):
        baby_steps[pow(g, i, p)] = i

    giant_step = pow(g, -n, p)
    y = h
    for j in range(n):
        if y in baby_steps:
            x = j * n + baby_steps[y]
            return x
        y = fast_pow(y * giant_step, 1, p)

    return None


def gen_mutually_prime(a):
    while True:
        b = random.randrange(2, a)
        if math.gcd(a, b) == 1:
            return b


def gen_c_d(p):
    c = gen_mutually_prime(p)
    gcd, d, _ = extgcd(c, p)
    assert gcd == 1
    while d < 0:
        d += p
    return c, d

def generate_safe_prime(a: int, b: int) -> int:
    if a > b:
        a, b = b, a
    while True:
        q = generate_prime(a // 2, (b - 1) // 2)
        if is_prime(p := q * 2 + 1):
            return p

def gen_mutually_prime(a):
    while True:
        b = random.randrange(2, a)
        if math.gcd(a, b) == 1:
            return b


def gen_g(mod: int) -> int:
    while True:
        g = random.randrange(2, mod)
        if pow(g, (mod - 1) // 2, mod) != 1:
            return g

def inverse(n, p):
    gcd, inv, _ = extgcd(n, p)
    assert gcd == 1
    return inv


def exponentiation_modulo(a: int, x: int, p: int) -> int:
    if p == 0:
        raise ValueError("Модуль не может быть равен нулю")
    if x < 0:
        raise ValueError("Показатель не может быть отрицательным")
    result = 1
    a = a % p
    if a == 0:
        return 0
    while x > 0:
        if x & 1 == 1:
            result = (result * a) % p
        a = (a ** 2) % p
        x >>= 1
    return result
