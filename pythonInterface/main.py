import serial.tools.list_ports
import tkinter as tk
from tkinter import ttk

class App(tk.Tk):

    def __init__(self):
        super().__init__()
        self.estSerialConnection()
        self.title("Six Axis Robot Arm")
        self.configure(bg='#1E1E1E')  # Dark background for modern look
        
        self.style = ttk.Style(self)
        self.setup_styles()
        self.create_widgets()
        self.update_window_size()
    
    def estSerialConnection(self):
        ports = serial.tools.list_ports.comports()
        serialInst = serial.Serial()
        count  = 0

        portsList = []
        # portvar = ""
        for onePort in ports:
            portsList.append(str(onePort))
            print (str(onePort))

        val = "9"

        for x in range(0,len(portsList)):
            if portsList[x].startswith("COM" + str(val)):
                portvar = "COM" + str(val)
                print (portvar)

        serialInst.baudrate = 115200
        serialInst.port = portvar
        serialInst.open()
    
    def setup_styles(self):
        self.style.configure('TFrame', background='#2C2C2C')
        self.style.configure('TLabel', background='#2C2C2C', foreground='#E8E8E8', font=("Helvetica", 16))
        self.style.configure('TButton', background='#4CAF50', foreground='#FFFFFF', font=("Helvetica", 14, 'bold'))
        self.style.configure('TScale', background='#2C2C2C')
    
    def create_widgets(self):
        # Create the main frame
        main_frame = tk.Frame(self, bg='#1E1E1E')
        main_frame.pack(fill='both', expand=True)
        
        # Create a canvas widget
        self.canvas = tk.Canvas(main_frame, bg='#1E1E1E', highlightthickness=0)
        self.canvas.pack(side='left', fill='both', expand=True)
        
        # Add a scrollbar to the canvas
        scrollbar = ttk.Scrollbar(main_frame, orient='vertical', command=self.canvas.yview)
        scrollbar.pack(side='right', fill='y')
        
        # Configure the canvas with the scrollbar
        self.canvas.configure(yscrollcommand=scrollbar.set)
        
        # Create a frame inside the canvas
        self.scrollable_frame = ttk.Frame(self.canvas)
        
        # Add the frame to a window in the canvas
        self.canvas.create_window((0, 0), window=self.scrollable_frame, anchor='nw')
        
        # Update the scrollregion of the canvas whenever the size of the frame changes
        self.scrollable_frame.bind("<Configure>", lambda e: self.canvas.configure(scrollregion=self.canvas.bbox("all")))
        
        # Bind mouse wheel events to the canvas for scrolling
        self.bind_mouse_wheel(self.canvas)
        
        # Create the title label
        title_label = tk.Label(self.scrollable_frame, text="Six Axis Robot Arm", font=("Helvetica", 30, "bold"), fg="#FFFFFF", bg='#1E1E1E')
        title_label.pack(pady=20)
        
        # Create the slider containers
        for i in range(1, 7):
            self.create_slider_container(self.scrollable_frame, i)
        
        # Create the serial communication button
        serial_button = ttk.Button(self.scrollable_frame, text="Serial Communication", command=self.open_serial_communication)
        serial_button.pack(pady=20)
    
    def bind_mouse_wheel(self, widget):
        # Windows and MacOS use different events for mouse wheel
        widget.bind_all("<MouseWheel>", self.on_mouse_wheel)
        widget.bind_all("<Button-4>", self.on_mouse_wheel)
        widget.bind_all("<Button-5>", self.on_mouse_wheel)
    
    def on_mouse_wheel(self, event):
        # Smooth scrolling by smaller increments
        if event.num == 5 or event.delta == -120:
            self.canvas.yview_scroll(1, "units")
        elif event.num == 4 or event.delta == 120:
            self.canvas.yview_scroll(-1, "units")
    
    def create_slider_container(self, parent, index):
        frame = ttk.Frame(parent, padding="10 10 10 10")
        frame.pack(pady=10, padx=20, fill='x')
        
        label = ttk.Label(frame, text=f"Motor {index} Control", style='TLabel')
        label.pack(pady=10)
        
        slider = ttk.Scale(frame, from_=0, to=100, orient='horizontal', style='TScale')
        slider.pack(pady=10, padx=20, fill='x')
        slider.bind("<Motion>", lambda event, idx=index: self.print_slider_value(idx, slider))
    
    def print_slider_value(self, index, slider):
        value = slider.get()
        print(f"Motor {index} Value: {int(value)}")
    
    def print_slider_to_serial(self, index, slider):
        value = slider.get()
        print(f"Motor {index} Value: {int(value)}")


    def open_serial_communication(self):
        # Function to handle serial communication
        print("Serial Communication Button Pressed")
    
    def update_window_size(self):
        self.update_idletasks()
        window_height = self.scrollable_frame.winfo_height() // 2 + 150  # Adjusting for 3 sliders visibility and additional space
        window_width = self.scrollable_frame.winfo_width() + 20  # Adding padding for scrollbar
        self.geometry(f"{window_width}x{window_height}")

if __name__ == "__main__":
    app = App()
    app.mainloop()
