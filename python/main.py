# task 1
def sum(n):
    total = 0
    i = 1
    while i <= n:
        total += i
        i += 1
    return total

print(sum(5))

#task2
def sum_for(n):
    total = 0
    for i in range(1, n + 1):
        total += i
    return total

print(sum_for(5))

#task3
def sum_from_a_to_b(a, b):
    total = 0
    for i in range(a, b + 1):
        total += i
    return total

print(sum_from_a_to_b(3, 7))

#task4(factorial)
def factorial(n):
    result = 1
    for i in range(1, n + 1):
        result *= i
    return result
print(factorial(5))

#task 5
def squares_to_n(n):
    return [i**2 for i in range (1, n + 1)]
print(squares_to_n(5))

#task 6
def squares_a_b(a, b):
    return [i**2 for i in range(a, b + 1)]
print(squares_a_b(3, 5))

#task 7
def odd_numbers(a, b):
    return [i for i in range(a, b + 1) if i % 2 != 0]
print(odd_numbers(3, 10))

#task 8
def filter_in_interval(nums):
    return[i for i in nums if 1 <= i <= 3]
print(filter_in_interval([0, 2, 4])) #output: 2

#task 9
import math

def solve_quadratic(a, b, c):
    discriminant = b**2 - 4*a*c
    if discriminant > 0:
        x1 = (-b + math.sqrt(discriminant)) / (2 * a)
        x2 = (-b - math.sqrt(discriminant)) / (2 * a)
        return x1, x2
    elif discriminant == 0:
        x = -b / (2 * a)
        return x
    else:
        return "Нет действительных корней"

print(solve_quadratic(1, -3, 2))  # Вывод: (2.0, 1.0)
    
#task 10
def max_of_three(a, b, c):
    return max(a, b, c)

print(max_of_three(3, 7, 5))  # Вывод: 7

#task 11
def is_triangle(a, b, c):
    return a + b > c and a + c > b and b + c > a

print(is_triangle(3, 4, 5))  # Вывод: True

#task 12
def powers_up_to_limit(base, limit):
    result = []
    power = 1
    while base**power <= limit:
        result.append(base**power)
        power += 1
    return result

print(powers_up_to_limit(2, 32))  # Вывод: [2, 4, 8, 16, 32]

#task 13
def sum_and_product_of_digits(num):
    digits = [int(d) for d in str(num)]
    return sum(digits), math.prod(digits)

print(sum_and_product_of_digits(123))  # Вывод: (6, 6)

#task 14
def count_even_odd_digits(num):
    digits = [int(d) for d in str(num)]
    even_count = sum(1 for d in digits if d % 2 == 0)
    odd_count = len(digits) - even_count
    return even_count, odd_count

print(count_even_odd_digits(12345))  # Вывод: (2, 3)