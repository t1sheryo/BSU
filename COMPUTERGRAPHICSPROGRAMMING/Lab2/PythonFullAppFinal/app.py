import os
import tkinter as tk
from tkinter import filedialog, ttk
from PIL import Image

def get_image_info(file_path):
    try:
        with Image.open(file_path) as img:
            file_name = os.path.basename(file_path)
            width, height = img.size
            dpi = img.info.get('dpi', (None, None))[0]
            color_depth = img.mode
            compression = img.info.get("compression", "Нет")

            return {
                "Имя файла": file_name,
                "Размер (пиксели)": f"{width}x{height}",
                "Разрешение (dpi)": dpi,
                "Глубина цвета": color_depth,
                "Сжатие": compression,
            }
    except Exception as e:
        print(f"Ошибка при обработке файла {file_path}: {e}")
        return None

def scan_directory(directory):
    supported_formats = ('.jpg', '.jpeg', '.gif', '.tif', '.bmp', '.png', '.pcx')
    results = []

    for root, _, files in os.walk(directory):
        for file in files:
            if file.lower().endswith(supported_formats):
                file_path = os.path.join(root, file)
                info = get_image_info(file_path)
                if info:
                    results.append(info)
    return results

def open_file():
    file_path = filedialog.askopenfilename(filetypes=[("Изображения", "*.jpg *.jpeg *.gif *.tif *.bmp *.png *.pcx")])
    if file_path:
        image_info = get_image_info(file_path)
        if image_info:
            display_info_table([image_info])

def open_directory():
    directory = filedialog.askdirectory()
    if directory:
        image_info_list = scan_directory(directory)
        display_info_table(image_info_list)

def display_info_table(info_list):
    for row in tree.get_children():
        tree.delete(row)

    for info in info_list:
        tree.insert('', tk.END, values=(info["Имя файла"], info["Размер (пиксели)"],
                                        info["Разрешение (dpi)"], info["Глубина цвета"],
                                        info["Сжатие"]))

root = tk.Tk()
root.title("Информация об изображениях")
root.geometry("800x400")

button_frame = tk.Frame(root)
button_frame.pack(pady=10)

open_file_button = tk.Button(button_frame, text="Выбрать файл", command=open_file)
open_file_button.pack(side=tk.LEFT, padx=5)

open_directory_button = tk.Button(button_frame, text="Выбрать папку с изображениями", command=open_directory)
open_directory_button.pack(side=tk.LEFT, padx=5)

columns = ("Имя файла", "Размер (пиксели)", "Разрешение (dpi)", "Глубина цвета", "Сжатие")
tree = ttk.Treeview(root, columns=columns, show="headings")
for col in columns:
    tree.heading(col, text=col)
    tree.column(col, anchor="center")

tree.pack(fill=tk.BOTH, expand=True)

root.mainloop()
