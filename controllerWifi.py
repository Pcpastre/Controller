
from pynput.keyboard import Key, Controller
import os
from flask import Flask, request
keyboard = Controller()

print("Hello Welcome to Nano Controller")

comands = ["f1", "f2", "f3", "f4", "f5"]
keys = [Key.f1,Key.f2,Key.f3,Key.f4,Key.f5]

app = Flask(__name__)


@app.route('/send', methods=['GET', 'POST'])
def index():
    data  = request.args.get('comand')
    print(data)
    count = 0
    for i in comands:
        if(data.startswith("!") and data[1:] == i ):
            keyboard.release(keys[count])
            print(data)
        elif (data == i ):
            print(data)
            keyboard.press(keys[count])
        count = count + 1
    return 'go'


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
  