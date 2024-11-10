from PIL import Image, ImageOps
import customtkinter as ctk
from tkinter import ttk
import tkinter as tk

filetype = [("All Files", "*.*"),("PNG files", "*.png"),("WebP files", "*.webp"), ("JPEG files", "*.jpeg"), ("JPG files", "*.jpg")]
def convert_file(inputfile: str, outputfile: str):
    try:
        img = ImageOps.invert(Image.open(inputfile).convert('RGB'))
        img.save(outputfile)
        statuslabel.config(
            text="Conversion successful!",
            fg="#276221",
        )
    except Exception as e:
        print(e)
        statuslabel.config(
            text="Something went wrong!",
            fg="#DE0A26"
        )

def select_input():
    "Opens a file dialog for inputfile"
    global in_file_var
    in_file_path = tk.filedialog.askopenfilename(
        title="Select Input Image",
        filetypes=filetype
    )
    if in_file_path:
            in_file_var.set(in_file_path)

def select_output():
    "Opens a file dialog for inputfile"
    global out_file_var
    out_file_path = tk.filedialog.asksaveasfilename(
        title="Save Image",
        filetypes=filetype
    )
    if out_file_path:
            out_file_var.set(out_file_path)



def submit():
    inputfile = in_file_var.get()
    outputfile = out_file_var.get()
    if inputfile and outputfile:
        convert_file(inputfile, outputfile)
    else:
        statuslabel.config(
            text="Input and Output Paths Cannot be empty",
            fg="#F4BC1C",
        )



root = tk.Tk()

root.title("Invert Image")
root.minsize(350,300)

frame = ttk.LabelFrame(master=root, text="Invert Image")
label = ttk.Label(master=frame, text="Source Image:").pack(pady=5)
in_file_var = tk.StringVar()
input_file_entry = ctk.CTkEntry(
    master=frame, textvariable=in_file_var, width=200).pack(pady=5)
frame.pack(fill="both", expand=True, padx=10, pady=10)

select_input_button= ttk.Button(
    master=frame,
    text="Browse",
    command=select_input,
).pack()

labelout = ttk.Label(master=frame, text="Destination Image:").pack(pady=5)
out_file_var = tk.StringVar()
output_file_entry = ctk.CTkEntry(
    master=frame, textvariable=out_file_var, width=200).pack(pady=5)
frame.pack(fill="both", expand=True, padx=10, pady=10)

select_output_button= ttk.Button(
    master=frame,
    text="Browse",
    command=select_output,
).pack()

convertbutton = ctk.CTkButton(
    master=frame,
    text="Convert",
    command=submit,
).pack(pady=10)

global statuslabel
statuslabel= tk.Label(master=frame, text="")
statuslabel.pack()

root.mainloop()



