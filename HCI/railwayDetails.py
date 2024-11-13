import tkinter as tk
from tkinter import messagebox

trains = {
    "12002": {"name": "Shatabdi Express", "arrival": "08:30 AM", "destination": "Mumbai"},
    "12345": {"name": "Rajdhani Express", "arrival": "02:15 PM", "destination": "Delhi"},
    "11056": {"name": "Konark Express", "arrival": "09:00 AM", "destination": "Pune"},
    "12617": {"name": "Mangala Express", "arrival": "05:45 AM", "destination": "Bangalore"},
    "12124": {"name": "Deccan Queen", "arrival": "07:10 PM", "destination": "Pune"},
    "12951": {"name": "Mumbai Rajdhani", "arrival": "04:40 PM", "destination": "Mumbai"},
    "12953": {"name": "August Kranti Rajdhani", "arrival": "05:40 AM", "destination": "Delhi"},
    "12622": {"name": "Tamil Nadu Express", "arrival": "10:30 PM", "destination": "Chennai"},
    "12423": {"name": "Rajdhani Express", "arrival": "10:50 AM", "destination": "Bhubaneswar"},
    "12615": {"name": "Grand Trunk Express", "arrival": "07:10 PM", "destination": "Delhi"},
    "12051": {"name": "Jan Shatabdi", "arrival": "06:00 PM", "destination": "Mumbai"},
    "12779": {"name": "Goa Express", "arrival": "08:00 AM", "destination": "Goa"},
    "12841": {"name": "Coromandel Express", "arrival": "08:15 PM", "destination": "Howrah"},
    "12301": {"name": "Howrah Rajdhani", "arrival": "10:15 AM", "destination": "Howrah"},
    "12903": {"name": "Golden Temple Mail", "arrival": "03:15 PM", "destination": "Amritsar"},
    "12280": {"name": "Taj Express", "arrival": "07:00 AM", "destination": "Agra"}
}


def getInfo():
    try:
        id = trains[id_entry.get()]
        train = id["name"]
        arrival = id["arrival"]
        dest = id["destination"]
        tName.config(text=train)
        result1.config(text=dest)
        result2.config(text=arrival)
    except Exception as e:
        messagebox.showerror(message=f"No Train Found for {e}")


def reset():
    result1.config(text="---")
    result2.config(text="---")
    id_entry.delete(0, 'end')
    tName.config(text="Train Name")


root = tk.Tk()
root.title("Railway Enquiry")
root.minsize(width=500, height=400)
root.config(bg="white")


frame1 = tk.LabelFrame(master=root, text="Enter Info", bg="white")
id_entry_label = tk.Label(
    master=frame1, text="Enter the Train Number for Information", font=("Sans Serif", 10, "bold"), bg="white")
id_entry_label.pack(pady=20)
id_entry = tk.Entry(master=frame1)
id_entry.pack()
idButton = tk.Button(master=frame1, text="Submit",
                     bg="lightgreen", command=getInfo)
idButton.pack()
frame1.pack(padx=10, pady=10, expand=True, fill="both")

frame2 = tk.LabelFrame(master=root, text="Results", bg="white")

tName = tk.Label(master=frame2, text="Train Name", bg="white",
                 font=("Arial", 14, "bold"))
tName.pack(padx=5, pady=5, expand=True, fill='both')

field1 = tk.LabelFrame(master=frame2, text="Destination:", bg="white")
result1 = tk.Label(master=field1, text="---", bg="white")
result1.pack(expand=True, fill='both', pady=10)
field2 = tk.LabelFrame(master=frame2, text="Arrival Time:", bg="white")
result2 = tk.Label(master=field2, text="---", bg="white")
result2.pack(expand=True, fill='both', pady=10)
field1.pack(side='left', expand=True, fill='both', pady=5, padx=5)
field2.pack(side='left', expand=True, fill='both', pady=5, padx=5)

rs_button = tk.Button(master=root, command=reset,
                      text="Reset Results", width=20, bg="grey")
rs_button.pack(side='bottom', padx=10,  expand=True, fill='x')

frame2.pack(padx=10, pady=5, expand=True, fill='both')
root.mainloop()
