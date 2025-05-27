import tkinter as tk
import subprocess

# MQTT Configuration
TOPIC_LIGHT = "room/light/main"
TOPIC_FAN = "room/fan"

def toggle_light(state):
    process = subprocess.run(["mosquitto_pub", "-t", f"{TOPIC_LIGHT}", "-m", f"{state}"])
    return process

def toggle_fan(state):
    process = subprocess.run(["mosquitto_pub", "-t", f"{TOPIC_FAN}", "-m", f"{state}"])
    return process

# GUI Setup
root = tk.Tk()
root.title("Override Dashboard")
root.geometry("320x200")
root.resizable(False, False)

# Light Controls
light_label = tk.Label(root, text="Light Control", font=("Arial", 14))
light_label.pack(pady=(15, 5))

light_frame = tk.Frame(root)
light_frame.pack(pady=5)

light_on_button = tk.Button(light_frame, text="Turn ON", command=lambda: toggle_light("ON"), bg="green", fg="white", width=10)
light_on_button.pack(side=tk.LEFT, padx=10)

light_off_button = tk.Button(light_frame, text="Turn OFF", command=lambda: toggle_light("OFF"), bg="red", fg="white", width=10)
light_off_button.pack(side=tk.LEFT, padx=10)

# Fan Controls
fan_label = tk.Label(root, text="Fan Control", font=("Arial", 14))
fan_label.pack(pady=(15, 5))

fan_frame = tk.Frame(root)
fan_frame.pack(pady=5)

fan_on_button = tk.Button(fan_frame, text="Turn ON", command=lambda: toggle_fan("ON"), bg="green", fg="white", width=10)
fan_on_button.pack(side=tk.LEFT, padx=10)

fan_off_button = tk.Button(fan_frame, text="Turn OFF", command=lambda: toggle_fan("OFF"), bg="red", fg="white", width=10)
fan_off_button.pack(side=tk.LEFT, padx=10)

# Start the GUI loop
root.mainloop()
