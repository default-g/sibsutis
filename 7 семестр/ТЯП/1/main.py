#!/usr/bin/env python3

import json
import typing
from dataclasses import dataclass
import tkinter as tk
from tkinter import filedialog, messagebox

from graphical_tree import GraphicalTree, Vertex
from grammar_editor import GrammarEditor

ans = []
G = None


@dataclass(frozen=True)
class Grammar:
    VT: typing.List[str]
    VN: typing.List[str]
    P: typing.Dict[str, typing.List[str]]
    S: str


def open_file():
    file_path = filedialog.askopenfilename(filetypes=(("JSON Files", "*.json"),))
    grammar_file_entry.delete(0, tk.END)
    grammar_file_entry.insert(tk.END, file_path)

def show_grammar_window():
    new_window = tk.Tk()
    new_window.title("Генератор цепочек")
    grammar_editor = GrammarEditor(new_window)


def generate_sequences():
    grammar_file = grammar_file_entry.get()
    range_from = range_from_entry.get()
    range_to = range_to_entry.get()
    global G
    try:
        with open(grammar_file) as f:
            G = Grammar(**json.load(f))
    except (json.JSONDecodeError, TypeError):
        messagebox.showerror("Error", "Файл грамматики некоректен")
        return


    if int(range_from) > int(range_to):
        range_from, range_to = range_to, range_from

    stack = [([], G.S)]
    was_in_stack = set()
    counter = 1
    ans.clear()
    output_text.delete("1.0", "end")
    try:
        while stack:
            prev, sequence = stack.pop()
            prev = prev.copy()
            prev.append(sequence)
            if sequence in was_in_stack:
                continue
            was_in_stack.add(sequence)
            only_term = True
            for i, symbol in enumerate(sequence):
                if symbol in G.VN:
                    only_term = False
                    for elem in G.P[symbol]:
                        scopy = sequence[:i] + elem + sequence[i + 1:]
                        if len(scopy) <= int(range_to) + 3:
                            stack.append((prev, scopy))
            if only_term and int(range_from) <= len(sequence) <= int(range_to):
                ans.append(prev)
                output_text.insert(tk.END, f"[{counter}] {'->'.join(prev) if sequence else 'λ'}\n")
                counter += 1

    except KeyError:
        messagebox.showerror("Error", "Ошибка. Вероятнее всего грамматика задана некорректно!")
        return


def select_sequence():
    choice = sequence_entry.get()
    if not choice.isdigit() or not (1 <= int(choice) <= len(ans)):
        messagebox.showerror("Error", "Введите натуральное число, не превышающее количества цепочек")
        return

    chosen_ans = ans[int(choice) - 1]

    def get_changes(current, next):
        if len(next) < len(current):
            return "λ"
        for i, ch in enumerate(current[::-1]):
            i = len(current) - i - 1
            if ch in G.VN:
                return next[i: i + len(next) - len(current) + 1]

    def get_right_vertex(tree):
        if not tree.children and tree.data in G.VN:
            return tree
        for vert in tree.children[::-1]:
            v = get_right_vertex(vert)
            if v:
                return v

    tree = Vertex(chosen_ans[0])
    for curr, next in zip(chosen_ans, chosen_ans[1:]):
        changes = get_changes(curr, next)
        v = get_right_vertex(tree)
        v.children = list(map(Vertex, changes))

    gt = GraphicalTree(tree)
    gt.start()


# GUI setup
root = tk.Tk()
root.title("Генератор цепочек")

# Grammar structure
grammar_frame = tk.Frame(root)
grammar_frame.pack()

# Grammar file selection
grammar_file_label = tk.Label(root, text="Файл:")
grammar_file_label.pack()
grammar_file_entry = tk.Entry(root)
grammar_file_entry.pack(side=tk.LEFT)
grammar_file_button = tk.Button(root, text="Открыть", command=open_file)
grammar_file_button.pack(side=tk.LEFT)


grammar_file_button = tk.Button(root, text="Генератор файла", command=show_grammar_window)
grammar_file_button.pack(side=tk.LEFT)

# Range selection
range_from_entry = tk.Entry(root, width=5)
range_from_entry.pack(side=tk.LEFT)
range_to_entry = tk.Entry(root, width=5)
range_to_entry.pack(side=tk.LEFT)

# Generate button
generate_button = tk.Button(root, text="Сгенерировать", command=generate_sequences)
generate_button.pack()

# Output text area
output_text = tk.Text(root, width=40, height=10)
output_text.pack()

# Sequence selection
sequence_label = tk.Label(root, text="Select Sequence:")
sequence_label.pack()
sequence_entry = tk.Entry(root, width=5)
sequence_entry.pack(side=tk.LEFT)
select_button = tk.Button(root, text="Select", command=select_sequence)
select_button.pack()

root.mainloop()
