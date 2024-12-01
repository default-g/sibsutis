import tkinter as tk
from tkinter import scrolledtext

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
    header = header_entry.get().split()
    non_term_inds = {char: i for i, char in enumerate(header)}
    automate.clear()
    try:
        for row in transitions_text.get("1.0", "end").split("\n"):
            if row.strip():
                row_data = row.split()
                if row_data[0] not in automate:
                    automate[row_data[0]] = {}
                automate[row_data[0]][row_data[1]] = row_data[2]
        output_text.delete(1.0, tk.END)
        output_text.insert(tk.END, "Автомат успешно обновлен!")
    except:
        output_text.delete(1.0, tk.END)
        output_text.insert(tk.END, "Произошла ошибка при обновлении автомата!")


def launch_automate(seq):
    i = 0
    output_text.delete(1.0, tk.END)
    if (state := start) not in automate:
        output_text.insert(tk.END, 'Ошибка! Неверно задано начальное состояние!')
        return
    for i, char in enumerate(seq):
        output_text.insert(tk.END, f'({state},{seq[i:]}) ├─ ')
        if (transition := automate.get(state)) is None:
            output_text.insert(tk.END, f'\nОшибка! Состояние "{state}" отсутствует в таблице! Переход невозможен!')
            return
        if (idx := non_term_inds.get(char)) is None:
            output_text.insert(tk.END, f'\nОшибка! В цепочке встречен посторонний символ "{char}", отсутствующий в алфавите!')
            return
        if (new_state := transition.get(char)) == None:
            output_text.insert(tk.END, f'\nОшибка: Отсутствует переход из состояния "{state}" по символу "{char}"')
            return
        state = new_state

    if state in end:
        output_text.insert(tk.END, f'({state},λ)\nАвтомат допускает цепочку {seq}')
    else:
        output_text.insert(tk.END, f'({state},{seq[i + 1:]})\nЦепочка кончилась, но автомат не пришёл в заключительное состояние!')

def on_submit():
    seq = seq_entry.get()
    launch_automate(seq)

def main():

    window = tk.Tk()
    window.title('Проверка цепочек по автомату')

    frame = tk.Frame(window)
    frame.pack(padx=10, pady=10)

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

    global header_entry
    header_label = tk.Label(definition_frame, text='Алфавит (через пробел):')
    header_label.grid(row=2, column=0, padx=5, pady=5)
    header_entry = tk.Entry(definition_frame)
    header_entry.grid(row=2, column=1, padx=5, pady=5)

    global transitions_text
    transitions_label = tk.Label(definition_frame, text='Переходы:')
    transitions_label.grid(row=3, column=0, padx=5, pady=5)
    transitions_text = scrolledtext.ScrolledText(definition_frame, width=20, height=5, wrap=tk.WORD)
    transitions_text.grid(row=3, column=1, padx=5, pady=5)

    update_button = tk.Button(definition_frame, text='Обновить автомат', command=update_automate)
    update_button.grid(row=4, columnspan=2, padx=5, pady=10)

    window.mainloop()

if __name__ == "__main__":
    main()
