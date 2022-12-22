from math import * #import stuff (*) from math module

print("   /|")
print("  / |")
print(" /  |")
print("/___|\n")

charName = "John"
charAge = "69"      #str
age = 50            #int
age = "400"         #notice we don't have to change the "type" of age - it's implied based on the data assigned
isMale = True       #boolean
isFemale = False    #boolean

#Note: print adds \n at the end
#Note: cannot concatenate with anything but str
#Note: use str(dataType) to convert other data types to str
print("There once was a man named " + charName + ", he was " + charAge + " years old.")
charName = "Scoots"
charAge = "25"
print("He really liked the name " + charName + ", but didn't like being " + charAge + ".\n")


#Working with Strings
msg = "UpDog"
print("String msg is: " + msg + "; in lowercase: " + msg.lower() + "; in all caps: " + msg.upper() + "; its length is " + str(len(msg)))
if(msg.isupper() == True):
    print(msg)
#index function - tells you where a specific char/string is located, only prints the first matching index
#ERROR if not found.
print("msg's first character is " + msg[0] + "; first index of \"D\": " + str(msg.index("D")) + "; first index of \"Dog\": " + str(msg.index("Dog")))

#replace - 2 parameters - token to replace, replacement str
print("Replacing \"Up\" with \"Down\": " + msg.replace("Up", "Down") + "\n")


#Working with Numbers
#+-*/%; Math functions...
num = -5
abs(num)        #absolute value
pow(num, 3)     #exponent (base, to the power of)
max(num, 6)     #returns the larger of the two numbers
min(num, 6)     #returns the smaller of the two numbers
round(3.2)      #follows expected rounding rules
#Math library functions
floor(3.2)      
ceil(3.2) 
sqrt(abs(num))
comb(20, 4)     #n choose k
factorial(4)


#Working with user input
name = input("Enter your name: ") #store user input as str
age = input("Enter your age: ")  #store user input as str
name = name.replace(name[0], name[0].upper()) #capitalize first letter in case user doesn't
nextYear = int(age) + 1
print("Hi " + name + "! You are " + age + " years old. On your next birthday you will be " + str(nextYear) + ".")


#Working with Tuples
#Similar to Lists but they're immutable; best use case is as look-up tables or data that won't change
coordinates = (4, 5) #() to create a tuple, similar to [] for a list
coordinates[0] #is 4
#coordinates[1] = 10 ***NOT ALLOWED***
listOfCoordinates = [(1, 1), (5, 9), (6, 14)] #list of tuples


#Functions (keyword def)
def sayHello(name):
    print("Hello " + str(name) + "!")
#^ void function (no return value)
sayHello("Joe") #Call the function

def cube(aNum):
    return aNum*aNum*aNum
print(cube(3)) #Notice: similar to pass by reference
#Notice no return type needs specified


#Conditions
statement = True
statement2 = True

if statement:
    if statement and statement2:
        print("statement and statement2 are true")
    if statement and not(statement2):
        print("statement is true")
elif statement2:
    print("statement2 is true")
else:
    print("statement and statement2 are false")

if statement or statement2:
    print("either statement is true or statement2 is true.")
    
num = 4
num2 = 10
num3 = 16

# == != are valid too
def largest(num, num2, num3):
    if num >= num2 and num >= num3:
        return num
    elif num2 >= num and num2 >= num3:
        return num2
    else:
        return num3

max = largest(num, num2, num3)













