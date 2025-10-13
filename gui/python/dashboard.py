import tkinter as tk
import threading
from board import board  
def open_board():
    threading.Thread(target=board).start()
   
# ---------- MAIN WINDOW ----------
window = tk.Tk()
window.title("Chess Dashboard")
window.geometry("500x350")
window.configure(bg="#1e1e1e")

# ---------- HEADER ----------
header = tk.Frame(window, bg="#2d2d2d", pady=15)
header.pack(fill="x")

title = tk.Label(
    header,
    text="♟ Chess Control Dashboard ♟",
    font=("Helvetica", 18, "bold"),
    fg="white",
    bg="#2d2d2d"
)
title.pack()

# ---------- MAIN CONTENT ----------
content = tk.Frame(window, bg="#1e1e1e", pady=40)
content.pack(expand=True, fill="both")

launch_btn = tk.Button(
    content,
    text="Launch Chess Board",
    font=("Arial", 14),
    bg="#3b82f6",
    fg="white",
    activebackground="#2563eb",
    relief="flat",
    width=17,
    padx=20,
    pady=10,
    command=open_board
)

setting_btn = tk.Button(
        content,
        text="Settings",
        font=("Arial", 14),
        bg="#3b82f6",
        fg="white",
        activebackground="#2563eb",
        relief="flat",
        width=17,
        padx=20,
        pady=10,
        command=None

)

exit_btn = tk.Button(
    content,
    text="Exit",
    font=("Arial", 14),
    bg="#ef4444",
    fg="white",
    activebackground="#dc2626",
    relief="flat",
    width=17,
    padx=20,
    pady=10,
    command=window.destroy
)




launch_btn.pack(pady=10)
setting_btn.pack(pady=10)
exit_btn.pack(pady=10)

# ---------- RUN ----------
window.mainloop()
