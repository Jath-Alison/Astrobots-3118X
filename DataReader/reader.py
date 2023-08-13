import serial                  
import matplotlib.pyplot as plt	
#https://www.vexforum.com/t/getting-an-output-from-code-that-isnt-through-the-vexcode-console/115708/6
# funciton to make two lists at the same length and output them into one list
def two_list_len_same(a, b):
    len_min = min( len(a), len(b) )
    result_a = a[0:len_min]
    result_b = b[0:len_min]
    
    return [result_a, result_b]

# funciton to make three lists at the same length and output them into one list
def three_list_len_same(a, b, c):
    len_min = min( len(a), len(b) , len(c))
    result_a = a[0:len_min]
    result_b = b[0:len_min]
    result_c = c[0:len_min]
    
    return [result_a, result_b, result_c]
    

if __name__ == '__main__':
    # init some varibles
    data_list = [0]                #  A list to store the date transformed from the brain
    cycle_mark = True       # To mark whether to maintain the cycle or not
    
    # create bunch of lists to group the data that transformed from the brain
    time_list = []
    rpm_list = []
    tem_list = []
    
    left_eff_list = []
    right_eff_list = []
    
    left_rpm_list = []
    right_rpm_list = []
    
    fly_temp_list = []
    fly_rpm_list = []
    fly_ema_list = []
    
    # create a picture
    plt.ion()
    plt.figure(1)
    
    # declare(create) a serial port
    ser = serial.Serial('COM6', 115200)
    
    while True:
        while cycle_mark:
            data = ser.readline()       # read the data until read the line break(/n)

            # process the data
            data = data.decode("utf-8")[0:-2]
            data_list = data.split(":")
    
           # group the data

            if data_list[0] == "Time":
                time_list.append(float(data_list[1]))
                
            elif data_list[0] == "DriveRpm":
                rpm_list.append(float(data_list[1]))
                
            elif data_list[0] == "DriveTem":
                tem_list.append(float(data_list[1]))
                
            elif data_list[0] == "LeftEff":
                left_eff_list.append(float(data_list[1]))
                
            elif data_list[0] == "RightEff":
                right_eff_list.append(float(data_list[1]))
                
            elif data_list[0] == "LeftRpm":
                left_rpm_list.append(float(data_list[1]))
                
            elif data_list[0] == "RightRpm":
                right_rpm_list.append(float(data_list[1]))
                
            elif data_list[0] == "FlyTemp":
                fly_temp_list.append( float(data_list[1]) )
                
            elif data_list[0] == "FlyRPM":
                fly_rpm_list.append( float(data_list[1]) )
            
            elif data_list[0] == "FlyEma":
                fly_ema_list.append( float(data_list[1]) )
             
            # cycle_mark == true means that this round of data has been read
            # then this cycle can stop to read the data from the next round 
            elif data_list[0] == "End":
                cycle_mark = False
                            
        cycle_mark = True
        
        tmp_list_a = two_list_len_same(time_list, fly_rpm_list)   # you could change the list to draw differnt data 
        
        # draw the picture                
        plt.clf()
        plt.title("FlyMotorRPM")
        plt.plot(tmp_list_a[0], tmp_list_a[1])
        plt.plot(tmp_list_a[0], tmp_list_a[2])
        plt.draw()
        plt.pause(0.1)