from tkinter import *

def openNewWindow():
    newWindow = Toplevel(root)
    newWindow.title("New page")
    newWindow.geometry("700x400")

def main():
    button = Button(root, text="Click me", command=openNewWindow)
    button.pack()

if __name__ == "__main__":
    main()