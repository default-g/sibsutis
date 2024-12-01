import tkinter as tk
from tkinter import messagebox
from tkinter import filedialog
from tkinter import ttk
from utils.regular_expression import Regex
import tkinter as tk
from tkinter import messagebox

from utils.regular_expression import Regex


class RegexGeneratorGUI:

    def __init__(self):

        self.cfg = None
        self.regex = None

        self.root = tk.Tk()
        self.root.title('Регулярное выражение в КС грамматику')
        self.root.resizable(False, False)


        # Create labels for entries
        self.regex_label = tk.Label(self.root, text="Регулярное выражение:")
        self.min_length_label = tk.Label(self.root, text="Минимальная длина:")
        self.max_length_label = tk.Label(self.root, text="Максимальная длина:")

        # Create the input fields for regex and word lengths
        self.regex_entry = tk.Entry(self.root, width=100)
        self.min_length_entry = tk.Entry(self.root)
        self.max_length_entry = tk.Entry(self.root)

        # Create separate text fields for cfg and generated words
        self.cfg_text = tk.Text(self.root, width=50, height=10)
        self.generated_words_text = tk.Text(self.root, width=50, height=10)
        self.generated_words_text2 = tk.Text(self.root, height=10)
        self.generated_words_text.config(state='disabled')
        self.cfg_text.config(state='disabled')

        # Create buttons for generating context-free grammar and words
        self.generate_cfg_button = tk.Button(
            self.root, text='Сформировать КС грамматику', command=self.generate_cfg
        )
        self.generate_words_button = tk.Button(
            self.root, text='Сформировать цепочки', command=self.generate_words
        )

        self.upload_regex_button = tk.Button(
            self.root, text='Загрузить регулярное выражение', command=self.upload_regex
        )

        self.save_word_button = tk.Button(
            self.root, text='Сохранить цепочки', command=self.save_chains
        )

        self.author_button = tk.Button(
            self.root, text='Автор', command=self.author
        )

        self.task_button = tk.Button(
            self.root, text='Задание', command=self.task
        )

        # Place labels and entry fields on the window
        self.regex_label.grid(row=0, column=0, padx=5, pady=5, sticky=tk.W)
        self.regex_entry.grid(row=0, column=1, columnspan=10, padx=5, pady=5)
        self.min_length_label.grid(row=1, column=0, padx=5, pady=5, sticky=tk.W)
        self.min_length_entry.grid(row=1, column=1, padx=5, pady=5)
        self.max_length_label.grid(row=1, column=2, padx=5, pady=5, sticky=tk.W)

        self.max_length_entry.grid(row=1, column=3, padx=5, pady=5)
        self.cfg_label = tk.Label(self.root, text="КС грамматика:")
        self.generated_words_label = tk.Label(self.root, text="Сгенерированные цепочки по КС грамматике:")
        self.generated_words_label2 = tk.Label(self.root, text="Сгенерированные цепочки по регулярному выражению:")

        self.separator = ttk.Separator(self.root, orient='vertical')
        self.separator2 = ttk.Separator(self.root, orient='vertical')

        self.cfg_label.grid(row=2, column=0, padx=5, pady=5, sticky=tk.W)
        self.cfg_text.grid(row=2, column=1, columnspan=10, padx=5, pady=5, sticky="nsew")

        self.generated_words_label.grid(row=3, column=0, padx=5, pady=5, sticky=tk.W)
        self.generated_words_label2.grid(row=4, column=0, padx=5, pady=5, sticky=tk.W)
        self.generated_words_text.grid(row=3, column=1, columnspan=10, padx=5, pady=5, sticky="ew")
        self.generated_words_text2.grid(row=4, column=1, columnspan=10, padx=5, pady=5, sticky="ew")

        self.generated_words_text.config(state='disabled')
        self.generated_words_text2.config(state='disabled')



        self.generate_cfg_button.grid(row=5, column=0, padx=5, pady=5)
        self.generate_words_button.grid(row=5, column=1, padx=5, pady=5)
        self.upload_regex_button.grid(row=5, column=3, padx=5, pady=5, sticky='nws')
        self.save_word_button.grid(row=5, column=4, padx=5, pady=5)
        self.separator2.grid(row=5, column=5, padx=0, pady=5, sticky='ns')
        self.author_button.grid(row=5, column=6, padx=5, pady=5)
        self.task_button.grid(row=5, column=7, padx=5, pady=5, sticky='nwe')

        self.root.mainloop()


    def generate_cfg(self):
        try:
            self.cfg_text.config(state='normal')
            self.generated_words_text.config(state='normal')
            self.generated_words_text2.config(state='normal')


            self.cfg_text.delete(1.0, tk.END)
            self.generated_words_text.delete(1.0, tk.END)
            self.generated_words_text2.delete(1.0, tk.END)

            regex = self.regex_entry.get()
            if not regex:
                messagebox.showerror('Ошибка', 'Не указано регулярное выражение!')

            self.regex = Regex(regex)
            self.cfg = Regex(regex).to_cfg()

            formatted_cfg_dict = {}
            for production in self.cfg.productions:
                variable = production.head.to_text()

                if variable not in formatted_cfg_dict.keys():
                    formatted_cfg_dict[variable] = []

                if len(production.body) > 0:
                    formatted_cfg_dict[variable].append(
                        "".join([x.to_text() for x in production.body])
                    )
                else:
                    formatted_cfg_dict[variable].append("λ")

            output_strings = []
            for key, value in formatted_cfg_dict.items():
                output_strings.append(key + " -> " + "|".join(value))

            formatted_cfg_string = "\n".join(output_strings)

            self.cfg_text.insert(2.0, formatted_cfg_string)

            self.cfg_text.config(state='disabled')
            self.generated_words_text.config(state='disabled')
            self.generated_words_text2.config(state='disabled')

        except:
            messagebox.showerror('Ошибка', 'Регулярное выражение некорректно! Повторите ввод')


    def generate_words(self):
            self.generated_words_text.config(state='normal')
            self.generated_words_text.delete(1.0, tk.END)
            self.generated_words_text2.config(state='normal')
            self.generated_words_text2.delete(1.0, tk.END)

            if not self.cfg:
                messagebox.showerror('Ошибка', 'Не указана КС грамматика!')
                return
            try:
                min_length = int(self.min_length_entry.get())
                if min_length < 0:
                    raise 'Error'
            except:
                messagebox.showerror('Ошибка', 'Минимальная длина некорректна!')
                return

            try:
                max_length = int(self.max_length_entry.get())
                if max_length < 0 or max_length < min_length:
                    raise 'Error'
            except:
                messagebox.showerror('Ошибка', 'Максимальная длина некорректна!')
                return
            cfg_words = []
            for word in self.cfg.get_words(max_length):
                if len(word) < min_length:
                    continue
                word = "".join([x.to_text() for x in word])
                cfg_words.append(word)

                self.generated_words_text.insert(tk.END, f"{word}\n")

            regex_words = []
            for word in self.regex.generate_words(min_length, max_length):
                regex_words.append(word)
                self.generated_words_text2.insert(tk.END, f"{word}\n")

            self.generated_words_text.config(state='disabled')
            self.generated_words_text2.config(state='disabled')

            if self.compare_chains(cfg_words, regex_words):
                messagebox.showinfo('Результат', 'КС и регулярное выражение совпадают!')


    def upload_regex(self):
        root = tk.Tk()
        root.withdraw()
        self.regex_entry.delete(0, tk.END)

        file_path = filedialog.askopenfilename()
        if file_path:
            with open(file_path, 'r') as file:
                regex = file.read()
            self.regex_entry.insert(0, regex)
        else:
            return None

    def save_chains(self):
        root = tk.Tk()
        root.withdraw()
        words = self.generated_words_text.get(1.0, tk.END)

        file_path = filedialog.asksaveasfilename(defaultextension=".txt")
        if file_path:
            with open(file_path, 'w') as file:
                file.write(words)
        else:
            return None

    def author(self):
        messagebox.showinfo('Автор', 'ИП-014 Обухов А.И.')

    def task(self):
        task_string = """Написать программу, которая по заданному регулярному выражению построит эквивалентную грамматику (по желанию разработчика – грамматика может быть контекстно-свободной или регулярной).
Программа должна сгенерировать по построенной грамматике и регулярному выражению множества всех цепочек в указанном диапазоне длин,
проверить их на совпадение. Процесс построения цепочек отображать на экране.
Для подтверждения корректности выполняемых действий предусмотреть возможность корректировки любого из построенных множеств пользователем (изменение цепочки, добавление, удаление…).
При обнаружении несовпадения в элементах множеств должна выдаваться диагностика различий – где именно несовпадения и в чём они состоят."""

        messagebox.showinfo('Задание', task_string)


    def compare_chains(self, a, b):
        return set(a) == set(b)


if __name__ == '__main__':
    window = RegexGeneratorGUI()
