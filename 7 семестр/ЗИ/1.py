from crypto import *

if __name__ == '__main__':
    a = generate_prime(10 ** 3, 10 ** 10)
    x = generate_prime(10 ** 3, 10 ** 10)
    p = generate_prime(10 ** 3, 10 ** 10)
    print(fast_pow(7,8,12))

    fast_pow_result = fast_pow(a, x, p)

    print(x)
    print(fast_pow_result)
    print(baby_step_giant_step(a, p, fast_pow_result))

    print(euclid(generate_prime(10 ** 5, 10 ** 9), generate_prime(10 ** 5, 10 ** 9)))

    print(generate_common_key())

    print(baby_step_giant_step(2, 7, 9))
