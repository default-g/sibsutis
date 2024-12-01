import tkinter as tk
from tkinter import scrolledtext
import re

automate = {}
start = ''
end = set()
header = []
non_term_inds = {}
seq_entry = None
output_text = None
start_entry = None
end_entry = None
header_entry = None


def update_automate():
    global automate, start, end, header, non_term_inds
    start = start_entry.get()
    end = set(end_entry.get().split())
    # header = header_entry.get().split()
    non_term_inds = {char: i for i, char in enumerate(header)}
    automate.clear()
    try:
        for row in transitions_text.get("1.0", "end").split("\n"):
            row = str(row).strip()
            match = re.fullmatch(r"\s*\(\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*\)\s*=\s*\(\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*\)\s*", row)
            if not match:
                continue
            state, char, stackchar, newstate, newstack, newchar = match.groups()

            if state not in automate:
                automate[state] = {}
            if char not in automate[state]:
                automate[state][char] = {}
            if stackchar not in automate[state][char]:
                automate[state][char][stackchar] = (newstate, newstack, newchar)

        output_text.delete(1.0, tk.END)
        output_text.insert(tk.END, "Автомат успешно обновлен!")
    except Exception as e:
        output_text.delete(1.0, tk.END)
        output_text.insert(tk.END, "Произошла ошибка при обновлении автомата!")

def launch_automate(seq):
    i = 0
    stack = ['Z']
    output_text.delete(1.0, tk.END)
    translated = ''

    if (state := start) not in automate:
        output_text.insert(tk.END, 'Ошибка! Неверно задано начальное состояние! Оно отсутствует в таблице!')
        return
    while stack:
        char = seq[i] if i < len(seq) else '_'

        output_text.insert(tk.END, f'({state}, {seq[i:] if len(seq[i:]) > 0 else "λ"}, {"".join(reversed(stack))}, {translated if len(translated) > 0 else "λ"}) ├─ ')

        if (transition1 := automate.get(state)) is None:
            output_text.insert(tk.END, f'\nОшибка! Состояние "{state}" отсутствует в таблице! Переход невозможен!')
            return

        if (transition2 := transition1.get(char)) is None:
            output_text.insert(tk.END, f'\nОшибка: Отсутствует переход из состояния "{state}" с символом {char} в стеке')
            return

        if (transition3 := transition2.get(stack[-1])) is None:
            output_text.insert(tk.END, f'\nОшибка: Отсутствует переход из состояния "{state}" с символом {char} в цепочке с символом {stack[-1]} в стеке')
            return

        i += 1
        new_state, stack_operation, new_char = transition3
        if new_char != '_':
            translated += new_char

        state = new_state
        if len(stack_operation) == 1 and stack[-1] == stack_operation:
            continue

        if stack_operation == '_':
            stack.pop()
        else:
            stack.pop()
            stack.extend(list(reversed(stack_operation)))

    if state in end and i >= len(seq):
        output_text.insert(tk.END, '\nАвтомат допускает цепочку', seq)
    elif state not in end:
        output_text.insert(tk.END, '\nСтек пуст, но автомат не пришёл в заключительное состояние!')
    else:
        output_text.insert(tk.END, '\nСтек пуст, автомат в заключительном состоянии, но цепочка не кончилась!')


def on_submit():
    seq = seq_entry.get()
    launch_automate(seq)

def main():

    window = tk.Tk()
    window.title('Проверка цепочек по автомату')

    frame = tk.Frame(window)
    frame.pack(padx=14, pady=10)

    seq_label = tk.Label(frame, text='Введите цепочку:')
    seq_label.grid(row=0, column=0, padx=5, pady=5)

    global seq_entry
    seq_entry = tk.Entry(frame)
    seq_entry.grid(row=0, column=1, padx=5, pady=5)

    submit_button = tk.Button(frame, text='Проверить', command=on_submit)
    submit_button.grid(row=0, column=2, padx=5, pady=5)

    global output_text
    output_text = scrolledtext.ScrolledText(frame, width=40, height=10, wrap=tk.WORD)
    output_text.grid(row=1, columnspan=3, padx=5, pady=5)

    # Create input fields for automaton definition
    definition_frame = tk.Frame(frame, padx=10, pady=10)
    definition_frame.grid(row=2, columnspan=3)

    global start_entry
    start_label = tk.Label(definition_frame, text='Начальное состояние:')
    start_label.grid(row=0, column=0, padx=5, pady=5)
    start_entry = tk.Entry(definition_frame)
    start_entry.grid(row=0, column=1, padx=5, pady=5)

    global end_entry
    end_label = tk.Label(definition_frame, text='Конечное состояние:')
    end_label.grid(row=1, column=0, padx=5, pady=5)
    end_entry = tk.Entry(definition_frame)
    end_entry.grid(row=1, column=1, padx=5, pady=5)

    # global header_entry
    # header_label = tk.Label(definition_frame, text='Алфавит (через пробел):')
    # header_label.grid(row=2, column=0, padx=5, pady=5)
    # header_entry = tk.Entry(definition_frame)
    # header_entry.grid(row=2, column=1, padx=5, pady=5)

    global transitions_text
    transitions_label = tk.Label(definition_frame, text='Переходы:')
    transitions_label.grid(row=3, column=0, padx=5, pady=5)
    transitions_text = scrolledtext.ScrolledText(definition_frame, width=40, height=20, wrap=tk.WORD)
    transitions_text.grid(row=3, column=1, padx=15, pady=5)

    update_button = tk.Button(definition_frame, text='Обновить автомат', command=update_automate)
    update_button.grid(row=4, columnspan=2, padx=5, pady=10)

    window.mainloop()

if __name__ == "__main__":
    main()

