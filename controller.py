
from pynput.keyboard import Controller
import os
from flask import Flask, request
keyboard = Controller()

print("Hello Welcome to Nano Controller")


app = Flask(__name__)


@app.route('/send', methods=['GET', 'POST'])
def index():
    data  = request.args.get('comand')
    print(data)
    if data == "d":
        print(data)
        keyboard.press("d")

    if data == "!d":
        print(data)
        keyboard.release("d")

    if data == "a":
        print(data)
        keyboard.press("a")

    if data == "!a":
        print(data)
        keyboard.release("a")

    if data == "f":
        print(data)
        keyboard.press("f")

    if data == "!f":
        print(data)
        keyboard.release("f")

    if data == "s":
        print(data)
        keyboard.press("s")

    if data == "!s":
        print(data)
        keyboard.release("s")

    if data == "g":
        print(data)
        keyboard.press("g")

    if data == "!g":
        print(data)
        keyboard.release("g")
    return 'go'


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
  