import copy
# import matplotlib.pyplot as plt
# import numpy as np

def main():

    file_path = input("Input file: ")
    
    f = open(file_path + ".txt", "rt")
    
    paths = []
    
    started = False
    points = []
    for l in f:
        
        
        if l[0] == '#':
            # print("Config found")
            
            if started:
                # print(f"Path added: {points}")
                paths.append(copy.deepcopy(points))
                points.clear()
            
            started = True
            continue
        
        if l[0] == "\n":
            continue
                
        p = l.split(",")
        
        # print(f"Point added: {p}")
        points.append(p)
                
        pass

    f.close()
    
    f = open("PathsOut.txt", "w")
    
    for path in paths:
        for point in path:
            # print(f"x: {point[0]}, y: {point[1]}, speed: {point[2]}")
            f.write(f"Jath::Point({point[0]}, {point[1]}, {point[2][0:-1]}), ")
            
        f.write("\n")
    f.close()

if __name__ == "__main__":
    main()