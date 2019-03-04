# Author: Stephen Timmel
# stimmel@vt.edu
# Not for external distribution.

#internal image layout: img[row][column][rgb]
#sample usage: img[5][5]['r']

import struct

def save_ppm_image_8(filename,img):
    f = open(filename,'w');

    #write ppm header
    width = len(img[0])
    height = len(img)
    f.write('P6 ' + str(width) + ' ' + str(height) + ' ' + '255' + '\n')

    for row in img:
        for pixel in row:
            red = struct.pack('@B',pixel['r'])
            green = struct.pack('@B',pixel['g'])
            blue = struct.pack('@B',pixel['b'])
            f.write(red + green + blue)
    f.close()

def load_ppm_image_8(filename):
    f = open(filename,'rb');

    #read ppm header
    header = f.readline().replace('\n','').split(' ')

    #validate header
    assert len(header) == 4, "Incorrect PPM8 header length"              
    assert header[0] == 'P6', "Incorrect PPM8 file format.  Must be P6"  
    assert header[1].isdigit(), "Incorrect PPM8 width.  Must be numeric" 
    assert header[2].isdigit(), "Incorrect PPM8 height. Must be numeric" 
    assert header[3].isdigit(), "Incorrect PPM8 color depth. Must be numeric"
    assert header[3] == '255', "Incorrect PPM8 color depth.  Must be 255"

    #save width and height for later
    width = int(header[1])
    height = int(header[2])
    
    #pull file into an array, three bytes at a time
    img = []
    for h in range(height):
        img.append([])
        for w in range(width):
            img[h].append({})
            data = f.read(3)
            img[h][w]['r'] = int(struct.unpack_from('@B',data,0)[0])
            img[h][w]['g'] = int(struct.unpack_from('@B',data,1)[0])
            img[h][w]['b'] = int(struct.unpack_from('@B',data,2)[0])

    f.close()
    return img

def save_pgm_image_8(filename,img):
    f = open(filename,'w');

    #write ppm header
    width = len(img[0])
    height = len(img)
    f.write('P5 ' + str(width) + ' ' + str(height) + ' ' + '255' + '\n')

    for row in img:
        for pixel in row:
            shade = struct.pack('@B',pixel)
            f.write(shade)
    f.close()

def load_pgm_image_8(filename):
    f = open(filename,'rb');

    #read ppm header
    header = f.readline().replace('\n','').split(' ')

    #validate header
    assert len(header) == 4, "Incorrect PGM8 header length"              
    assert header[0] == 'P5', "Incorrect PGM8 file format.  Must be P5"  
    assert header[1].isdigit(), "Incorrect PGM8 width.  Must be numeric" 
    assert header[2].isdigit(), "Incorrect PGM8 height. Must be numeric" 
    assert header[3].isdigit(), "Incorrect PGM8 color depth. Must be numeric"
    assert header[3] == '255', "Incorrect PGM8 color depth.  Must be 255"

    #save width and height for later
    width = int(header[1])
    height = int(header[2])
    
    #pull file into an array, three bytes at a time
    img = []
    for h in range(height):
        img.append([])
        for w in range(width):
            data = f.read(1)
            img[h].append(int(struct.unpack('@B',data)[0]))

    f.close()
    return img
