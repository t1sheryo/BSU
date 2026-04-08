import os
from fpdf import FPDF

class PetriReport(FPDF):
    def header(self):
        self.set_font("CustomArial", "B", 16)
        self.cell(0, 10, "Лабораторная работа №4: Сети Петри", align="C", new_x="LMARGIN", new_y="NEXT")
        self.ln(5)

    def add_task_title(self, title):
        self.set_font("CustomArial", "B", 12)
        self.set_fill_color(235, 235, 235)
        self.cell(0, 10, title, fill=True, new_x="LMARGIN", new_y="NEXT")
        self.ln(2)

    def add_text(self, text):
        self.set_font("CustomArial", "", 10)
        self.multi_cell(0, 6, text)
        self.ln(3)

pdf = PetriReport()
font_path = r"C:\Windows\Fonts\arial.ttf"
font_bold = r"C:\Windows\Fonts\arialbd.ttf"

if not os.path.exists(font_path):
    print("Шрифт Arial не найден. Пожалуйста, проверьте путь.")
else:
    pdf.add_font("CustomArial", "", font_path)
    pdf.add_font("CustomArial", "B", font_bold)
    pdf.add_page()

    # Задание 1
    pdf.add_task_title("ЗАДАНИЕ 1: Структурный и динамический анализ")
    pdf.add_text(
        "1. Определение C = (P, T, I, O):\n"
        "P = {p1, p2, p3, p4, p5}, T = {t1, t2, t3, t4, t5}\n"
        "Входы: I(t1)={p4,p5}, I(t2)={p2,p2}, I(t3)={p1}, I(t4)={p3}, I(t5)={p3}\n"
        "Выходы: O(t1)={p1,p5}, O(t2)={p3}, O(t3)={p2,p2}, O(t4)={p4}, O(t5)=empty\n\n"
        "2. Расширенные функции:\n"
        "I(p1)={t1}, I(p2)={t3,t3}, I(p3)={t2}, I(p4)={t4}, I(p5)={t1}\n"
        "O(p1)={t3}, O(p2)={t2,t2}, O(p3)={t4,t5}, O(p4)={t1}, O(p5)={t1}\n\n"
        "3. Мультиграф G = (V, A):\n"
        "V = {p1,p2,p3,p4,p5,t1,t2,t3,t4,t5}\n"
        "A = {(p4,t1), (p5,t1), (t1,p1), (t1,p5), (p1,t3), (t3,p2), (t3,p2), (p2,t2), (p2,t2), (t2,p3), (p3,t4), (t4,p4), (p3,t5)}\n\n"
        "4. Выполнение (маркировки):\n"
        "m0 = (0,0,0,1,1) -> m1=(1,0,0,0,1) -> m2=(0,2,0,0,1) -> m3=(0,0,1,0,1) -> m4=(0,0,0,1,1)\n\n"
        "5. Двойственная сеть:\n"
        "Позиции становятся переходами. I'(p1)={t1}, O'(p1)={t3}, и т.д.\n\n"
        "6. Инверсная сеть:\n"
        "Все стрелки меняют направление. I_inv(t1)={p1,p5}, O_inv(t1)={p4,p5}."
    )

    # Задание 2
    pdf.add_task_title("ЗАДАНИЕ 2: Построение графа по структуре")
    pdf.add_text(
        "Данные:\nP={p1,p2}, T={t1,t2,t3}\n"
        "I(t1)={p1}, O(t1)={p1,p2}\n"
        "I(t2)={p1}, O(t2)={p2}\n"
        "I(t3)={p2}, O(t3)={p1}\n\n"
        "Описание графа:\n"
        "t1: вход из p1, выходы в p1 (петля) и p2.\n"
        "t2: вход из p1, выход в p2.\n"
        "t3: вход из p2, выход в p1."
    )

    pdf.output("Petri_Net_Detailed_Report.pdf")
    print("Файл Petri_Net_Detailed_Report.pdf успешно создан!")