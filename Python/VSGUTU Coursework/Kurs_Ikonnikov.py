import tkinter as tk
from tkinter import ttk, messagebox, filedialog
import os
import re


class Teacher:
    def __init__(self, department, position, degree, experience, subject):
        self.department = department
        self.position = position
        self.degree = degree
        self.experience = experience
        self.subject = subject


class Data:
    def __init__(self):
        self.input_teachers = []
        self.filt_teachers = []

    def load_data(self, file_path):
        self.input_teachers = []
        with open(file_path, 'r', encoding='utf-8') as file:
            for line in file:
                buf = re.split(r'[^a-zA-Zа-яА-Я0-9\s]+', line.strip())
                if len(buf) == 5:
                    teacher = Teacher(*buf)
                    self.input_teachers.append(teacher)
        self.filt_teachers = self.input_teachers

    def save_data(self, file_path):
        with open(file_path, 'w', encoding='utf-8') as file:
            for teacher in self.filt_teachers:
                file.write(
                    f"{teacher.department:<40} | {teacher.position:<20} | {teacher.degree:<20} | "
                    f"{teacher.experience:<4} | {teacher.subject:<20}\n")

    def filter_data(self, department, position, subject):
        if department == "выберите файл" or position == "выберите файл" or subject == "выберите файл":
            return
        filtered_teachers = []
        a = []
        for teacher in self.filt_teachers:
            if (department == "не выбрано" or teacher.department == department) and \
                (position == "не выбрано" or teacher.position == position) and \
                    (subject == "не выбрано" or teacher.subject == subject):
                filtered_teachers.append(teacher)
        self.filt_teachers = filtered_teachers

    def get_unique_values(self, attribute):
        values = set()
        for teacher in self.filt_teachers:
            values.add(getattr(teacher, attribute))
        return sorted(list(values))


class AuthWindow():
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Авторизация")
        self.root.geometry("300x150")
        self.users = {}
        self.load_users_from_file("logins.txt")
        self.design()
        self.root.mainloop()

    def design(self):
        label_login = tk.Label(self.root, text="Логин:",
                               font=("Times New Roman", 14))
        label_login.grid(row=0, column=0, padx=10, pady=10)

        self.entry_login = tk.Entry(self.root, font=("Times New Roman", 14))
        self.entry_login.grid(row=0, column=1, padx=10, pady=10)

        label_password = tk.Label(
            self.root, text="Пароль:", font=("Times New Roman", 14))
        label_password.grid(row=1, column=0, padx=10, pady=10)

        self.entry_password = tk.Entry(
            self.root, show="*", font=("Times New Roman", 14))
        self.entry_password.grid(row=1, column=1, padx=10, pady=10)

        button_login = tk.Button(
            self.root, text="Войти", font=("Times New Roman", 14), 
            command=lambda: self.check_user())
        button_login.grid(row=2, column=0, columnspan=2, padx=10, pady=10)

    def load_users_from_file(self, file_path):
        if os.path.isfile(file_path):
            with open(file_path, 'r', encoding='utf-8') as file:
                for line in file:
                    buf = line.strip().split(' ')
                    if len(buf) == 2:
                        login, password = buf
                        self.users[login] = password

    def check_user(self):
        login = self.entry_login.get()
        password = self.entry_password.get()
        if login in self.users and self.users[login] == password:
            self.root.destroy()
            main_window = MainWindow()
            main_window.root.deiconify()
            main_window.root.mainloop()
        else:
            tk.messagebox.showerror("Ошибка", "Неверный логин или пароль")
            self.entry_login.delete(0, tk.END)
            self.entry_password.delete(0, tk.END)


class MainWindow():
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Данные о преподавателях")
        self.root.geometry("900x500")
        self.root.withdraw()
        self.data = Data()
        self.ffont = ("Times New Roman", 14)
        self.create_menu()
        self.create_table()
        self.create_filter_controls()

    def create_menu(self):
        menubar = tk.Menu(self.root, font=self.ffont)
        filemenu = tk.Menu(menubar, tearoff=0)
        filemenu.add_command(
            label="Открыть", command=self.open_file, font=self.ffont)
        filemenu.add_command(
            label="Сохранить", command=self.save_file, font=self.ffont)
        menubar.add_cascade(label="Файл", menu=filemenu, font=self.ffont)
        self.root.config(menu=menubar)

    def create_table(self):
        columns = ("Кафедра", "Должность", "Степень", "Стаж", "Предмет")
        self.table = ttk.Treeview(self.root, columns=columns, show="headings")
        for column in columns:
            self.table.heading(column, text=column)
        self.table.pack(fill="both", expand=True)
        # Фиксируем ширину столбца "Стаж"
        self.table.column("Стаж", width=50, stretch=False)

    def create_filter_controls(self):
        filter_frame = tk.Frame(self.root)
        filter_frame.pack(pady=10)

        label_department = ttk.Label(
            filter_frame, text="Кафедра", font=self.ffont)
        label_department.grid(row=0, column=0, padx=5)
        self.department_combobox = ttk.Combobox(
            filter_frame, values=["выберите файл"], width=20, font=self.ffont, state="readonly")
        self.department_combobox.grid(row=1, column=0, padx=5)
        label_position = ttk.Label(
            filter_frame, text="Должность", font=self.ffont)
        label_position.grid(row=0, column=1, padx=5)
        self.position_combobox = ttk.Combobox(
            filter_frame, values=["выберите файл"], font=self.ffont, width=20, state="readonly")
        self.position_combobox.grid(row=1, column=1, padx=5)
        label_subject = ttk.Label(
            filter_frame, text="Предмет", font=self.ffont)
        label_subject.grid(row=0, column=2, padx=5)
        self.subject_combobox = ttk.Combobox(
            filter_frame, values=["выберите файл"], font=self.ffont, width=20, state="readonly")
        self.subject_combobox.grid(row=1, column=2, padx=5)

        def backup():
            self.data.filt_teachers = self.data.input_teachers
            self.update_treeview()
            self.update_combobox()
        filter_button = tk.Button(
            filter_frame, text="Применить", command=lambda: self.apply(), font=self.ffont, width=20)
        filter_button.grid(row=1, column=3, padx=5, pady=10)
        backup_button = tk.Button(
            filter_frame, text="Сбросить", command=lambda: backup(), font=self.ffont, width=20)
        backup_button.grid(row=0, column=3, padx=5)

    def update_combobox(self):
        self.department_combobox.config(
            values=["не выбрано"] + self.data.get_unique_values("department"))
        self.department_combobox.current(0)
        self.position_combobox.config(
            values=["не выбрано"] + self.data.get_unique_values("position"))
        self.position_combobox.current(0)
        self.subject_combobox.config(
            values=["не выбрано"] + self.data.get_unique_values("subject"))
        self.subject_combobox.current(0)

    def update_treeview(self):
        self.table.delete(*self.table.get_children())
        for teacher in self.data.filt_teachers:
            self.table.insert("", tk.END, values=(
                teacher.department, teacher.position, 
                teacher.degree, teacher.experience, teacher.subject))

    def apply(self):
        department = self.department_combobox.get()
        position = self.position_combobox.get()
        subject = self.subject_combobox.get()
        self.data.filter_data(department, position, subject)
        self.update_treeview()
        self.update_combobox()

    def open_file(self):
        file_path = tk.filedialog.askopenfilename(defaultextension=".txt", filetypes=[
                                                  ("txt files", "*.txt"), ("All files", "*.*")])
        if file_path:
            self.data.load_data(file_path)
            self.update_treeview()
            self.update_combobox()

    def save_file(self):
        file_path = tk.filedialog.asksaveasfilename(defaultextension=".txt", filetypes=[
                                                    ("txt files", "*.txt"), ("All files", "*.*")])
        if file_path:
            self.data.save_data(file_path)
            messagebox.showinfo("Успех", "Сохранено")


if __name__ == "__main__":
    auth_window = AuthWindow()