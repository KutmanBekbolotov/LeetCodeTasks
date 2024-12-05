number = int(input('Enter number: '))

if(number % 2 == 0):
    print("Even")

    if(number % 6 == 0):
        print(f"{number} divided by 6")
    else:
        print(f"{number} not divided by 6")

else:
    print("odd")

    
    