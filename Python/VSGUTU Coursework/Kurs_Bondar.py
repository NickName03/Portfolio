import tkinter as tk
from tkinter import filedialog, messagebox, ttk
from tkinter import scrolledtext as st
import re


class Pharmacy:
    def __init__(self, firma, name, form, count, cost):
        self.firma = firma
        self.name = name
        self.form = form
        self.count = count
        self.cost = cost


class File:
    def file_reader(self, filepath):
        try:
            pharmacy_data = []
            with open(filepath, "r", encoding='utf-8') as f:
                for line in f:
                    parts = re.split(r"[:.;!?^%$*|\n\t<>,\s]+", line.strip())
                    if len(parts) > 4 and len(parts) < 7:
                        try:
                            firma = parts[0]
                            name = parts[1]
                            form = parts[2]
                            count = int(parts[3])
                            if len(parts) == 5:
                                cost = float(parts[4])
                            else:
                                cost = float(parts[4] + '.' + parts[5])
                            pharmacy_data.append(
                                Pharmacy(firma, name, form, count, cost)
                            )
                        except ValueError:
                            messagebox.showerror(
                                "Ошибка", f"Некорректные данные в строке: {line}")
                            return []
                    else:
                        messagebox.showerror(
                            "Ошибка", f"Некорректное количество данных в строке: {line}")
                        return []
                return pharmacy_data
        except FileNotFoundError:
            messagebox.showerror("Ошибка", f"Файл {filepath} не найден!")
            return []

    def save_to_file(self, filepath, pharmacy_data):
        with open(filepath, "w", encoding='utf-8') as f:
            for item in pharmacy_data:
                line = f"{item.firma:^20}{item.name:^20}\t{item.form:^15}\t{item.count:^6}\t{item.cost:^6.2f}\n"
                f.write(line)


class Menu:
    def __init__(self, master):
        # привязываем главное окно как переменную внутри класса, чтобы можно было
        # привязывать другие элементы к нему
        self.master = master
        # основные переменные
        self.pharmacy_data = None
        self.file = File()
        self.status = None
        # чисто графика
        self.font = ('Helvetica', 12)
        self.menubar = tk.Menu(master, font=self.font)  # сама плашка меню
        # переменная для подраздела
        self.filemenu = tk.Menu(self.menubar, tearoff=0)
        self.filtermenu = tk.Menu(self.menubar, tearoff=0)
        # определение подраздела
        self.menubar.add_cascade(
            label="Файл", menu=self.filemenu, font=self.font)
        self.menubar.add_cascade(
            label="Фильтрация", menu=self.filtermenu, state=tk.DISABLED, font=self.font)
        self.filemenu.add_command(  # подпункты "Файл"
            label="Открыть", font=self.font, command=lambda: self.open_file())
        self.filemenu.add_command(
            label="Изменить", font=self.font, command=lambda: self.edit_data(), state=tk.DISABLED)
        self.filemenu.add_command(
            label="Сохранить", font=self.font, command=lambda: self.save_data(), state=tk.DISABLED)
        self.filemenu.add_separator()
        self.filemenu.add_command(
            label="Выход", font=self.font, command=lambda: self.quit())
        self.filtermenu.add_command(  # подпункты "Фильтрация"
            label="По имени", font=self.font, command=lambda: self.filter_name())
        self.filtermenu.add_command(
            label="По форме выпуска", font=self.font, command=lambda: self.filter_form())
        self.filtermenu.add_command(
            label="По цене", font=self.font, command=lambda: self.filter_cost())
        self.master.config(menu=self.menubar)

    def quit(self):
        if self.status == "Edited":
            ans = messagebox.askquestion(
                "Внимание!", "У вас есть несохраненные данные. Сохранить?")
            if ans == "yes":
                self.save_data()
        self.master.quit()

    def entries_for_labels(self, window, labels):
        entries = []
        for i, label in enumerate(labels):
            tk.Label(window, text=label, font=self.font).grid(
                row=i, column=0, padx=5, pady=5)
            entry = tk.Entry(window, font=self.font)
            entry.grid(row=i, column=1, padx=5, pady=5)
            entries.append(entry)

        return entries

    def clear_interface(self):
        # Удаляем все элементы интерфейса, кроме menubar
        for widget in self.master.winfo_children():
            if widget != self.menubar:
                widget.destroy()

    def update_menu_state(self):
        if self.pharmacy_data:
            self.filemenu.entryconfig("Изменить", state=tk.NORMAL)
            self.filemenu.entryconfig("Сохранить", state=tk.NORMAL)
            self.menubar.entryconfig("Фильтрация", state=tk.NORMAL)
        else:
            self.filemenu.entryconfig("Изменить", state=tk.DISABLED)
            self.filemenu.entryconfig("Сохранить", state=tk.DISABLED)
            self.menubar.entryconfig("Фильтрация", state=tk.DISABLED)

    def autorization(self):
        self.master.withdraw()  # скрытие главного окна пока не выполнен вход
        new_window = tk.Toplevel(self.master)  # создание нового окна поверх
        new_window.title("Авторизация")
        new_window.geometry('300x250')
        labels = ["Логин", "Пароль"]
        entries = self.entries_for_labels(new_window, labels)
        entries[1].config(show="*")  # чтобы вводимый пароль был скрыт

        users = []
        # Считываем пользователей
        with open("Users\data.txt", "r", encoding="utf-8") as f:
            for line in f:
                users.append(line.strip().split(" "))

        def check_data():  # локальная функция для проверки данных
            login = entries[0].get()
            password = entries[1].get()
            # Проверяем каждого забитого пользователя
            for user in users:
                if user[0] == login:
                    if user[1] == password:  # если всё верно
                        self.master.deiconify()  # отображаем главное окно
                        new_window.destroy()  # удаляем окно авторизации
                        return
                    else:
                        messagebox.showwarning(
                            "Ошибка", "Неверный пароль!")
                        return
            messagebox.showwarning(
                "Ошибка", "Такого пользователя не существует!")

        tk.Button(new_window, text="Войти", command=check_data, font=self.font).grid(
            row=5, column=0, columnspan=2, padx=5, pady=5)

    def open_file(self):
        if self.status == "Edited":  # если пользователь уже изменил какой-то файл
            ans = messagebox.askquestion(
                "Внимание!", "У вас есть несохраненные данные. Сохранить?")
            if ans == "yes":
                self.save_data()
            else:
                self.status = None
        filepath = filedialog.askopenfilename(
            defaultextension=".txt",  # расширение файлов по умолчанию
            filetypes=[("Текстовые файлы", "*.txt"), ("Все файлы", "*.*")])
        if filepath:  # если файл выбрали
            self.master.title(f"Лекарства из файла {filepath}")
            self.clear_interface()  # очищаем, если что-то было в окне
            self.pharmacy_data = self.file.file_reader(
                filepath)  # считываем данные
            self.update_menu_state()  # меняем отображение пунктов меню, если они были заблокированы
            self.create_table()  # отображаем таблицу
        else:
            messagebox.showwarning("Ошибка", "Файл не выбран!")

    def edit_data(self):
        if self.pharmacy_data is None:
            messagebox.showwarning(
                "Предупреждение", "Сначала откройте файл!")
            self.open_file(master)
            return
        self.clear_interface()
        button_frame = tk.Frame(self.master, height=30)
        button_frame.pack(fill="x", anchor="nw", pady=10)
        # Добавляем кнопки "+" и "-"
        add_button = tk.Button(
            button_frame, text="Добавить", command=lambda: self.add_row(),
            width=12, fg="green", font=('Helvetica', 12, 'bold'))
        add_button.pack(side="left")
        remove_button = tk.Button(
            button_frame, text="Удалить", command=lambda: self.remove_row(),
            width=12, fg="red", font=('Helvetica', 12, 'bold'))
        remove_button.pack(side="left")

        # Создаем таблицу
        self.create_table()

    def save_data(self):
        if self.pharmacy_data is None or self.status == None:
            messagebox.showinfo(
                "Предупреждение", "Нет данных для сохранения!")
            self.open_file()
            return

        filepath = filedialog.asksaveasfilename(
            defaultextension=".txt",
            filetypes=[("Текстовые файлы", "*.txt"), ("Все файлы", "*.*")])
        if filepath:
            self.file.save_to_file(filepath, self.pharmacy_data)
            messagebox.showinfo(
                "Успех", f"Данные успешно сохранены в файл {filepath}!")
            self.status = None
        else:
            messagebox.showwarning("Ошибка", "Файл не выбран!")

    def filter_name(self):
        filter_value = tk.simpledialog.askstring(
            "Поиск по названию лекарства", "Введите название лекарства:")
        if filter_value is None:
            return
         # переменная флаг для хранения статуса поиска
        found = False
        # проходимся по всем записям
        for item in self.pharmacy_data:
            # если находим совпадение, то выводим
            if item.name == filter_value:
                info = (
                    f"Фирма: {item.firma}\n"
                    f"Название: {item.name}\n"
                    f"Форма выпуска: {item.form}\n"
                    f"Количество: {item.count}\n"
                    f"Цена: {item.cost}"
                )
                messagebox.showinfo("Успех", info)
                found = True

        if not found:
            messagebox.showwarning("Ошибка", "Такого лекарства нет!")

    def filter_window_close(self, window, title, pharmacy_data):
        self.pharmacy_data = pharmacy_data  # устанавливаем отформатированные данные
        self.master.title(title)
        self.clear_interface()
        self.create_table()
        self.status = "Edited"
        if window:  # удаляем окно, если оно было
            window.destroy()

    def filter_form(self):
        title = "Фильтрация по форме выпуска"
        forms = set()  # получаем уникальные значения формы выпуска
        for item in self.pharmacy_data:
            forms.add(item.form)
        new_window = tk.Toplevel(self.master)
        new_window.title(title)
        new_window.geometry('300x250')
        label = tk.Label(
            new_window, text="Выберите форму выпуска", font=self.font)
        combobox = ttk.Combobox(
            new_window, values=list(forms), state="readonly", font=self.font)
        label.pack(anchor="nw", padx=5, pady=5)
        combobox.pack(anchor="w", padx=5, pady=5)

        def show_filter():  # локальная функция
            selected_form = combobox.get()  # получаем выбранную форму
            form_list = [  # формируем лист с подходящими лекарствами по выбранной форме
                item for item in self.pharmacy_data if item.form == selected_form]
            self.filter_window_close(
                new_window, title, form_list)  # закрываем окно

        result = tk.Button(new_window, text="Применить",
                           command=show_filter, font=self.font)
        result.pack(anchor="s", padx=5, pady=5)

    def filter_cost(self):
        lower_bound = tk.simpledialog.askfloat(
            "Нижний порог цены", "От", initialvalue=0, parent=self.master)
        if lower_bound is None:  # если был отказ
            return
        if lower_bound < 0:
            messagebox.showwarning(
                "Ошибка", "Значение должно быть больше 0!")
            return
        upper_bound = tk.simpledialog.askfloat(
            "Верхний порог цены", "До", initialvalue=lower_bound + 1, parent=self.master)
        if upper_bound is None:  # если был отказ
            return
        if upper_bound < lower_bound:
            messagebox.showwarning(
                "Ошибка", "Значение должно быть больше нижнего порога цены!")
            return
        cost_list = [
            item for item in self.pharmacy_data if lower_bound <= item.cost <= upper_bound]
        if len(cost_list) == 0:
            messagebox.showinfo(
                "Внимание!", "Лекарств в заданном диапазоне не обнаружено!")
        else:
            self.filter_window_close(None, "Фильтрация по цене", cost_list)

    def create_table(self):
        columns = ("фирма", "название", "форма", "количество", "стоимость")
        # Настраиваем стиль для Treeview
        style = ttk.Style()
        # Устанавливаем размер шрифта для всего Treeview
        style.configure("mystyle.Treeview", font=("Helvetica", 16))
        # Устанавливаем размер шрифта для заголовков
        style.configure("mystyle.Treeview.Heading",
                        font=("Helvetica", 16, 'bold'))
        # Создаем фрейм для размещения Treeview и Scrollbar
        frame = tk.Frame(self.master)
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
            # Устанавливаем выравнивание по центру для каждого столбца
            self.tree.column(column, anchor="center")
        # Заполняем данными
        for i, item in enumerate(self.pharmacy_data):
            self.tree.insert("", "end", values=(
                item.firma, item.name, item.form, item.count, item.cost))
        # Привязываем Scrollbar к Treeview
        scrollbar.config(command=self.tree.yview)
        # Размещаем Treeview
        self.tree.pack(fill="both", expand=True)

    def add_row(self):
        new_window = tk.Toplevel(self.master)
        new_window.title("Добавить лекарство")
        new_window.geometry('300x250')

        labels = ["Фирма", "Название", "Форма", "Количество", "Стоимость"]
        entries = self.entries_for_labels(new_window, labels)

        def add_to_table():
            firma = entries[0].get()
            name = entries[1].get()
            form = entries[2].get()
            try:
                count = int(entries[3].get())
                cost = float(entries[4].get())
            except ValueError:
                messagebox.showerror(
                    "Ошибка", "Неверный формат количества или стоимости")
                return
            new_item = Pharmacy(firma, name, form, count, cost)
            self.pharmacy_data.append(new_item)
            self.tree.insert("", "end",
                             values=(
                                 new_item.firma,
                                 new_item.name,
                                 new_item.form,
                                 new_item.count,
                                 new_item.cost),
                             )
            self.status = "Edited"
            new_window.destroy()
        tk.Button(new_window, text="Добавить", command=add_to_table).grid(
            row=5, column=0, columnspan=2, padx=5, pady=5)

    def remove_row(self):
        selected_item = self.tree.selection()  # достаем выбранные строки
        if selected_item:  # если что-то выбрано
            # идем с конца выбранных строк, иначе будет проблема с индексами
            for item in selected_item[::-1]:
                # Корректируем индекс для удаления
                self.pharmacy_data.pop(int(item[1:], 16) - 1)
                self.tree.delete(item)
            self.status = "Edited"
        else:
            messagebox.showinfo(
                "Предупреждение", "Выберите строку для удаления")


if __name__ == "__main__":
    root = tk.Tk()
    root.title("Лекарства")
    root.geometry('1400x650')
    root.option_add('*Dialog.msg.font', 'Helvetica 14')
    menu = Menu(root)
    menu.autorization()

    root.mainloop()
