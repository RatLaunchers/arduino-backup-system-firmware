from gps3.agps3threaded import AGPS3mechanism
import time
from datetime import datetime
import csv

print("logging to sensorLog.csv")
print("press ctrl+c to stop execution")

agps_thread = AGPS3mechanism()
agps_thread.stream_data()
agps_thread.run_thread()

while True:
    log = open("sensorLog.csv", 'a', newline='')
    writer = csv.writer(log)
    writer.writerow([
        str(datetime.now()),
        agps_thread.data_stream.lat,
        agps_thread.data_stream.lon
        ])
    log.close()
    time.sleep(1)
