import serial.tools.list_ports


ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()
count  = 0


portsList = []
# portvar = ""
for onePort in ports:
    portsList.append(str(onePort))
    print (str(onePort))

val = "8"

for x in range(0,len(portsList)):
    if portsList[x].startswith("COM" + str(val)):
        portvar = "COM" + str(val)
        print (portvar)

serialInst.baudrate = 9600
serialInst.port = portvar
serialInst.open()

isTest= True
while isTest:
    getStr = input("Enter val sXYYY")
    # cmd = "INJD"
    serialInst.write(getStr.encode('utf-8'))
