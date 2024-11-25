import tkinter as tk
from tkinter import filedialog, messagebox, ttk
import tkinter.scrolledtext as st
from tkinter import font as tkFont
import re


class College:
    def __init__(self, name: str, city: str, year: int, avg_score: float, it: bool):
        self.name = name
        self.city = city
        self.year = year
        self.avg_score = avg_score
        self.it = it


class Menu:
    def __init__(self, master):
        self.root = master
        self.table = tk.Frame(master)
        # список объектов
        self.data = []
        self.copy_data = []  # локальная копия для фильтрации
        # статичное меню
        self.menubar = tk.Menu(self.root)
        # переменная для подраздела
        self.filemenu = tk.Menu(self.menubar, tearoff=0, bg="#e3e1e1")
        # общий стиль
        self.font = ("Arial 12")
        self.style = ttk.Style()
        self.style.configure('TButton', font=self.font)  # для всех кнопок
        self.style.configure('TLabel', font=self.font)  # для надписей
        self.style.configure('TLabel', font=self.font)

    def auth_frame(self):
        # Получение данных зарегистрированных пользователей
        users = {}  # в словарь, чтобы было легче искать по логину
        # Читаем файл с данными пользователей
        with open("Users/data.txt", "r", encoding="utf-8") as f:
            for line in f:
                login, password = line.strip().split(" ")
                users[login] = password

        # Локальная функция активируемая нажатием на кнопку "Войти"
        def on_enter_click(login, password):
            # Проверка данных
            if login in users and users[login] == password:
                messagebox.showinfo("Успех", "Авторизация прошла успешно!")
                main_window.destroy()  # удаляем рабочую область
                self.config_menubar()
                self.filter_window()
            else:
                messagebox.showerror("Ошибка", "Неверный логин или пароль!")

        # локальная функция для создания фреймов с полями ввода. Меняется только название фрейма
        def create_LabelFrame(text):
            frame = tk.LabelFrame(
                auth_frame, font=self.font, text=text, bg="#e3e1e1", width=50, height=40)
            frame.pack(padx=15, pady=15, expand=True)
            entry = ttk.Entry(frame, width=16, font=self.font)
            entry.pack(side="left", padx=10, pady=10)
            return entry
        # Создает фрейм поверх главного окна
        main_window = tk.Frame(self.root, bg="green")
        main_window.pack(expand=True)  # растягиваем его по размеру гл. окна
        # фрейм с авторизацией
        auth_frame = tk.Frame(main_window, width=350, height=250, bg="#e3e1e1")
        auth_frame.pack(anchor="center")

        # Заголовок
        title_label = tk.Label(
            auth_frame, text="АВТОРИЗАЦИЯ", font=("Arial", 18, "bold"), bg="#e3e1e1")
        title_label.pack(anchor="n", pady=15)
        # Фрейм с логином
        login_entry = create_LabelFrame("Логин")
        # Фрейм с паролем
        password_entry = create_LabelFrame("Пароль")
        password_entry.config(show="x")
        # Кнопка "Вход"
        enter_button = ttk.Button(auth_frame, text="ВХОД", command=lambda: on_enter_click(
            login_entry.get(), password_entry.get()))
        enter_button.pack(pady=15)

    def config_menubar(self):
        # определение подраздела
        self.menubar.add_cascade(
            label="Файл",  font=self.font, menu=self.filemenu)
        self.filemenu.add_command(  # подпункты "Файл"
            label="Открыть",  font=self.font, command=lambda: self.open_file())
        self.filemenu.add_command(
            label="Сохранить",  font=self.font, command=lambda: self.save_data())
        self.filemenu.add_separator()
        self.filemenu.add_command(
            label="Выход", font=self.font, command=lambda: self.quit())
        self.root.config(menu=self.menubar)

    # универсальная функция для раскрытия/скрытия фреймов
    # parametr ('width' or 'height'), size, на который нужно развернуть фрейм
    # text отражает переключение режимов
    def show_frame(self, frame, parametr: str, size: int, button, text: list):
        if button['text'] == text[1]:
            frame.pack(pady=5)
            button['text'] = text[0]
            button[parametr] = size
        else:
            frame.pack_forget()
            button['text'] = text[1]
            button[parametr] = 4

    def result_filt(self, select_city, lower, upper, value):
        if len(select_city) == 0 and len(lower) == 0 and len(upper) == 0 and value == 0:
            self.copy_data = self.data
            self.create_table(self.copy_data)
            return
        found = False
        # предварительная проверка входящих данных
        for city in self.copy_data:
            if city.city == select_city:
                found = True
                break
        if len(select_city) == 0: # это нормально, что город не выбран
            found = True
        if found == False:
            messagebox.showerror(
                "Ошибка!", "Такого города нет!")
            return
        try:
            l = float(lower)
            u = float(upper)
        except ValueError:
            l = 3.0
            u = 5.0
        if l < 3.0:
            messagebox.showerror(
                "Ошибка!", "Проходной балл не может быть меньше 3!")
            return
        if u > 5.0:
            messagebox.showerror(
                "Ошибка!", "Проходной балл не может быть больше 5!")
            return
        if l > u:
            messagebox.showerror(
                "Ошибка!", "Некорректный ввод!")
            return
        if len(select_city) != 0:
            self.filt_city(select_city)
        if l != 3.0 or u != 5.0: # если не параметры по умолчанию
            self.filt_score(l, u)
        self.filt_it(value)
        self.create_table(self.copy_data)

    def filter_window(self):
        # область выбора фильтров
        filter_main = tk.Frame(self.root, width=300, bg="#e3e1e1")
        filter_main.pack(fill="both", side="right")
        filter_ = tk.Frame(filter_main, width=0)
        # раскрывающийся список
        # передаем через lambda функцию, чтобы можно было менять параметры вызвавшей кнопки внутри функции
        toggleButton = tk.Button(filter_main, bg="#c7c7c7", width=4, text="◁", command=lambda: self.show_frame(
            filter_, 'width', 26, toggleButton, ['▷', '◁']))
        toggleButton.pack()
        # всё связанное с городом
        filter_city = tk.LabelFrame(
            filter_, text="Введите\nгород", labelanchor="n", font=self.font, bg="#c7c7c7", width=50, height=40)
        filter_city.pack(fill="both", anchor="center")
        select_city = tk.Entry(filter_city, font=self.font)
        select_city.pack(fill="x")
        # все связанное с баллами
        filter_score = tk.LabelFrame(
            filter_, text="Средний балл", labelanchor="n", font=self.font, bg="#c7c7c7", width=50, height=40)
        filter_score.pack(fill="both", anchor="center", pady=10)
        lower_score = tk.LabelFrame(filter_score, text="От", font=self.font)
        lower_score.pack(fill="x", expand=True)
        lower_entry = tk.Entry(lower_score, font=self.font)
        lower_entry.pack(fill="x", expand=True,  pady=5)
        upper_score = tk.LabelFrame(filter_score, text="До", font=self.font)
        upper_score.pack(fill="x", expand=True)
        upper_entry = tk.Entry(upper_score, font=self.font)
        upper_entry.pack(fill="x", expand=True,  pady=5)
        # все связанное с направлением
        filter_it = tk.LabelFrame(
            filter_, text="Наличие IT", labelanchor="n", font=self.font, bg="#c7c7c7", width=50, height=40)
        enabled = tk.IntVar(value=0)
        it = tk.Checkbutton(filter_it, text="Есть",
                            font=self.font, variable=enabled)
        it.pack(fill='x', anchor="center")
        filter_it.pack(fill="x", anchor="center", pady=10)
        resutl = tk.Button(filter_, text="Применить", bg="#c7c7c7", font=self.font, command=lambda: self.result_filt(
            select_city.get(), lower_entry.get(), upper_entry.get(), enabled.get()))
        resutl.pack(fill='x', pady=10)

    def quit(self):
        ans = messagebox.askquestion(
            "Внимание!", "Вы уверены, что хотите выйти?")
        if ans == "yes":
            self.root.quit()

    def file_reader(self, filepath):
        try:
            data = []  # сначала создаем локальный лист
            with open(filepath, "r", encoding='utf-8') as f:
                for line in f:
                    # Разделяем строку
                    parts = re.split(r"[:.;!?^%$*|\n\t<>,\s]+", line.strip())
                    if parts[-1] != "Да" and parts[-1] != "Нет":
                        messagebox.showerror(
                            "Ошибка", f"Строка {line} не соответствует формату")
                        return
                    # Собираем название колледжа, если оно состоит из нескольких слов
                    name = " ".join(parts[0:-5])
                    city = parts[-5]
                    year = int(parts[-4])
                    avg_score = float(parts[-3] + '.' + parts[-2])
                    # Преобразуем "+" в True и "-" в False, эквивалентно коду
                    # if parts[-1] == "Да": it == True else: it = False
                    it = parts[-1] == "Да"
                    data.append(College(name, city, year, avg_score, it))
            self.data = data  # если все успешно, то записываем
            self.copy_data = self.data
        except FileNotFoundError:
            messagebox.showerror("Ошибка", f"Файл {filepath} не найден!")
            return

    def file_print(self, filepath):
        with open(filepath, "w", encoding='utf-8') as f:
            for college in self.copy_data:
                if college.it == True:
                    it = "Да"
                else:
                    it = "Нет"
                line = f"{college.name:<60} {college.city:<20} {college.year:^4} {college.avg_score:<1.2} {it}\n"
                f.write(line)

    def open_file(self):
        filepath = filedialog.askopenfilename(
            defaultextension=".txt",  # расширение файлов по умолчанию
            filetypes=[("Текстовые файлы", "*.txt"), ("Все файлы", "*.*")])
        if filepath:  # если файл выбрали
            self.file_reader(filepath)
            self.create_table(self.copy_data)  # отображаем таблицу
        else:
            messagebox.showwarning("Ошибка", "Файл не выбран!")

    def save_data(self):
        filepath = filedialog.asksaveasfilename(
            defaultextension=".txt",
            filetypes=[("Текстовые файлы", "*.txt"), ("Все файлы", "*.*")])
        if filepath:
            self.file_print(filepath)
            messagebox.showinfo(
                "Готово", f"Данные успешно сохранены в файл {filepath}!")
        else:
            messagebox.showwarning("Ошибка", "Файл не выбран!")

    def filt_city(self, select_city):
        local = [
            college for college in self.copy_data if college.city == select_city]
        self.copy_data = local

    def filt_score(self, lower, upper):
        # Фильтрация по диапазону среднего балла
        local = [
            college for college in self.copy_data
            if lower <= college.avg_score <= upper
        ]
        self.copy_data = local

    def filt_it(self, value):
        # Фильтрация по наличию/отсутствию направления "IT"
        local = [
            college for college in self.copy_data
            if (value == 1 and college.it) or (value == 0 and not college.it)
        ]
        self.copy_data = local

    def create_table(self, data):
        # очищаем область с таблицей ,если в ней чо-то было
        for widget in self.table.winfo_children():
            widget.destroy()
        # область с таблицей
        self.table.pack(fill="both", expand=True, side="left")
        columns = ("Название", "Город",
                   "Год", "Балл", "IT")
        # Настраиваем стиль для Treeview
        style = ttk.Style()
        # Устанавливаем размер шрифта для всего Treeview
        style.configure("mystyle.Treeview", font=self.font)
        # Устанавливаем размер шрифта для заголовков
        style.configure("mystyle.Treeview.Heading", font=("Arial", 16, 'bold'))
        # Создаем фрейм для размещения Treeview и Scrollbar
        frame = tk.Frame(self.table)
        frame.pack(fill="both", expand=True, pady=5)

        # Создаем Scrollbar
        scrollbar = tk.Scrollbar(frame)
        scrollbar.pack(side="right", fill="y")

        # Создаем Treeview
        self.tree = ttk.Treeview(
            frame, columns=columns, show="headings", yscrollcommand=scrollbar.set, style="mystyle.Treeview"
        )
        # Добавляем заголовки
        for column in columns:
            self.tree.heading(column, text=column)
            # для всех кроме первого столбца
            if column != columns[0] and column != columns[1]:
                self.tree.column(column, minwidth=0, width=60, stretch=False)
        # Заполняем данными
        for i, college in enumerate(data):
            it_status = "Нет"
            if college.it:
                it_status = "Есть"
            self.tree.insert("", "end", values=(
                college.name, college.city, college.year, college.avg_score, it_status))
        # Привязываем Scrollbar к Treeview
        scrollbar.config(command=self.tree.yview)
        # Размещаем Treeview
        self.tree.pack(fill="both", expand=True)


if __name__ == "__main__":
    root = tk.Tk()
    root.title("Колледжи")
    root.geometry('1440x680')
    root.resizable(False, True)
    menu = Menu(root)
    menu.auth_frame()
    root.mainloop()
