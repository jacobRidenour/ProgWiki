print("Basic Calculator v0.1\n---------------------\nFormat: first number (operation) second number\n---------------------")
num1 = input("Enter a number: ")
num2 = input("Enter another number: ")

print("[1] add [2] subtract [3] multiply [4] divide [5] modulus")

validInput = False
op = input("Enter an operation: ")
op = int(op)

while(validInput == False):
    if(op >= 1 and op <= 5):
        validInput = True
    else:
        op = input("Enter an operation: ")
        op = int(op) #cast back to int so we don't treat str as int if invalid input more than once

#Having op as a str and checking == "+", "-", etc. would also work
if(op == 1):
    #add
    result = float(num1) + float(num2)
    print(num1 + " + " + num2 + " = " + str(result))
elif(op == 2):
    #subtract
    result = float(num1) - float(num2)
    print(num1 + " - " + num2 + " = " + str(result))
elif(op == 3):
    #multiply
    result = float(num1) * float(num2)
    print(num1 + " * " + num2 + " = " + str(result))
elif(op == 4):
    #divide
    result = float(num1) / float(num2)
    print(num1 + " / " + num2 + " = " + str(result))
    result = int(result)
    print(num1 + " / " + num2 + " = " + str(result) + " (integer division)")
else:
    #mod
    result = float(num1) % float(num2)
    print(num1 + " % " + num2 + " = " + str(result))
    