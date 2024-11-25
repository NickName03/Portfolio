import re
import tkinter as tk
from tkinter import filedialog, messagebox, ttk


class Motorcycle:
    def __init__(self, brand, type_, country, year, price):
        self.data = {
            "brand": brand,
            "type": type_,
            "country": country,
            "year": year,
            "price": price
        }

    def get_data(self):
        return f"{self.data['brand']:<20} {self.data['type']:<20} {self.data['country']:<20} {self.data['year']:<6} {self.data['price']:<15}\n"


class DataManager:
    def __init__(self):
        self.data = []
        self.backup_data = []

    def load_data(self, file_name):
        self.data = []
        self.backup_data = []
        with open(file_name, 'r', encoding='utf-8') as f:
            for line in f:
                split = re.split(
                    r"[:.;!?^%$*|\n\t<>,\s]+", line.strip())
                self.data.append(Motorcycle(
                    " ".join(split[0:-4]), split[-4], split[-3], int(split[-2]), int(split[-1])))
        self.backup_data = self.data

    def save_data(self, file_name):
        with open(file_name, 'w', encoding='utf-8') as f:
            for bike in self.data:
                f.write(bike.get_data())

    def load_backup_data(self):
        self.data = self.backup_data

    def filter_by_brand(self, brands):
        return [bike for bike in self.data if bike.data["brand"] in brands]

    def filter_by_type(self, types):
        return [bike for bike in self.data if bike.data["type"] in types]

    def filter_by_price(self, lower, upper):
        return [bike for bike in self.data if lower <= bike.data["price"] <= upper]


class User:
    def __init__(self, username, password):
        self.username = username
        self.password = password


class Authorization:
    def __init__(self, file_name):
        self.users = []
        self.file_name = file_name
        self.load_users()

    def load_users(self):
        with open(self.file_name, 'r', encoding='utf-8') as f:
            for line in f:
                username, password = line.strip().split(' ')
                self.users.append(User(username, password))

    def verify_user(self, username, password):
        for user in self.users:
            if user.username == username and user.password == password:
                return True

        messagebox.showerror(
            "Ошибка!", "Неверное имя пользователя или пароль!")


class Application:
    def __init__(self):
        self.data_manager = DataManager()
        self.authorization = Authorization('Users/login.txt')
        self.root = tk.Tk()
        self.root.title("Мотоциклы")
        self.root.geometry("1400x700")
        self.root.resizable(False, True)
        self.root.config(bg="#EAE1B6")
        self.style = ttk.Style()
        self.font = ("Open Sans", 14)
        self.style_config()
        self.login_window()

    def run(self):
        self.root.mainloop()

    def login_window(self):
        def entry_focus_in(event, entry):
            if entry.get() == "username" or entry.get() == "password":
                entry.delete(0, tk.END)

        def entry_focus_out(event, entry, text):
            if len(entry.get()) == 0:
                entry.insert(0, text)

        width = 30
        self.login = tk.Frame(self.root)
        self.login.pack(fill="both", expand=True)

        frame = tk.Frame(self.login, bg="#012F49", width=200, height=400)
        frame.pack(fill="both", expand=True)
        # Размещение по центру
        frame.place(relx=0.5, rely=0.4, anchor="center")

        header = tk.Label(frame, text="Авторизация", font=(
            "Open Sans", 24, "bold"), bg="#012F49", fg="#EAE1B6")
        header.pack(pady=15, anchor="center")

        username_frame = tk.Frame(frame)
        username_entry = ttk.Entry(
            username_frame, style="style.TEntry", font=self.font, width=width)
        username_entry.insert(0, "username")
        username_entry.bind(
            "<FocusIn>", lambda event: entry_focus_in(event, username_entry))
        username_entry.bind("<FocusOut>", lambda event: entry_focus_out(
            event, username_entry, "username"))
        username_entry.pack()
        username_frame.pack(padx=15, pady=15, expand=True)

        password_frame = tk.Frame(frame)
        password_entry = ttk.Entry(
            password_frame, style="style.TEntry", font=self.font, width=width, show="*")
        password_entry.insert(0, "password")
        password_entry.bind(
            "<FocusIn>", lambda event: entry_focus_in(event, password_entry))
        password_entry.bind("<FocusOut>", lambda event: entry_focus_out(
            event, password_entry, "password"))
        password_entry.pack(anchor="w")
        password_frame.pack(padx=15, pady=15, expand=True)

        tk.Button(frame, text="Войти", width=width, font=self.font,
                  bg="#F67F01", fg="#012F49",
                  command=lambda: self.verify_login(username_entry.get(), password_entry.get())).pack(pady=15)

    def verify_login(self, username, password):
        if self.authorization.verify_user(username, password):
            self.login.destroy()
            self.main_window()
        else:
            tk.messagebox.showerror(
                "Ошибка", "Неверные имя пользователя или пароль")

    def style_config(self):
        self.style.configure("Toolbutton", background="#012F49", foreground="#EAE1B6",
                             font=("Open Sans", 12), width=15, padding=10, anchor="center")
        self.style.configure("style.TEntry", font=("Open Sans", 16, 'bold'),
                             background="#EAE1B6", foreground="#012F49", padding=10)
        self.style.configure("Header.TLabel", font=("Open Sans", 16, 'bold'),
                             background="#EAE1B6", foreground="#012F49", padding=5,
                             padx=5, anchor="nw")
        self.style.configure("Common.TLabel", font=("Open Sans", 14),
                             background="#EAE1B6", foreground="#012F49", padding=5,
                             padx=5, anchor="nw", width=10)
        self.style.configure("style.Treeview", font=self.font,
                             background="#EAE1B6", foreground="#012F49")
        self.style.configure("style.Treeview.Heading", font=("Open Sans", 16, 'bold'),
                             background="blue", foreground="#012F49", padding=5)

    def main_window(self):
        self.show_menubar()
        self.main_frame = tk.Frame(self.root, bg="#EAE1B6")
        self.main_frame.pack(fill="both", side="left", expand=True)
        self.tree = ttk.Treeview()
        self.all_filters = tk.Frame(self.root, width=200, bg="#EAE1B6")

    def show_menubar(self):
        def on_enter(event):
            self.style.configure(
                "Toolbutton", background="#EAE1B6", foreground="#012F49")
            bar['background'] = "#EAE1B6"

        def on_leave(event):
            self.style.configure(
                "Toolbutton", background="#012F49", foreground="#EAE1B6")
            bar['background'] = "#012F49"

        bar = tk.Frame(self.root, bg="#012F49")
        bar.pack(fill="x")
        filebar = ttk.Menubutton(
            bar, text="Файл", style="Toolbutton")
        filebar.bind("<Enter>", lambda event: on_enter(event))
        filebar.bind("<Leave>", lambda event: on_leave(event))
        filterbar = ttk.Menubutton(
            bar, text="Фильтрация", style="Toolbutton")
        filterbar.bind("<Enter>", lambda event: on_enter(event))
        filterbar.bind("<Leave>", lambda event: on_leave(event))
        filebar.pack(side="left")
        filterbar.pack(side="left")

        filemenu = tk.Menu(filebar, tearoff=0, bg="#012F49",
                           fg="#EAE1B6", font=("Open Sans", 12))
        filemenu.add_command(
            label="Открыть",  command=lambda: self.open_file("load"))
        filemenu.add_command(
            label="Сохранить", command=lambda: self.open_file("save"))
        filebar["menu"] = filemenu

        filtermenu = tk.Menu(filterbar, tearoff=0, bg="#012F49",
                             fg="#EAE1B6", font=("Open Sans", 12))
        check_var = tk.BooleanVar(value=True)
        filtermenu.add_checkbutton(label="Отобразить фильтры", variable=check_var,
                                   command=lambda: self.change_filtering_frame(check_var.get()))
        filtermenu.add_command(label="Сбросить фильтрацию",
                               command=lambda: self.reset_filtering())
        filterbar["menu"] = filtermenu

    def open_file(self, mode):
        if mode == "load":
            filepath = filedialog.askopenfilename(
                defaultextension=".txt",  # расширение файлов по умолчанию
                filetypes=[("Текстовые файлы", "*.txt"), ("Все файлы", "*.*")])
            if filepath:
                if not self.data_manager.data:
                    self.data_manager.load_data(filepath)
                    self.show_filter()
                    self.show_data()
                else:
                    self.data_manager.load_data(filepath)
                    self.show_data()
                    self.update_ListBox()

        if mode == "save":
            filepath = filedialog.asksaveasfilename(
                defaultextension=".txt",
                filetypes=[("Текстовые файлы", "*.txt"), ("Все файлы", "*.*")])
            if filepath:
                self.data_manager.save_data(filepath)
                messagebox.showinfo("Внимание", "Файл успешно сохранен!")

    def change_filtering_frame(self, check):
        if not self.data_manager.data:
            messagebox.showerror("Ошибка!", "Нет данных для фильтрации!")
            return
        if check:
            self.all_filters.pack(fill="both", side="right")
        else:
            self.all_filters.pack_forget()
        self.show_data()

    def reset_filtering(self):
        self.data_manager.load_backup_data()
        self.update_ListBox()
        self.brand_listbox.selection_clear(0, tk.END)
        self.type_listbox.selection_clear(0, tk.END)
        self.show_data()

    def show_data(self):
        if self.tree:
            self.tree.destroy()
        headers = ["Марка", "Тип", "Страна", "Год", "Цена"]
        self.tree = ttk.Treeview(
            self.main_frame, columns=headers, show="headings", style="style.Treeview")
        for head in headers:
            self.tree.heading(head, text=head)
        for bike in self.data_manager.data:
            self.tree.insert("", tk.END, values=(bike.data["brand"], bike.data["type"],
                                                 bike.data["country"], bike.data["year"], bike.data["price"]))
        self.tree.pack(fill="both", expand=True)

    def filtering(self):
        if len(self.price_low_entry.get()) > 0 and len(self.price_up_entry.get()) > 0:
            try:
                lower = int(self.price_low_entry.get())
                upper = int(self.price_up_entry.get())
                if upper < lower:
                    messagebox.showerror(
                        "Ошибка!", "Указан неверный диапазон!")
                self.data_manager.data = self.data_manager.filter_by_price(
                    lower, upper)
            except ValueError:
                messagebox.showerror(
                    "Ошибка!", "В поля цены должны быть введены числа!")
                return
        else:
            messagebox.showerror(
                "Ошибка!", "Введенное значение не должно быть отрицательным!")
            return
        self.show_data()
        self.update_ListBox()
        self.price_low_entry.delete(0, tk.END)
        self.price_up_entry.delete(0, tk.END)

    def get_set(self, key):
        uniq = set()
        for bike in self.data_manager.data:
            uniq.add(bike.data[key])
        return list(uniq)

    def update_ListBox(self):
        brand_all = tk.StringVar(value=self.get_set("brand"))
        type_all = tk.StringVar(value=self.get_set("type"))
        self.brand_listbox.config(listvariable=brand_all)
        self.type_listbox.config(listvariable=type_all)

    def show_filter(self):
        self.selected_brands = []
        self.selected_types = []

        def update_brand_selection(event):
            self.selected_brands = [self.brand_listbox.get(
                i) for i in self.brand_listbox.curselection()]
            if len(self.selected_brands) == 0:
                return
            self.data_manager.data = self.data_manager.filter_by_brand(
                self.selected_brands)
            self.update_ListBox()
            self.show_data()

        def update_type_selection(event):
            self.selected_types = [self.type_listbox.get(
                i) for i in self.type_listbox.curselection()]
            if len(self.selected_types) == 0:
                return
            self.data_manager.data = self.data_manager.filter_by_type(
                self.selected_types)
            self.update_ListBox()
            self.show_data()
        # секция марка
        brand_frame = tk.Frame(self.all_filters, height=200)
        brand_label = ttk.Label(
            brand_frame, text="Марка", style="Header.TLabel")
        brand_label.pack(fill="x")
        self.brand_listbox = tk.Listbox(brand_frame, selectmode="multiple", bg="#EAE1B6", fg="#012F49",
                                        highlightcolor="#F67F01", selectbackground="#F67F01", font=self.font, height=8)
        self.brand_listbox.bind(
            "<Leave>", lambda event: update_brand_selection(event))
        self.brand_listbox.pack(fill="x")
        brand_frame.pack(fill="x", expand=True)
        # секция тип
        type_frame = tk.Frame(self.all_filters, height=200)
        type_label = ttk.Label(type_frame, text="Тип", style="Header.TLabel")
        type_label.pack(fill="x")
        self.type_listbox = tk.Listbox(
            type_frame, selectmode="multiple", bg="#EAE1B6", fg="#012F49",
                                   highlightcolor="#F67F01", selectbackground="#F67F01", font=self.font, height=8)
        self.type_listbox.bind(
            "<Leave>", lambda event: update_type_selection(event))
        self.type_listbox.pack(fill="x")
        self.update_ListBox()
        type_frame.pack(fill="x")
        # секция цена
        price_frame = tk.Frame(self.all_filters, bg="#EAE1B6")
        price_label = ttk.Label(
            price_frame, text="Цена", style="Header.TLabel")
        price_label.pack(fill="x")
        # Фрейм с нижним порогом цены
        price_low_frame = tk.Frame(price_frame)
        price_low_label = ttk.Label(
            price_low_frame, text="От", style="Common.TLabel").pack(side="left", fill="y")
        self.price_low_entry = ttk.Entry(
            price_low_frame, style="style.TEntry", font=self.font)
        self.price_low_entry.pack(side="right", fill="x", expand=True)
        price_low_frame.pack(fill="x")
        # с верхним
        price_up_frame = tk.Frame(price_frame)
        price_up_label = ttk.Label(
            price_up_frame, text="До", style="Common.TLabel").pack(side="left", fill="y")
        self.price_up_entry = ttk.Entry(
            price_up_frame, style="style.TEntry", font=self.font)
        self.price_up_entry.pack(side="right", fill="x", expand=True)
        price_up_frame.pack(fill="x")
        price_frame.pack(fill="x")

        apply = tk.Button(self.all_filters, text="Применить", width=20, font=self.font,
                          bg="#F67F01", fg="#012F49",
                          command=lambda: self.filtering())
        apply.pack(side="bottom", pady=10)
        self.all_filters.pack(fill="both", side="right")


if __name__ == "__main__":
    app = Application()
    app.run()
