import math
import random
from turtle import *

def heart(k):
    return 15 * math.sin(k)**3

def heart1(k):
    return 12 * math.cos(k) - 5 * \
        math.cos(2 * k) - 2 * \
        math.cos(3 * k) - \
        math.cos(4 * k)

speed(0.001)
bgcolor('black')
colormode(255)

penup()
goto(0, 0)
pendown()

for i in range(6000):
    r = random.randint(50, 255)
    g = random.randint(50, 255)
    b = random.randint(50, 255)
    color((r,  g, b))

    goto(heart(i) * 20, heart1(i) * 20)

done()