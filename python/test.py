x = float(input("Enter x: "))
y = float(input("Enter y: "))

if x == 0 or y == 0:
    print ("Dot on axis")
else:
    if x > 0:
        if y> 0:
            print("Dot on 1/4")
        else:
            print("Dot on 4/4")
    else:
        if y > 0:
            print("Dot on 2/4")
        else:
            print("Dot 3/4")
