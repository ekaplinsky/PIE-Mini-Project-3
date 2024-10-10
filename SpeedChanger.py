# pylint: disable=invalid-name
""" 
SpeedChanger.py file: 
creates a popup window that communicates with arduino to change the speed of the car
"""

import tkinter as tk

import serial

arduino_com_port = "/dev/ttyACM0"  # pylint: disable=invalid-name
baud_rate = 9600  # pylint: disable=invalid-name

serial_port = serial.Serial(arduino_com_port, baud_rate, timeout=1)


# function that runs when the button is clicked in the popup window
def change_speed_clicked():
    """
    when the button is clicked, it writes the int 2000 to serial
    this gets picked up in the arduino code, which will change the speed of the
    car.
    """
    serial_port.write(2000)
    print(f"changing speed to {int(a.get())}")


# initializing the popup called 'root' and setting it's size
root = tk.Tk()
root.geometry("700x350")

tk.Label(root, text="Enter Speed (0-255)").pack()
a = tk.Entry(root, width=35)
a.pack()

button = tk.Button(
    root,
    text="Change Speed",
    command=change_speed_clicked,
    activebackground="blue",
    activeforeground="white",
    anchor="center",
    bd=3,
    bg="lightgray",
    cursor="hand2",
    disabledforeground="gray",
    fg="black",
    font=("Arial", 14),
    height=2,
    highlightbackground="black",
    highlightcolor="green",
    highlightthickness=2,
    justify="center",
    overrelief="raised",
    padx=10,
    pady=5,
    width=15,
    wraplength=100,
)
button.pack(padx=20, pady=20)
root.mainloop()
