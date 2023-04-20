import tkinter
from tkinter import Frame, StringVar, Label
from TextEditorModel import TextEditorModel
from Observers import TextObserver, CursorObserver


class InfoPanel(Frame, TextObserver, CursorObserver):
    def __init__(self, model: TextEditorModel, root, **kwargs):
        super().__init__(root, **kwargs)
        model.add_text_observer(self)
        model.add_cursor_observer(self)
        self._lines = model.lines
        self.cursor_info = StringVar(value="Row:0 Col:0")
        self.lines_info = StringVar(value=f"Lines{len(model.lines)}")
        Label(self, textvariable=self.cursor_info).pack(side=tkinter.RIGHT)
        Label(self, textvariable=self.lines_info).pack(side=tkinter.LEFT)

    def update_text(self):
        self.lines_info.set(f"Lines:{len(self._lines)}")

    def update_cursor_location(self, loc):
        self.cursor_info.set(f"Row:{loc.row} Col:{loc.col}")




