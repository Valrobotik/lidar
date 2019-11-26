import serial

serialLid = serial.Serial('/dev/ttyACM0', 9600, timeout=0.50)

print (hex (ord ('V')))

def write_cmd(string):
    if (type(string) == type('thisisastring')):
        #command = [0x50, 0x50, 0x0A]
        command = []
        for char in string:
            #command.append(hex( ord(char)))
            command.append( ord(char))
        serialLid.write(command)

def read_cmd():
    f = open("encryptx.txt", 'w+')
    a = 1
    while a:    
        while serialLid.in_waiting:
            data = serialLid.readline()
            print (data)
            f.write(data.decode())
            a = 0

last = ['MS004407250103\n', 'GD0044072501\n']
while True:
    string = input('would you command this lidar ?\n')
    if (string == 'last'):
        print (last)
    else:
        if (string[0] >= '0' and string[0] <= '9'):
            string = last[int(string[0]) % len(last)]
        else:
            string = string + '\n'
        last.append(string)
        write_cmd(string)
        read_cmd()
