import tkinter as tk
import random
from itertools import product
from crypto import *
from PIL import Image, ImageTk



CARD_NAMES = tuple(range(2, 11)) + ('jack', 'queen', 'king', 'ace')
SUIT_NAMES = 'diamond', 'club', 'heart', 'spade'
DECK_NAMES = tuple(product(CARD_NAMES, SUIT_NAMES))


def encrypt(deck, key, p):
    return [pow(card, key, p) for card in deck]


def cards_to_str(cards):
    return [DECK_NAMES[card - 2] for card in cards]


PLAYERS_COUNT = 10

if PLAYERS_COUNT > 23:
    print("Cannot have more than 23 players")
    exit(1)

deck = list(range(2, len(DECK_NAMES) + 2))
assert len(deck) == 52

p = generate_prime(10 ** 8, 10 ** 9)
serv_c, serv_d = gen_c_d(p - 1)

players_decryption_keys = []

for _ in range(PLAYERS_COUNT):
    player_c, player_d = gen_c_d(p - 1)
    deck = encrypt(deck, player_c, p)
    random.shuffle(deck)
    players_decryption_keys.append(player_d)

serv_deck = deck.copy()
serv_deck = encrypt(serv_deck, serv_c, p)
random.shuffle(serv_deck)
serv_decryption_key = serv_d

players_cards = []
for i in range(0, PLAYERS_COUNT * 2, 2):
    first_card = deck.pop()
    second_card = deck.pop()
    players_cards.append([first_card, second_card])


for i in range(len(players_cards)):
    for decryption_key in players_decryption_keys:
        players_cards[i] = encrypt(players_cards[i], decryption_key, p)


for decryption_key in players_decryption_keys:
    serv_deck = encrypt(serv_deck, decryption_key, p)

serv_deck = encrypt(serv_deck, serv_decryption_key, p)

for i, cards in enumerate(players_cards, 1):
    cards = cards_to_str(cards)
    print(f'Player {i} has cards', *cards)


root = tk.Tk()
root.title("Mental Poker")

window_height = 80 * PLAYERS_COUNT
root.geometry("800x" + str(window_height))


canvas = tk.Canvas(root, width=800, height=window_height, bg='green')
canvas.place(x=0, y=0)

card_images = []
for deck_name in DECK_NAMES:
    image = Image.open(f"poker_cards/{deck_name[0]}_of_{deck_name[1]}s.png")
    image = image.resize((60, 100))
    card_image = ImageTk.PhotoImage(image)

    card_images.append(card_image)

for i, cards in enumerate(players_cards):
    for j, card in enumerate(cards):
        image = card_images[card - 2]
        x = 100 + j * 50
        y = 20 + i * 60
        canvas.create_image(x, y, anchor='nw', image=image)
    canvas.create_text(50, y + 25, text=f"Player {i + 1}")

table = serv_deck[:5]

print('Table cards: ' + str(cards_to_str(table)))

for i, card in enumerate(table):
    image = card_images[card - 2]
    x = 300 + i * 50
    y = 200
    canvas.create_image(x, y, anchor='nw', image=image)



root.mainloop()
