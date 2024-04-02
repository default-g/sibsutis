import random
import math
import logging
import json

HOST = '127.0.0.1'
PORT = 65433
BUFFER_SIZE = 1024
ROUNDS = 20

format = "[%(asctime)s]: %(message)s"
logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")

def is_prime(n):
  if n == 2 or n == 3: return True
  if n < 2 or n%2 == 0: return False
  if n < 9: return True
  if n%3 == 0: return False
  r = int(n**0.5)
  f = 5
  while f <= r:
    if n % f == 0: return False
    if n % (f+2) == 0: return False
    f += 6
  return True


def generate_prime(a: int, b: int):
    number = 0
    while not is_prime(number):
        number = random.randint(a, b)
    return number


def format_address(address):
    return f"{address[0]}:{address[1]}"


def generate_coprime(a):
    while True:
        b = random.randrange(1, a)
        if math.gcd(a, b) == 1:
            return b

def save_json(object, filename):
    with open(filename, 'w') as fp:
        json.dump(object, fp)


def load_json(filename):
    fp = open(filename, 'r')
    return json.load(fp)

