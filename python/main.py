number = int(input("Введите число: "))

product = 1

for digit in str(abs(number)):
    product *= int(digit)

print(f"Произведение цифр числа {number}: {product}")