import math

map = [[0 for i in range(200)] for j in range(200)]


walls = {
    1: [[40,40],[40,160]],
    2: [[40,160],[160,40]]
}

for k in walls.keys():
    x=walls[k][0][0]
    y=walls[k][0][1]
    difx=walls[k][1][0]-walls[k][0][0]
    dify=walls[k][1][1]-walls[k][0][1]
    dif = math.sqrt(difx**2+dify**2)
    stepx = difx/dif
    stepy = dify/dif
    while abs(x - walls[k][0][0])< abs(difx) or abs(y-walls[k][1][0])<abs(dify):
        x += stepx
        y += stepy
        print(int(x), end=" ")
        print(int(y))
        print(map[int(x)][int(y)])
        map[int(x)][int(y)] = 1
        print(map[int(x)][int(y)])

file = open("map.txt","w")
for x in map:
    for y in x:
        if y == 0:
            file.write("0")
            file.write(" ")
            print(" ",end=" ")
        else:
            file.write("1")
            file.write(" ")
            print("X",end=" ")
    file.write("\n")
    print()