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
        
    for i in range(len(line)) :
        if (i == 0) :
            print line[i]
        elif ( i < len(line)-2) :
            if (i % 4 == 1 or i % 4 == 2) :
                print line[i],
            elif ( i % 4 == 3) :
                print line[i],
                print line[i+1]
                print line[i],
                print line[i+1],
            else :
                print line[i]
                print '\n'

