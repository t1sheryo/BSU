import cv2
import numpy as np
from tkinter import filedialog, Tk, Button, Label
from PIL import Image, ImageTk

class ImageProcessingApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Image Processing Application")

        self.load_button = Button(root, text="Load Image", command=self.load_image)
        self.load_button.pack()

        self.hist_eq_button = Button(root, text="Histogram Equalization", command=self.histogram_equalization)
        self.hist_eq_button.pack()

        self.linear_contrast_button = Button(root, text="Linear Contrast Stretching", command=self.linear_contrast)
        self.linear_contrast_button.pack()

        self.edge_detection_button = Button(root, text="Edge Detection", command=self.edge_detection)
        self.edge_detection_button.pack()

        self.label = Label(root)
        self.label.pack()

        self.image = None
        self.processed_image = None

    def load_image(self):
        file_path = filedialog.askopenfilename()
        if file_path:
            self.image = cv2.imread(file_path)
            # Проверяем, что изображение успешно загружено
            if self.image is None:
                print("Ошибка: не удалось загрузить изображение. Проверьте путь к файлу.")
            else:
                self.show_image(self.image)

    def show_image(self, img):
        if img is not None:
            img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
            img_pil = Image.fromarray(img_rgb)
            img_tk = ImageTk.PhotoImage(img_pil)

            self.label.config(image=img_tk)
            self.label.image = img_tk

    def histogram_equalization(self):
        if self.image is not None:
            img_yuv = cv2.cvtColor(self.image, cv2.COLOR_BGR2YUV)
            img_yuv[:, :, 0] = cv2.equalizeHist(img_yuv[:, :, 0])
            self.processed_image = cv2.cvtColor(img_yuv, cv2.COLOR_YUV2BGR)
            self.show_image(self.processed_image)
        else:
            print("Изображение не загружено.")

    def linear_contrast(self):
        if self.image is not None:
            min_val = np.min(self.image)
            max_val = np.max(self.image)
            self.processed_image = ((self.image - min_val) * (255 / (max_val - min_val))).astype(np.uint8)
            self.show_image(self.processed_image)
        else:
            print("Изображение не загружено.")

    def edge_detection(self):
        if self.image is not None:
            gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
            edges = cv2.Canny(gray, 100, 200)
            self.processed_image = cv2.cvtColor(edges, cv2.COLOR_GRAY2BGR)
            self.show_image(self.processed_image)
        else:
            print("Изображение не загружено.")


if __name__ == "__main__":
    root = Tk()
    app = ImageProcessingApp(root)
    root.mainloop()
