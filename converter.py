import customtkinter as ct
from PIL import Image
import tkinter
import os
# dirname = os.path.dirname(__file__)
# filename = os.path.join(dirname, 'test.ico')


def convert_webp_to_png(input_file, output_file):
    """Converts a WebP image to PNG format."""
    try:
        img = Image.open(input_file)
        img.save(output_file)
        status_label.configure(
            text="Conversion successful!", text_color="green")
    except Exception as e:
        status_label.configure(text=f"Error: {str(e)}", text_color="red")


def select_source_file():
    """Opens a file dialog to select the source WebP image."""
    global input_file_var
    file_types = [("WebP files", "*.webp")]
    input_file_path = ct.filedialog.askopenfilename(
        title="Select WebP Image", filetypes=file_types)
    if input_file_path:
        input_file_var.set(input_file_path)


def select_destination_file():
    """Opens a file dialog to select the destination PNG file path."""
    global output_file_var
    file_types = [("PNG files", "*.png")]
    output_file_path = ct.filedialog.asksaveasfilename(
        title="Save PNG File", filetypes=file_types)
    if output_file_path:
        if ".png" not in output_file_path:
            output_file_path += ".png"
        output_file_var.set(output_file_path)


def convert_button_click():
    """Triggers the WebP to PNG conversion based on user input."""
    input_file = input_file_var.get()
    output_file = output_file_var.get()
    if input_file and output_file:
        convert_webp_to_png(input_file, output_file)


def switch_theme():
    """Toggles the theme between light and dark."""
    if switch_var.get() == "on":
        switch_var.set(value="off")
        ct.set_appearance_mode("dark")
        switch.configure(text="Dark Theme")
    else:
        switch_var.set(value="on")
        ct.set_appearance_mode("light")
        switch.configure(text="Light Theme")


root = ct.CTk()
# ico = tkinter.PhotoImage(filename)
# root.wm_iconbitmap(ico)
root.title("WebP to PNG Converter")

root.minsize(350, 300)

frame = ct.CTkFrame(master=root, corner_radius=10,
                    bg_color="#808080")
frame.pack(fill="both", expand=True)

input_file_label = ct.CTkLabel(
    master=frame, text="Source WebP File:", font=("Arial", 12))
input_file_label.pack(pady=5)

input_file_var = ct.StringVar()
input_file_entry = ct.CTkEntry(
    master=frame, textvariable=input_file_var, font=("Arial", 12), width=200)
input_file_entry.pack(pady=5)

select_source_button = ct.CTkButton(
    master=frame,
    text="Browse",
    command=select_source_file,
    font=("Arial", 10),
    hover_color="#404040",
)
select_source_button.pack(pady=5)

output_file_label = ct.CTkLabel(
    master=frame, text="Destination PNG File:", font=("Arial", 12))
output_file_label.pack(pady=5)

output_file_var = ct.StringVar()
output_file_entry = ct.CTkEntry(
    master=frame, textvariable=output_file_var, font=("Arial", 12), width=200)
# Adjust width for responsiveness
output_file_entry.pack(pady=5)

select_destination_button = ct.CTkButton(
    master=frame,
    text="Browse",
    command=select_destination_file,
    font=("Arial", 10),
    hover_color="#404040",
)
select_destination_button.pack(pady=5)

# Create a stylish CTkButton for conversion
convert_button = ct.CTkButton(
    master=frame,
    text="Convert",
    command=convert_button_click,
    font=("Arial", 12),
    # hover_color="",
    fg_color=("white", "#B78428"),
)
convert_button.pack(pady=10)

theme_label = ct.CTkLabel(master=root, text="Theme:",
                          font=("Arial", 16, "bold"))
theme_label.pack()

status_label = ct.CTkLabel(master=frame, text="")
status_label.pack()

# Create a CTkSwitch for theme selection with initial indicator
switch_var = ct.StringVar(value=0)
switch = ct.CTkSwitch(
    master=root,
    text="Dark Theme",
    font=("Arial", 12),
    command=switch_theme,
    onvalue="on",
    offvalue="off",
)
switch.pack(pady=5)


root.mainloop()
