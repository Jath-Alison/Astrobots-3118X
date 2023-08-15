import serial
import time
import pandas as pd
import matplotlib.pyplot as plt	
#https://www.vexforum.com/t/getting-an-output-from-code-that-isnt-through-the-vexcode-console/115708/6

data_frame_dict = {}
ser = serial.Serial('COM6', 115200)

try:
    while True:
        reading = True
        while reading:
            data = ser.readline().decode("utf-8")[0:-2]
            if "Data-" in data:
                data = data.split("-")[1]
            else:
                continue
            
            if "End" in data:
                print("end")
                reading = False
                break
                
            data_list = data.split(":")
            
            if data_list[0] in data_frame_dict:
                data_frame_dict[data_list[0]].append(float(data_list[1]))
            else:
                data_frame_dict[data_list[0]] = []
                data_frame_dict[data_list[0]].append(float(data_list[1]))
            print (data_list)
                
                
            
            time.sleep(.05)
        time.sleep(.25)
                
except KeyboardInterrupt:
    print('interrupted!')
print(data_frame_dict)
data_frame = pd.DataFrame(data_frame_dict)
print(data_frame)
data_frame.plot()

plt.show()