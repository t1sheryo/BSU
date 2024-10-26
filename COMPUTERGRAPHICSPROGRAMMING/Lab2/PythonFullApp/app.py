import os
import tkinter as tk
from tkinter import filedialog, ttk, messagebox
from PIL import Image, ImageTk

def get_image_info(file_path):
    """Получает основную информацию из графического файла."""
    try:
        with Image.open(file_path) as img:
            # Основная информация об изображении
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
    """Сканирует директорию и извлекает информацию из графических файлов."""
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

def open_directory():
    """Открывает диалоговое окно для выбора директории."""
    directory = filedialog.askdirectory()
    if directory:
        image_info_list = scan_directory(directory)
        display_info_table(image_info_list)

def display_info_table(info_list):
    """Отображает информацию в таблице."""
    # Очистка предыдущих данных
    for row in tree.get_children():
        tree.delete(row)

    # Добавление новых данных
    for info in info_list:
        tree.insert('', tk.END, values=(info["Имя файла"], info["Размер (пиксели)"],
                                        info["Разрешение (dpi)"], info["Глубина цвета"],
                                        info["Сжатие"]))

# Создание главного окна
root = tk.Tk()
root.title("Информация об изображениях")
root.geometry("800x400")

# Кнопка выбора директории
button_frame = tk.Frame(root)
button_frame.pack(pady=10)
open_button = tk.Button(button_frame, text="Выбрать папку с изображениями", command=open_directory)
open_button.pack()

# Таблица для отображения информации
columns = ("Имя файла", "Размер (пиксели)", "Разрешение (dpi)", "Глубина цвета", "Сжатие")
tree = ttk.Treeview(root, columns=columns, show="headings")
for col in columns:
    tree.heading(col, text=col)
    tree.column(col, anchor="center")

tree.pack(fill=tk.BOTH, expand=True)

# Запуск приложения
root.mainloop()
