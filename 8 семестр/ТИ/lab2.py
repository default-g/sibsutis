import heapq
from math import ceil
from lab1 import *

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq


def huffman_encode(line: str) -> float:
    print("\nHuffman:\n")

    def build_huffman_tree(text):
        char_freq = Counter(text)
        heap = [Node(char, freq) for char, freq in char_freq.items()]
        heapq.heapify(heap)

        while len(heap) > 1:
            left = heapq.heappop(heap)
            right = heapq.heappop(heap)
            merged = Node(None, left.freq + right.freq)
            merged.left = left # type:ignore
            merged.right = right # type:ignore
            heapq.heappush(heap, merged)

        return heap[0]

    def build_huffman_codes(node, prefix="", codes={}):
        if node:
            if node.char is not None:
                codes[node.char] = prefix
            build_huffman_codes(node.left, prefix + "0", codes)
            build_huffman_codes(node.right, prefix + "1", codes)

    split_line = list(line[i: i + 1] for i in range(len(line)))
    probabilities = {k: v / len(split_line) for k, v in Counter(split_line).items()}
    probabilities = dict(
        sorted(probabilities.items(), key=lambda item: item[1], reverse=True)
    )

    root = build_huffman_tree(line)
    codes = {}
    build_huffman_codes(root, "", codes)

    for i in probabilities.keys():
        print( f"{i}: {probabilities[i]:.4f} - {codes[i]}")
    l_average = sum(probabilities[i] * len(codes[i]) for i in probabilities.keys())
    print("L avg = ", l_average)

    print("coded_huffman.txt")
    with open("./output/coded_huffman.txt", "w") as f:
        for i in line:
            f.write(codes[i])

    with open("./output/coded_huffman.txt", "r") as f:
        text = f.readline()
    for i in range(1, 4):
        print(f'H{i} = ', calc_entropy(text, i))
    return l_average

def shannon_encode(line: str) -> float:
    print("\nShannon:\n")
    def decimal_converter(num):
        if num == 0.0:
            return 0.0
        while num > 1:
            num /= 10
        return num

    def float_bin(number: float, places: int):
        whole, dec = str(number).split(".")
        whole = int(whole)
        dec = int(dec)
        res = bin(whole).strip("0b") + "."
        for x in range(places):
            whole, dec = str((decimal_converter(dec)) * 2).split(".")
            dec = int(dec)
            res += whole
        return res

    split_line = list(line[i: i + 1] for i in range(len(line)))

    probabilities = {k: v / len(split_line) for k, v in Counter(split_line).items()}
    probabilities = dict(
        sorted(probabilities.items(), key=lambda item: item[1], reverse=True)
    )
    # print(probabilities)

    code_length = [ceil(-log2(i)) for i in probabilities.values()]
    # print(code_length)

    cumulative_probs = [float(0) for _ in range(len(probabilities))]
    for i in range(1, len(probabilities)):
        cumulative_probs[i] = (
            cumulative_probs[i - 1] + list(probabilities.values())[i - 1]
        )
    # print(cumulative_probs)

    codes = list()
    for i in range(len(cumulative_probs)):
        codes.append(float_bin(cumulative_probs[i], code_length[i])[1:])
        print(
            f"{list(probabilities.keys())[i]}: {list(probabilities.values())[i]:.4f} - {codes[i]}"
        )

    # print(codes)
    l_average = sum(
        list(probabilities.values())[i] * code_length[i]
        for i in range(len(probabilities.items()))
    )
    print("L avg = ", l_average)

    print("coded_shannon.txt")
    with open("./output/coded_shannon.txt", "w") as f:
        for i in line:
            index = list(probabilities.keys()).index(i)
            f.write(codes[index])

    with open("./output/coded_shannon.txt", "r") as f:
        text = f.readline()
    for i in range(1, 4):
        print(f'H{i} = ', calc_entropy(text, i))
    return l_average

def main():

    print("\n----- Equal probs -----")
    input_text = preprocess_file('./input/equal_prob.txt', 'en')

    orig_entropy = calc_entropy(input_text, 1)
    print(f"H = {orig_entropy[0]}\np = {orig_entropy[1]}")

    l_avg_huf = huffman_encode(input_text)
    l_avg_shan = shannon_encode(input_text)
    print(f"\nr huffman = {l_avg_huf - orig_entropy[0]}\nr shannon = {l_avg_shan - orig_entropy[0]}")


    print("\n----- Different probs -----")
    input_text = preprocess_file('./input/diff_prob.txt', 'en')

    orig_entropy = calc_entropy(input_text, 1)
    print(f"H = {orig_entropy[0]}\np = {orig_entropy[1]}")

    l_avg_huf = huffman_encode(input_text)
    l_avg_shan = shannon_encode(input_text)
    print(f"\nr huffman = {l_avg_huf - orig_entropy[0]}\nr shannon = {l_avg_shan - orig_entropy[0]}")


    print("\n----- text.txt -----")
    input_text = preprocess_file('./input/text.txt', 'ru')
    orig_entropy = calc_entropy(input_text, 1)
    print(f"H = {orig_entropy[0]}\np = {orig_entropy[1]}")

    l_avg_huf = huffman_encode(input_text)
    l_avg_shan = shannon_encode(input_text)
    print(f"\nr huffman = {l_avg_huf - orig_entropy[0]}\nr shannon = {l_avg_shan - orig_entropy[0]}")


if __name__ == "__main__":
    main()
