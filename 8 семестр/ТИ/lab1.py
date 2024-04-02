from collections import Counter
import csv
import random
import re
from math import log2

def generate_file(filename: str, alphabet: dict[str, float], symbols_num: int) -> None:
    symbols = list(alphabet.keys())
    weights = list(alphabet.values())
    with open(filename, 'w') as f:
        for i in range(symbols_num):
            f.write(''.join(random.choices(symbols, weights)))
        f.close()

def preprocess_file(filename: str, lang: str) -> str:
    with open(filename, 'r', encoding='utf-8') as f:
        line = f.read()
        f.close()
    line = line.lower()
    if lang == "ru":
        line = re.sub(r'[^а-яА-Я0-9 ]', '', line)
    elif lang == "en":
        line = re.sub(r'[^a-zA-Z0-9 ]', '', line)
    else:
        exit(1)
    return line

def hartley_entropy(alphabet_size) -> float: # Максимально возможное значение энтропии
    return log2(alphabet_size)

def shannon_entropy(probabilities) -> float:
    return -sum(p * log2(p) for p in probabilities if p != 0)

def calc_entropy(line: str, symb_in_row: int):
    split_line = list(
        line[i: i + symb_in_row] for i in range(len(line) - symb_in_row + 1)
    )
    actual_probability = {k: v / len(line) for k, v in Counter(split_line).items()}
    result = shannon_entropy(actual_probability.values()) / symb_in_row

    return result, sorted(actual_probability.items())

def main() -> None:
    equal_prob = {'a': 0.25, 'b': 0.25, 'c': 0.25, 'd':0.25}
    diff_prob = {'a': 0.1, 'b': 0.1, 'c': 0.1, 'd':0.7}

    generate_file('./input/equal_prob.txt', equal_prob, 50000)
    generate_file('./input/diff_prob.txt', diff_prob, 50000)

    equal_prob_line = preprocess_file('./input/equal_prob.txt', 'en')
    diff_prob_line = preprocess_file('./input/diff_prob.txt', 'en')
    pre_gen_line = preprocess_file('./input/text.txt', 'ru')

    print(f"{len(equal_prob_line) = }\n{len(diff_prob_line) = }\n{len(pre_gen_line) = }\n")

    max_sequential_multiplicity = 3

    print("\n~~~equal_prob.txt~~~")
    for i in range(1, max_sequential_multiplicity + 1):
        entropy, actual_probabilities = calc_entropy(equal_prob_line, i)
        if i == 1:
            print(f"theoretical_probabilities = {equal_prob}")
            print(f"actual_probabilities = {actual_probabilities}")
            print(f"N = {len(actual_probabilities)}")
            print(f"H{i} = {hartley_entropy(len(actual_probabilities))}")
            continue
        print(f"H{i} = {entropy}")
    print(f"HT = {shannon_entropy(equal_prob.values())}")

    print("\n~~~diff_prob.txt~~~")
    for i in range(1, max_sequential_multiplicity + 1):
        entropy, actual_probabilities = calc_entropy(diff_prob_line, i)
        if i == 1:
            print(f"theoretical_probabilities = {diff_prob}")
            print(f"actual_probabilities = {actual_probabilities}")
            print(f"N = {len(actual_probabilities)}")
            print(f"H{i} = {hartley_entropy(len(actual_probabilities))}")
            continue
        print(f"H{i} = {entropy}")
    print(f"HT = {shannon_entropy(diff_prob.values())}")

    print("\n~~~text.txt~~~")
    for i in range(1, max_sequential_multiplicity + 1):
        entropy, actual_probabilities = calc_entropy(pre_gen_line, i)
        if i == 1:
            print(f"{actual_probabilities = }")
            print(f"N = {len(actual_probabilities)}")
            print(f"H{i} = {hartley_entropy(len(actual_probabilities))}")
            continue
        print(f"H{i} = {entropy}")
    print(f"HT = NaN")

    with open('./output/entropy_results.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['File name'] + [f'H{i}' for i in range(1, max_sequential_multiplicity)] + ['Max Possible Entropy', 'Theoretical Entropy'])


        for filename, line in [('./input/equal_prob.txt', equal_prob_line), ('./input/diff_prob.txt', diff_prob_line), ('./input/text.txt', pre_gen_line)]:
            row = []
            h0 = None
            for i in range(1, max_sequential_multiplicity):
                entropy, actual_probabilities = calc_entropy(line, i)
                row.append(entropy)
                if i == 1:
                    h0 = hartley_entropy(len(actual_probabilities))
                if i == max_sequential_multiplicity - 1:
                    row.append(h0)
            if filename == './input/equal_prob.txt':
                row.append(shannon_entropy(equal_prob.values()))
            elif filename == './input/diff_prob.txt':
                row.append(shannon_entropy(diff_prob.values()))
            else:
                row.append('NaN')
            writer.writerow([filename] + row)

if __name__ == '__main__':
    main()
