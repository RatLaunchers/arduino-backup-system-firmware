import os
import datetime

def jpg():
    time = datetime.datetime.now().strftime("%y-%m-%d %H:%M:%S")
    cmd = os.system("libcamera-jpeg -o \"/data/" + time + ".jpg\"")
    if os.path.exists("/data/" + time + ".jpg") and cmd == 0:
        return "/data/" + time + ".jpg"
    else:
        return None
