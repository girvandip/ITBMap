from xml.dom import minidom

doc = minidom.parse('peta_itb_pohon_jalan_temp.svg')  # parseString also exists
path_strings = [path.getAttribute('d') for path
                in doc.getElementsByTagName('path')]

path_colors = [path.getAttribute('stroke') for path
                in doc.getElementsByTagName('path')]

for i in range(len(path_strings)):

    file = open(str(i)+".txt","w")

    path_strings[i] = path_strings[i].replace(',',' ')
    b = path_strings[i].count(' ')
    path_strings[i] = path_strings[i].replace('m',str(b)+' ')
    path_strings[i] = path_strings[i].replace('l', ' ')
    path_strings[i] = path_strings[i].replace('z', ' ')
    line = str(path_strings[i])
    line = line.split(" ")

    while ' ' in line :
         line.remove(' ')
    while '' in line :
        line.remove('')

    x = float(line[1])
    y = float(line[2])
    tempx = float(line[1])
    tempy = float(line[2])
    line = list(map(float, line))
    # print line
    for j in range(len(line)) :
        if (line[j] != ' '):
            if (j > 2) :
                if (j % 2 == 1) :
                    line[j] = (float(tempx) + float(line[j]))
                    tempx = repr(float(line[j]))
                else :
                    line[j] = float(tempy) + float(line[j])
                    tempy = float(line[j])

    maksx = float(line[1])
    minx = float(line[1])
    maksy = float(line[2])
    miny = float(line[2])
    line = list(map(str, line))

    for k in range(len(line)) :
        if (k == 0) :
            print int(round(float(line[k])))
            file.write(str(int(round(float(line[k])))))
            file.write('\n')
        elif ( k < len(line) - 2) :
            if ( k % 2 == 1) :
                print int(round(float(line[k]))),
                print ' ',
                print int(round(float(line[k+1]))),
                print ' ',
                print int(round(float(line[k+2]))),
                print ' ',
                print int(round(float(line[k+3])))

                file.write(str(int(round(float(line[k]))),))
                file.write( ' ',)
                file.write(str(int(round(float(line[k+1]))),))
                file.write( ' ',)
                file.write(str(int(round(float(line[k+2]))),))
                file.write( ' ',)
                file.write(str(int(round(float(line[k+3])))))
                file.write('\n')
        elif ( k == len(line) - 2) :
                print int(round(float(line[k]))),
                print ' ',
                print int(round(float(line[k+1]))),
                print ' ',
                print int(round(float(line[1]))),
                print ' ',
                print int(round(float(line[2])))

                file.write(str(int(round(float(line[k]))),))
                file.write( ' ',)
                file.write(str(int(round(float(line[k+1]))),))
                file.write( ' ',)
                file.write(str(int(round(float(line[1]))),))
                file.write( ' ',)
                file.write(str(int(round(float(line[2])))))
                file.write('\n')
        if (k != 0 ) :
            if (k % 2 == 1) :
                if (maksx < float(line[k])) :
                    maksx = float(line[k])
                if (minx > float(line[k])) :
                    minx = float(line[k])
            else :
                if (maksy < float(line[k])) :
                    maksy = float(line[k])
                if (miny > float(line[k])) :
                    miny = float(line[k])


    print int(round(minx)),
    print ' ',
    print int(round(miny))
    print int(round(maksx)),
    print ' ',
    print int(round(maksy))

    #bottom right and top left Point
    file.write(str(int(round(minx)),))
    file.write( ' ',)
    file.write(str(int(round(miny))))
    file.write('\n')
    file.write(str(int(round(maksx)),))
    file.write( ' ',)
    file.write(str(int(round(maksy))))
    file.write('\n')
    

    if (i > 1) :
        tempcolor = path_colors[i].replace('#','')
        if (len(tempcolor) == 6) :
            n = 2
            colorlist = [tempcolor[i:i+n] for i in range(0, len(tempcolor), n)]
            for a in colorlist :
                print a
                file.write(str(int(a,16))+' ',)
        elif (len(tempcolor) == 3) :
            n = 1

            colorlist = [tempcolor[i:i+n] for i in range(0, len(tempcolor), n)]
            for a in colorlist :
                print a+a
                file.write(str(int(a+a,16))+' ',)
    file.close()
    print '\n'
