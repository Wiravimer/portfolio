#чтение значений который пересылает Ардуино и сохранение в файл
import serial
file_name = 'XY.txt'
r = serial.Serial("COM4", 9600)
with open(file_name) as file:
    while True:
        t = int(r.readline ())
        file = open(file_name, 'a')
        file.write(f'{str(t)}\n')