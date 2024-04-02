from crypto  import *
import hashlib
import os
import shutil

def elgamal_sign(m: bytearray) -> bool:
    hash = hashlib.md5(m)
    hash_16 = hash.hexdigest()
    hash_10 = int(hash_16, base=16)

    p = generate_safe_prime(10 ** 2, 10 ** 9)
    g = gen_g(p)

    x = random.randrange(2, p - 1)  # Закрытый ключ
    y = pow(g, x, p)  # Открытый ключ

    k = gen_mutually_prime(p - 1)
    r = pow(g, k, p)

    u = (hash_10 - x * r) % (p - 1)
    kk = inverse(k, p - 1)
    s = kk * u % (p - 1)

    print(f'RSA md5 hash: {hash_16}')

    with open('signs/elgamal.txt', 'w') as f:
        f.write(str(s))


    # Проверка подписи
    yr = pow(y, r, p) * pow(r, s, p) % p
    gh = pow(g, hash_10, p)

    return yr == gh


def rsa_sign(m: bytearray) -> bool:
    p = generate_prime(10 ** 2, 10 ** 9)
    q = generate_prime(10 ** 2, 10 ** 9)

    n = p * q

    phi = (p - 1) * (q - 1)

    d = get_coprime(phi)
    c = euclid(d, phi)[1]
    if c < 0:
        c += phi

    h = hashlib.md5(m).hexdigest()
    print(f'RSA md5 hash: {h}')
    s = [fast_pow(int(i, 16), c, n) for i in h]
    e = ''.join(str(fast_pow(i, d, n)) for i in s)

    h_b = ''.join(str(int(i, 16)) for i in h)

    with open(r'signs/rsa_sign.txt', 'w') as f:
        f.write(h_b)
        f.write('\n' + e)

    return e == h_b


def gost_sign(m: bytearray) -> bool:
    q = generate_prime(1 << 255, (1 << 256) - 1)

    while True:
        b = random.randint(math.ceil((1 << 1023) / q), ((1 << 1024) - 1) // q)
        p = b * q + 1
        if is_prime(p):
            break

    while True:  # Находим a
        g = random.randrange(2, p - 1)
        if (a := pow(g, b, p)) > 1:
            break

    x = random.randint(0, q)
    y = pow(a, x, p)

    h = hashlib.md5(m).hexdigest()
    print(f'gost md5 hash: {h}')
    h = int(h, 16)

    k = random.randint(0, q)
    r = pow(a, k, p) % q
    s = (k * h + x * r) % q
    while s == 0:
        k = random.randint(0, q)
        r = pow(a, k, p) % q
        s = (k * h + x * r) % q

    h = hashlib.md5(m).hexdigest()
    h = int(h, 16)

    temp = extgcd(h, q)[1]
    if temp < 1:
        temp += q

    u1 = (s * temp) % q
    u2 = (-r * temp) % q
    v = ((pow(a, u1, p) * pow(y, u2, p)) % p) % q

    with open(r'signs/gost_sign.txt', 'w') as f:
        f.write(str(v))
        f.write('\n' + str(r))

    return v == r

def read_file(filename: str, ext: str) -> bytearray:
    with open(filename + '.' + ext, 'rb') as origin_file:
        return bytearray(origin_file.read())


def main() -> int:
    try:
        shutil.rmtree('signs')
    except OSError:
        pass
    os.mkdir('signs')

    filename = 'file'
    ext = 'jpg'
    m = read_file(filename, ext)

    print(f'Sign with RSA is: {rsa_sign(m)}')
    print(f'Sign with Elgamal is: {elgamal_sign(m)}')
    print(f'Sign with GOST is: {gost_sign(m)}')
    return 0


if __name__ == '__main__':
    exit(main())
