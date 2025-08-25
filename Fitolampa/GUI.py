from tkinter import *
from  tkinter import ttk
from functools import partial
import matplotlib.pyplot as plt
import time

ws  = Tk()
ws.title('База Данных')
ws.geometry('450x300')
ws['bg'] = '#34495e'

db_frame = Frame(ws)
db_frame.pack()

db_scroll = Scrollbar(db_frame)
db_scroll.pack(side=RIGHT, fill=Y)

my_db = ttk.Treeview(db_frame,yscrollcommand=db_scroll.set)
my_db.pack()

db_scroll.config(command=my_db.yview)
db_scroll.config(command=my_db.xview)

my_db['columns'] = ('column_id', 'column_data', 'column_hour', 'column_value')

my_db.column("#0", width=0,  stretch=NO)
my_db.column("column_id",anchor=CENTER, width=80)
my_db.column("column_data",anchor=CENTER,width=110)
my_db.column("column_hour",anchor=CENTER,width=80)
my_db.column("column_value",anchor=CENTER,width=80)

my_db.heading("#0",text="",anchor=CENTER)
my_db.heading("column_id",text="№",anchor=CENTER)
my_db.heading("column_data",text="Дата",anchor=CENTER)
my_db.heading("column_hour",text="Час",anchor=CENTER)
my_db.heading("column_value",text="Значение",anchor=CENTER)

entry_number = 1
x_list = []
y_list = []

day = time.strftime("%d/%m/%Y", time.localtime())
with open('data.csv', 'r') as file: 
    for line in file:
        line = line.replace('\n', '') 
        data = line.split(",")
        if data[0] == day:
            x_list.append(data[1])
            y_list.append(data[2])
        my_db.insert(parent='', index='end', iid=entry_number,text='',
            values=(entry_number, data[0], data[1], data[2]))
        entry_number+=1
my_db.pack()
def fun(y, day):   
    plt.plot(x,y)      
    plt.title("График интенсивность освещения солнца " + day)   
    plt.ylabel('Максимальная интенсивность')   
    plt.xlabel('Час')   
    plt.show() 
