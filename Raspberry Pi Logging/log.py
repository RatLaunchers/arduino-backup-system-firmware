from gps import *
import time
from datetime import datetime
import csv

gpsd = gps(mode=WATCH_ENABLE|WATCH_NEWSTYLE)

def getCoords():
    nx = gpsd.next()
    if nx['class'] == 'TPV':
        return getattr(nx, 'lat', "Unknown"), getattr(nx, 'lon', "Unknown")
    return None

print("logging to sensorLog.csv")
print("press ctrl+c to stop execution")

while True:
    coords = getCoords()
    if coords is not None:
        log = open("sensorLog.csv", 'a', newline='')
        writer = csv.writer(log)
        writer.writerow([str(datetime.now()), coords[0], coords[1]])
        log.close()
    time.sleep(5)
