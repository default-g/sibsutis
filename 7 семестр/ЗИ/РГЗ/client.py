import socket
import utils
import logging
import random
import sys

username = sys.argv[1]
users_s = utils.load_json('users_s.json')

if __name__ == '__main__':
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.connect((utils.HOST, utils.PORT))

    connection.sendall(username.encode())

    N = int(connection.recv(utils.BUFFER_SIZE).decode())
    logging.info(f'Received N from server : {N}')

    s = utils.generate_coprime(N)
    if username not in users_s:
        users_s[username] = s
        utils.save_json(users_s, 'users_s.json')
    else:
        s = users_s[username]

    v  = (s ** 2) % N
    connection.sendall(str(v).encode())
    logging.info(f'Generated v and sent to server : {v}')
    try:
        for i in range(utils.ROUNDS):
                r = random.randint(1, N)
                x = (r ** 2) % N
                connection.sendall(str(x).encode())
                logging.info(f'Generated x and sent to server : {x}')

                e = int(connection.recv(utils.BUFFER_SIZE).decode())

                logging.info(f'Received e from server : {e}')

                if e == 0:
                    y = r
                else:
                    y = (r * s ** e) % N

                connection.sendall(str(y).encode())

                logging.info(f'Sent to server : {y}')
        logging.info('Verification successfull')
    except:
        logging.error('Verification failed')
        connection.close()
        exit()

