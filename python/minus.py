import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QFileDialog, QMessageBox
)
import librosa
import numpy as np
from pydub import AudioSegment


class VocalRemoverApp(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("Удаление вокала")
        self.setGeometry(100, 100, 400, 200)

        # Layout
        layout = QVBoxLayout()

        # Labels and Buttons
        self.label_input = QLabel("Файл не выбран")
        self.label_output = QLabel("Путь для сохранения не указан")
        self.btn_select_input = QPushButton("Выбрать файл песни")
        self.btn_select_output = QPushButton("Сохранить как")
        self.btn_remove_vocals = QPushButton("Удалить вокал")
        
        # Button actions
        self.btn_select_input.clicked.connect(self.select_input_file)
        self.btn_select_output.clicked.connect(self.select_output_file)
        self.btn_remove_vocals.clicked.connect(self.process_audio)  # Подключаем метод process_audio

        # Add widgets to layout
        layout.addWidget(self.label_input)
        layout.addWidget(self.btn_select_input)
        layout.addWidget(self.label_output)
        layout.addWidget(self.btn_select_output)
        layout.addWidget(self.btn_remove_vocals)

        self.setLayout(layout)

        # File paths
        self.input_file = None
        self.output_file = None

    def select_input_file(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self, "Выберите файл песни", "", "Audio Files (*.wav;*.mp3);;All Files (*)"
        )
        if file_path:
            self.input_file = file_path
            self.label_input.setText(f"Файл: {file_path}")

    def select_output_file(self):
        file_path, _ = QFileDialog.getSaveFileName(
            self, "Сохранить минусовку", "", "Audio Files (*.mp3);;All Files (*)"
        )
        if file_path:
            if not file_path.endswith(".mp3"):
                file_path += ".mp3"
            self.output_file = file_path
            self.label_output.setText(f"Сохранить как: {file_path}")

    def process_audio(self):
        if not self.input_file:
            QMessageBox.warning(self, "Предупреждение", "Выберите файл песни!")
            return
        if not self.output_file:
            QMessageBox.warning(self, "Предупреждение", "Укажите путь для сохранения!")
            return

        try:
            # Load the audio file
            y, sr = librosa.load(self.input_file, sr=None, mono=False)
            
            if y.ndim == 1:
                QMessageBox.warning(self, "Ошибка", "Файл должен быть стерео!")
                return
            
            # Separate stereo channels
            left_channel = y[0]
            right_channel = y[1]
            
            # Remove vocals by subtracting channels
            instrumental = left_channel - right_channel
            
            # Apply Fourier Transform to suppress vocal frequencies
            fft = np.fft.rfft(instrumental)
            freqs = np.fft.rfftfreq(len(instrumental), d=1/sr)

            # Suppress vocal frequencies (300 Hz to 3400 Hz)
            vocal_freq_range = (freqs > 300) & (freqs < 3400)
            fft[vocal_freq_range] *= 0.1  # Reduce amplitude by 90%
            
            # Apply inverse FFT
            instrumental = np.fft.irfft(fft)

            # Normalize and clip the audio
            instrumental = instrumental / np.max(np.abs(instrumental))
            instrumental = np.clip(instrumental, -1.0, 1.0)

            # Convert to int16 for pydub compatibility
            instrumental = (instrumental * 32767).astype(np.int16)

            # Save as MP3
            audio_segment = AudioSegment(
                instrumental.tobytes(), 
                frame_rate=sr, 
                sample_width=2, 
                channels=1
            )
            audio_segment.export(self.output_file, format="mp3")

            QMessageBox.information(self, "Успех", f"Минусовка сохранена как {self.output_file}")

        except Exception as e:
            QMessageBox.critical(self, "Ошибка", f"Не удалось обработать файл: {e}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = VocalRemoverApp()
    window.show()  # Показываем окно приложения
    sys.exit(app.exec())
