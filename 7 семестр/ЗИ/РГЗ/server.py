import socket
import threading
import logging
import utils
import random
import signal


DATABASE_NAME = 'db.json'
database = {}

server_socket = None
def signal_handler(sig, frame):
    utils.save_json(database, DATABASE_NAME)
    server_socket.close()
    exit()


def client_thread(connection, address):
    address = utils.format_address(address)
    logging.info(f'Sent N to {address}')

    username = connection.recv(utils.BUFFER_SIZE).decode()


    connection.sendall(str(N).encode())
    v = int(connection.recv(utils.BUFFER_SIZE).decode())

    if username not in database:
        database[username] = v
    else:
        v = database[username]
    logging.info(f'Value of v from client {address} is {v}')
    for i in range(utils.ROUNDS):
        x = int(connection.recv(utils.BUFFER_SIZE).decode())
        logging.info(f'Value of x from {address} is {x}')
        e = random.getrandbits(1)
        connection.sendall(str(e).encode())
        logging.info(f'Sent e to {address}')

        y = int(connection.recv(utils.BUFFER_SIZE).decode())

        if y == 0:
            logging.error(f'Verification failed on {address}')
            connection.close()
            return

        if y ** 2 % N == (x * v**e) % N:
            logging.info(f'Verification successfull on {address}!')
        else:
            logging.error(f'Verification failed on {address}!')
            connection.close()
            return

database = utils.load_json(DATABASE_NAME)

if 'N' not in database:
    p = utils.generate_prime(10**2, 10**6)
    q = utils.generate_prime(10**2, 10**6)
    N = p * q
    database['N'] = N

N = database['N']


if '__main__' == __name__:

    signal.signal(signal.SIGINT, signal_handler)

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((utils.HOST, utils.PORT))
    server_socket.listen()
    logging.info(f"Server is listening on {utils.format_address(server_socket.getsockname())}")
    logging.info(f"N = {N}")
    while True:
        connection, address = server_socket.accept()
        logging.info(f"Received connection from {utils.format_address(server_socket.getsockname())}")
        threading.Thread(target=client_thread, args=(connection, address)).start()


