import os, platform

def clearTerminal():
    if platform.system() == "Windows":
        clear = "cls"
    else:
        clear = "clear"
    os.system(clear)
