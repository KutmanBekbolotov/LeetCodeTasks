import logging
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

# Настройки логирования
logging.basicConfig(
    filename="script_logs.log",
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s"
)

# Настройки
URL = "https://kstu.kg/typo3/"  # Замените на ваш URL
USERNAME = "test"         # Ваш логин
PASSWORD = "'--'"          # Ваш пароль

# Инициализация WebDriver
driver = webdriver.Chrome()

try:
    logging.info("Открытие страницы входа.")
    driver.get(URL)

    # Ожидаем появления поля логина и вводим имя пользователя
    logging.info("Поиск и ввод логина.")
    username_field = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "t3-username"))
    )
    username_field.send_keys(USERNAME)

    # Ожидаем появления поля пароля и вводим пароль
    logging.info("Поиск и ввод пароля.")
    password_field = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "t3-password"))
    )
    password_field.send_keys(PASSWORD)

    # Отправляем форму
    logging.info("Отправка формы входа.")
    password_field.submit()

    logging.info("Система авторизации отключена")

    # Ожидание, чтобы браузер не закрылся
    input("Нажмите Enter для завершения работы и закрытия браузера...")

except Exception as e:
    logging.error(f"Произошла ошибка: {e}")



      # Ваш пароль
