import serial
from pynput.keyboard import Key, Controller
import os
from threading import *
import serialFind as serialFind
keyboard = Controller()

Controller = serial.Serial(serialFind.serialEnd, 115200)

comands = ["f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9","f10", "f11", "f12", "1","2","3","4","5","6","7","8","9","0","-","=","q","w","e","r","t","ip","u","i","o","p","'","[","a","s","d","f","g","h","j","k","l","ce","ti", "]","bi","z","x","c","v","b","n", "m", ",", ".", ";", "/", "up"]
keys = [Key.f1,Key.f2,Key.f3,Key.f4,Key.f5,Key.f6,Key.f7,Key.f8,Key.f9,Key.f10,Key.f11,Key.f12,"1","2","3","4","5","6","7","8","9","0","-","=","q","w","e","r","t","y","u","i","o","p","'","[","a","s","d","f","g","h","j","k","l","ç",Key.down, "]","\\","z","x","c","v","b","n", "m", ",", ".", ";", Key.left, Key.up]
print("Hello Welcome to Nano Controller")
THREADS = []
class outputTecl(Thread):
    def __init__(self, s):
        try:
            Thread.__init__(self)
            self.data = s
        except:
            print("Error in Thread outputTecl")

    def run(self):
        count = 0
        for i in comands:
            if(self.data.startswith("!") and self.data[1:] == i ):
                keyboard.release(keys[count])
                print(self.data)
            elif (self.data == i ):
                print(self.data)
                keyboard.press(keys[count])
            count = count + 1


while(True):
    b = Controller.readline()
    data = b.decode("utf-8")
    dataSplit = data.split("\r")
    data = dataSplit[0]
    t = outputTecl(data)
    t.start()