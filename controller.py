
from pynput.keyboard import Controller

print("Hello Welcome to NBox 100")

print("""Please enter the COM port of your controller.
You can find it if you go to your device manager and look for COM & LPT
section. find your device by unpluging it and pluging it again.
You write it like:
ex: COM8
""")


print("connection established")

keyboard = Controller()

while True:
    data = input("Enter")
    
    if data == "a":
        keyboard.press("d")

    if data == "!d":
        keyboard.release("d")

    if data == "a":
        keyboard.press("a")

    if data == "!a":
        keyboard.release("a")

    if data == "f":
        keyboard.press("f")

    if data == "!f":
        keyboard.release("f")