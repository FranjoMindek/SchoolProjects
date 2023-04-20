from TextEditorModel import TextEditorModel
from tkinter import Canvas
from Observers import CursorObserver, TextObserver
from Location import Location


class TextEditor(Canvas, CursorObserver, TextObserver):
    def __init__(self, root, **kwargs):
        self.model: TextEditorModel = kwargs.pop("model")
        super().__init__(root, **kwargs)
        self.model.add_cursor_observer(self)
        self.model.add_text_observer(self)
        self._col = 0
        self._row = 0  # Cursor cache
        self._render_text()
        self._render_cursor()

    def render(self):
        self.delete("all")
        self.create_rectangle(0, 0, self.winfo_width(), self.winfo_height(), fill="white")
        self._render_text()
        self._render_cursor()

    def update_cursor_location(self, loc: Location):
        self._col = loc.col
        self._row = loc.row
        self.render()

    def update_text(self):
        self.render()

    def _render_cursor(self):
        x = self._col*20*0.8
        y = self._row*30
        self.create_rectangle(x, y, x + 5, y + 20, fill="red", outline="red")

    def _render_text(self):
        iterator = self.model.all_lines()
        row = 0
        while True:
            try:
                line = next(iterator)
                self.create_text(0, row * 30, text=line, anchor='nw', font=('Courier', 20), fill='black')
                selection = self.model.get_selection_range()
                if selection is not None:
                    if row == selection.start.row == selection.end.row:
                        self.create_text(selection.start.col*20*0.8, row * 30, text=line[selection.start.col:selection.end.col], anchor='nw', font=('Courier', 20), fill='red')
                    elif row == selection.start.row:
                        self.create_text(selection.start.col * 20 * 0.8, row * 30,text=line[selection.start.col:], anchor='nw',font=('Courier', 20), fill='red')
                    elif selection.start.row < row < selection.end.row:
                        self.create_text(0, row * 30, text=line, anchor='nw', font=('Courier', 20), fill='red')
                    elif row == selection.end.row:
                        self.create_text(0, row * 30, text=line[:selection.end.col], anchor='nw', font=('Courier', 20), fill='red')
                row += 1
            except StopIteration as err:
                break
