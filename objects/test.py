from xml.dom import minidom

doc = minidom.parse("peta_itb.svg")  # parseString also exists
path_strings = [path.getAttribute('d') for path
                in doc.getElementsByTagName('path')]

for i in range(len(path_strings)):

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

    for i in range(len(line)) :
        if (line[i] != ' '):
            if (i > 2) :
                if (i % 2 == 1) :
                    line[i] = x + float(line[i])
                else :
                    line[i] = y + float(line[i])

    maksx = float(line[1])
    minx = float(line[1])
    maksy = float(line[2])
    miny = float(line[2])    
    for i in range(len(line)) :
        if (i == 0) :
            print line[i]
        elif ( i < len(line) - 2) :
            if ( i % 2 == 1) :
                print int(round(float(line[i]))),
                print ' ',
                print int(round(float(line[i+1]))),
                print ' ',
                print int(round(float(line[i+2]))),
                print ' ',
                print int(round(float(line[i+3])))

        elif ( i == len(line) - 2) :
                print int(round(float(line[i]))),
                print ' ',
                print int(round(float(line[i+1]))),
                print ' ',
                print int(round(float(line[1]))),
                print ' ',
                print int(round(float(line[2])))
        if (i != 0 ) :
            if (i % 2 == 1) :
                if (maksx < float(line[i])) :
                    maksx = float(line[i])
                if (minx > float(line[i])) :
                    minx = float(line[i])
            else :
                if (maksy < float(line[i])) :
                    maksy = float(line[i])
                if (miny > float(line[i])) :
                    miny = float(line[i])

    
    print int(round(minx)),
    print ' ',
    print int(round(miny))
    print int(round(maksx)),
    print ' ',
    print int(round(maksy))
    print '\n'