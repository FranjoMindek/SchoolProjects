from TextEditorModel import TextEditorModel, UndoManager, ClipboardStack
from tkinter import messagebox as mb
from UndoManager import EditAction


class Plugin:
    def __init__(self):
        pass

    def get_name(self):
        return "Capitalize"

    def get_description(self):
        mb.showinfo("Description", "Plugin which capitalizes first letter of each word.")

    def execute(self, model: TextEditorModel, undo_manager: UndoManager, clipboard_stack: ClipboardStack):
        for i, line in enumerate(model.lines):
            model.lines[i] = line.title()
        undo_manager.push(CapitalizeAction(model))
        model._text_changed = True
        model._notify_changed()


class CapitalizeAction(EditAction):
    def __init__(self, target):
        self._target = target
        pass

    def execute_do(self):
        pass

    def execute_undo(self):
        for i, line in enumerate(self._target.lines):
            words = line.split()
            for j, word in enumerate(words):
                words[j] = word.lower()
            self._target.lines[i] = " ".join(words)
            print(words)
        self._target._text_changed = True
        self._target._notify_changed()
