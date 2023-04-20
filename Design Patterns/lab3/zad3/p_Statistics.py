from tkinter import messagebox as mb
from TextEditorModel import TextEditorModel, UndoManager, ClipboardStack


class Plugin:
    def __init__(self):
        pass

    def get_name(self):
        return "Statistics"

    def get_description(self):
        mb.showinfo("Description", "Plugin which counts number of rows, words and characters in a document.")

    def execute(self, model: TextEditorModel, undo_manager: UndoManager, clipboard_stack: ClipboardStack):
        lines = len(model.lines)
        words = 0
        characters = 0
        for line in model.lines:
            words += len(line.split())
            characters += len(line)
        mb.showinfo("Statistics info", f"There are {lines} lines, {words} words and {characters} characters in the document.")
