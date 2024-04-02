import math
import numpy as np
from lab1 import *
def shannon_encode(text: str) -> str:
    print("Shannon:")

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

    split_line = list(text[i: i + 1] for i in range(len(text)))

    probabilities = {k: v / len(split_line) for k, v in Counter(split_line).items()}
    probabilities = dict(
        sorted(probabilities.items(), key=lambda item: item[1], reverse=True)
    )


    code_length = [math.ceil(-math.log2(i)) for i in probabilities.values()]

    cumulative_probs = [float(0) for _ in range(len(probabilities))]
    for i in range(1, len(probabilities)):
        cumulative_probs[i] = cumulative_probs[i - 1] + list(probabilities.values())[i - 1]

    codes = list()
    for i in range(len(cumulative_probs)):
        codes.append(float_bin(cumulative_probs[i], code_length[i])[1:])
        print(f"{list(probabilities.keys())[i]}: {list(probabilities.values())[i]:.4f} - {codes[i]}")
    print()

    with open("./output/coded_shannon.txt", "w") as f:
        for i in text:
            index = list(probabilities.keys()).index(i)
            f.write(codes[index])
    with open("./output/coded_shannon.txt", "r") as f:
        text = f.readline()
    return text

def calcRedundantBits(m):
    for i in range(m):
        if 2**i >= m + i + 1:
            return i

def hamming_encode(file_path: str) -> str:
    def posRedundantBits(data, r):
        j = 0
        k = 1
        m = len(data)
        res = ''

        for i in range(1, m + r+1):
            if(i == 2**j):
                res = res + '0'
                j += 1
            else:
                res = res + data[-1 * k]
                k += 1

        return res[::-1]

    def calcParityBits(arr, r):
        n = len(arr)
        for i in range(r):
            val = 0
            for j in range(1, n + 1):
                if(j & (2**i) == (2**i)):
                    val = val ^ int(arr[-1 * j])

            arr = arr[:n-(2**i)] + str(val) + arr[n-(2**i)+1:]
        return arr

    with open(file_path, 'r') as file:
        data = file.read()

    m = len(data)
    r = calcRedundantBits(m)
    arr = posRedundantBits(data, r)
    arr = calcParityBits(arr, r)

    return arr

def hamming_decode(encoded_data: str) -> str:
    def detectError(arr, nr):
        n = len(arr)
        res = 0

        for i in range(nr):
            val = 0
            for j in range(1, n + 1):
                if j & (2**i) == (2**i):
                    val = val ^ int(arr[-1 * j])
            res = res + val*(10**i)

        return int(str(res), 2)

    m = len(encoded_data)
    r = calcRedundantBits(m)

    error_position = detectError(encoded_data, r)

    if error_position != 0:
        error_index = error_position - 1
        encoded_data = encoded_data[:error_index] + ('0' if encoded_data[error_index] == '1' else '1') + encoded_data[error_index+1:]

    decoded_data = ''
    j = 0
    for i in range(1, len(encoded_data) + 1):
        if i != 2**j:
            decoded_data += encoded_data[-i]
        else:
            j += 1

    return decoded_data[::-1]

def count_errors(original_data: str, decoded_data: str) -> int:
    errors = sum(bit1 != bit2 for bit1, bit2 in zip(original_data, decoded_data))
    return errors

def main():
    print("------ text.txt ------\n")
    input_text = preprocess_file('./input/text.txt', 'ru')
    encoded_text_shannon = shannon_encode(input_text)

    print("Hamming:")
    encoded_text_hamming = hamming_encode('./output/coded_shannon.txt')
    decoded_text = hamming_decode(encoded_text_hamming)

    if (encoded_text_shannon == decoded_text):
        print("SUCCESS: Original text equals decoded")
    else:
        print("ERROR: Original text doesn't equal decoded")

    probabilities = [0.0001, 0.001, 0.01, 0.1]
    print("Error probability\tError count")
    for probability in probabilities:
        encoded_copy = list(encoded_text_hamming)
        for i in range(len(encoded_copy)):
            if random.random() < probability:
                encoded_copy[i] = '0' if encoded_copy[i] == '1' else '1'
        corrupted_data = ''.join(encoded_copy)
        decoded_text = hamming_decode(corrupted_data)
        errors = count_errors(encoded_text_shannon, decoded_text)
        print(f"{probability}\t\t\t{errors}")

if __name__ == "__main__":
    main()
