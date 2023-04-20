from Location import Location, LocationRange
from Observers import CursorObserver, TextObserver
from copy import deepcopy
from ClipboardStack import ClipboardStack
from UndoManager import UndoManager, EditAction


class TextEditorModel:
    def __init__(self, initial_text: str = None):
        if initial_text is not None:
            initial_text.replace('\t', "   ")
            self.lines = initial_text.splitlines()
        else:
            self.lines = []
        self._cursor: Location = Location(0, 0)
        self.selection: LocationRange = LocationRange(None, None)  # None = doesnt exist
        self._start: int = 0
        self._end: int = 0
        self._cursor_observers = []
        self._text_observer = []
        self._shift: bool = False
        self.clipboard_stack = ClipboardStack()
        self.undo_manager = UndoManager()
        self._text_changed: bool = False
        self._cursor_changed: bool = False
        self._inside_undo_redo: bool = False

    # Iteration
    def __iter__(self):
        return self

    def __next__(self):
        if self._start < self._end:
            self._start += 1
            return self.lines[self._start-1]
        else:
            raise StopIteration

    def all_lines(self):
        self._start = 0
        self._end = len(self.lines)
        return iter(self)

    def range_lines(self, start, end):
        self._start = start
        self._end = end
        return iter(self)

    # Getters and setters
    def set_selection_range(self, selection):
        self.selection = selection
        self._shift = True

    def get_selection_range(self):
        if self.selection.start is not None and self.selection.end is not None:
            if self.selection.start.row < self.selection.end.row or (self.selection.start.row == self.selection.end.row and self.selection.start.col < self.selection.end.col):
                return self.selection
            else:
                temp = deepcopy(self.selection)
                temp2 = temp.start
                temp.start = temp.end
                temp.end = temp2
                del temp2
                return temp
        else:
            return None

    def set_cursor(self, cursor: Location):
        self._cursor = cursor
        self._cursor_changed = True

    def get_cursor(self):
        return self._cursor

    # Some selection logic
    def stop_selection(self):
        self._shift = False
        self.selection.start = None
        self.selection.end = None
        self._text_changed = True

    def _calculate_selection(self):
        if self._shift:
            if self.selection.start is None:
                self.selection.start = deepcopy(self._cursor)
            else:
                self.selection.end = deepcopy(self._cursor)

    # Observers
    def add_text_observer(self, observer: TextObserver):
        self._text_observer.append(observer)

    def remove_text_observer(self, observer: TextObserver):
        self._text_observer.remove(observer)

    def _notify_text_observers(self):
        # print("notifying text change")
        for observer in self._text_observer:
            observer.update_text()

    def add_cursor_observer(self, observer: CursorObserver):
        self._cursor_observers.append(observer)

    def remove_cursor_observer(self, observer: CursorObserver):
        self._cursor_observers.remove(observer)

    def _notify_cursor_observers(self):
        # print("notifying cursor movement")
        for observer in self._cursor_observers:
            observer.update_cursor_location(self._cursor)

    def _notify_changed(self):
        if self._text_changed:
            self._notify_text_observers()
            self._text_changed = False
        if self._cursor_changed:
            self._notify_cursor_observers()
            self._cursor_changed = False

    # Logic behind text
    def delete_before(self):
        if self._shift:
            self.delete_range()
        else:
            if 0 < self._cursor.col <= len(self.lines[self._cursor.row]):
                if not self._inside_undo_redo:
                    self.undo_manager.push(DeleteBeforeActionChar(self, self.lines[self._cursor.row][self._cursor.col-1:self._cursor.col-0],
                                                                  Location(self._cursor.row, self._cursor.col),
                                                                  Location(self._cursor.row, self._cursor.col - 1)))
                self.lines[self._cursor.row] = self.lines[self._cursor.row][:self._cursor.col - 1] + \
                                               self.lines[self._cursor.row][self._cursor.col:]
                self._cursor.col -= 1
            elif self._cursor.col == 0 and self._cursor.row > 0:
                if not self._inside_undo_redo:
                    self.undo_manager.push(DeleteBeforeActionLine(self, self._cursor.row, len(self.lines[self._cursor.row-1])))
                self.set_cursor(Location(self._cursor.row-1, len(self.lines[self._cursor.row-1])))
                self.lines[self._cursor.row] += self.lines[self._cursor.row+1]
                del self.lines[self._cursor.row+1]
            else:
                return
            self._text_changed = True
            self._cursor_changed = True

    def delete_after(self):
        if self._shift:
            return self.delete_range()
        else:
            if self._cursor.col < len(self.lines[self._cursor.row]):
                if not self._inside_undo_redo:
                    self.undo_manager.push(DeleteAfterActionChar(self, self.lines[self._cursor.row][self._cursor.col:self._cursor.col+1],
                                                                 Location(self._cursor.row, self._cursor.col)))
                self.lines[self._cursor.row] = self.lines[self._cursor.row][:self._cursor.col] + \
                                               self.lines[self._cursor.row][self._cursor.col + 1:]
            elif len(self.lines[self._cursor.row]) == self._cursor.col and len(self.lines)-1 > self._cursor.row:
                if not self._inside_undo_redo:
                    self.undo_manager.push((DeleteAfterActionLine(self, self._cursor.row+1, self._cursor.col)))
                self.lines[self._cursor.row] += self.lines[self._cursor.row+1]
                del self.lines[self._cursor.row+1]
            else:
                return
            self._text_changed = True

    def delete_range(self):
        selection: LocationRange = self.get_selection_range()
        if selection is not None:
            deleted = ""
            for i in range(selection.start.row, selection.end.row + 1):
                if i == selection.start.row == selection.end.row:
                    deleted += self.lines[i][selection.start.col:selection.end.col]
                    self.lines[i] = self.lines[i][:selection.start.col] + self.lines[i][selection.end.col:]
                elif i == selection.start.row:
                    deleted += self.lines[i][selection.start.col:] + '\n'
                    self.lines[i] = self.lines[i][:selection.start.col]
                elif i == selection.end.row:
                    deleted += self.lines[i][:selection.end.col]
                    self.lines[selection.start.row] += self.lines[i][selection.end.col:]
                    self.lines[i] = ''
                else:
                    deleted += self.lines[i] + '\n'
                    self.lines[i] = ''
            if not self._inside_undo_redo:
                self.undo_manager.push(DeleteRangeAction(self, deleted, deepcopy(selection)))
            # print(f"{selection.start.row} {selection.end.row}")
            for i in reversed(range(selection.start.row, selection.end.row+1)):
                if self.lines[i] == '' and not i == 0:
                    del self.lines[i]
            # self.lines = [line for i, line in enumerate(self.lines) if line != '' or i <= selection.start.row or i > selection.end.row]
            self._cursor = selection.start
            self.stop_selection()
            self._text_changed = True
            self._cursor_changed = True

    def insert_char(self, char):
        move: int = 1
        if char == '\t':
            char = '   '
            move = 3
        if not self._inside_undo_redo:
            self.undo_manager.push(InsertCharAction(self, char, deepcopy(self._cursor)))
        self.lines[self._cursor.row] = self.lines[self._cursor.row][:self._cursor.col] + char + self.lines[self._cursor.row][self._cursor.col:]
        self._cursor.col += move
        self._text_changed = True
        self._cursor_changed = True

    def insert_string(self, string: str):
        string.replace('\t', "   ")  # inace imamo problem s renderiranjem pokazivaca
        lines = string.splitlines()
        start = deepcopy(self._cursor)
        if len(lines) == 1:
            self.lines[self._cursor.row] = self.lines[self._cursor.row][:self._cursor.col] + \
                                           lines[0] + self.lines[self._cursor.row][self._cursor.col:]
            self._cursor.col += len(lines[0])
        else:
            leftover: str = ''
            for i, line in enumerate(lines):
                if i == 0:  # first
                    leftover = self.lines[self._cursor.row][self._cursor.col:]
                    self.lines[self._cursor.row] = self.lines[self._cursor.row][:self._cursor.col] + line
                elif i == len(lines)-1:  # last
                    self.lines.insert(self._cursor.row + i, line + leftover)
                    self._cursor.row += i
                    self._cursor.col = len(line)
                else:  # else
                    self.lines.insert(self._cursor.row + i, line)
        end = deepcopy(self._cursor)
        self.undo_manager.push(InsertStringAction(self, "", LocationRange(start, end)))
        self.stop_selection()
        self._text_changed = True
        self._cursor_changed = True

    def line_break(self):
        self.lines.insert(self._cursor.row + 1, self.lines[self._cursor.row][self._cursor.col:])
        self.lines[self._cursor.row] = self.lines[self._cursor.row][:self._cursor.col]
        self._cursor.col = 0
        self._cursor.row += 1
        self._text_changed = True
        self._cursor_changed = True

    def copy_range(self, event=None):
        selection: LocationRange = self.get_selection_range()
        if selection is not None:
            text = ''
            for i in range(selection.start.row, selection.end.row + 1):
                if i == selection.start.row == selection.end.row:
                    text += self.lines[i][selection.start.col:selection.end.col]
                elif i == selection.start.row:
                    text += self.lines[i][selection.start.col:] + "\n"
                elif i == selection.end.row:
                    text += self.lines[i][:selection.end.col]
                else:
                    text += self.lines[i] + "\n"
            self.clipboard_stack.push(text)

    def cut_range(self):
        self.copy_range()
        self.delete_range()

    def paste_range(self):
        if not self.clipboard_stack.is_empty():
            self.insert_string(self.clipboard_stack.peek())

    def paste_range_pop(self):
        if not self.clipboard_stack.is_empty():
            self.insert_string(self.clipboard_stack.pop())

    def move_cursor_left(self):
        self._calculate_selection()
        if self._cursor.col == 0:  # if at the end of row
            if self._cursor.row > 0:  # move down if you can
                self._cursor.row -= 1
                self._cursor.col = len(self.lines[self._cursor.row])
                self._calculate_selection()
                self._cursor_changed = True
        else:
            self._cursor.col -= 1
            self._calculate_selection()
            self._cursor_changed = True

    def move_cursor_right(self):
        self._calculate_selection()
        if self._cursor.col >= len(self.lines[self._cursor.row]):  # if at the end of row
            if self._cursor.row < len(self.lines) - 1:  # move down if you can
                self._cursor.row += 1
                self._cursor.col = 0
                self._calculate_selection()
                self._cursor_changed = True
        else:
            self._cursor.col += 1
            self._calculate_selection()
            self._cursor_changed = True

    def move_cursor_up(self):
        self._calculate_selection()
        if self._cursor.row > 0:
            self._cursor.row -= 1
            if self._cursor.col >= len(self.lines[self._cursor.row]):
                self._cursor.col = len(self.lines[self._cursor.row])
            self._calculate_selection()
            self._cursor_changed = True

    def move_cursor_down(self):
        self._calculate_selection()
        if self._cursor.row < len(self.lines)-1:
            self._cursor.row += 1
            if self._cursor.col >= len(self.lines[self._cursor.row]):
                self._cursor.col = len(self.lines[self._cursor.row])
            self._calculate_selection()
            self._cursor_changed = True

    def read_file(self, name: str):
        f = open(name, "r")
        del self.lines
        self.lines = f.readlines()
        f.close()
        for line in self.lines:
            line.replace('\t', "   ")
        self._text_changed = True

    def save_file(self, name: str):
        f = open(name, "w")
        f.writelines(line + '\n' for line in self.lines)
        f.close()
        self._text_changed = True

    def clear_lines(self):
        del self.lines
        self.lines = [""]
        self.set_cursor(Location(0, 0))
        self._text_changed = True

    # Actions for inputs
    def on_start(self, event=None):
        self.set_cursor(Location(0, 0))
        self._notify_changed()

    def on_end(self, event=None):
        if len(self.lines) > 0:
            self.set_cursor(Location(len(self.lines)-1, len(self.lines[len(self.lines)-1])))
            self._notify_changed()

    def on_clear(self, event=None):
        self.clear_lines()
        self._notify_changed()

    def on_save(self, name: str, event=None):
        self.save_file(name)
        self._notify_changed()

    def on_open(self, name: str, event=None):
        self.read_file(name)
        self._notify_changed()

    def on_copy(self, event=None):
        self.copy_range()
        self._notify_changed()

    def on_cut(self, event=None):
        self.cut_range()
        self._notify_changed()

    def on_paste(self, event=None):
        self.paste_range()
        self._notify_changed()

    def on_shift_paste(self, event=None):
        self.paste_range_pop()
        self._notify_changed()

    def on_undo(self, event=None):
        self._inside_undo_redo = True
        self.undo_manager.undo()
        self._inside_undo_redo = False
        self._notify_changed()

    def on_redo(self, event=None):
        self._inside_undo_redo = True
        self.undo_manager.redo()
        self._inside_undo_redo = False
        self._notify_changed()

    def on_backspace(self, event=None):
        self.delete_before()
        self._notify_changed()

    def on_delete(self, event=None):
        self.delete_after()
        self._notify_changed()

    def on_delete_section(self, event=None):
        if self._shift:
            self.delete_range()
        self._notify_changed()

    def on_enter(self, event=None):
        self.line_break()
        self._notify_changed()

    def on_shift_press(self, event=None):
        if self._shift:  # ovo samo jer shift-off ne radi zbog nekog razloga
            self.stop_selection()
        else:
            self._shift = True
        self._notify_changed()

    def on_shift_release(self, event=None):  # ne radi
        self.stop_selection()
        self._notify_changed()

    def on_up(self, event=None):
        self.move_cursor_up()
        self._notify_changed()

    def on_down(self, event=None):
        self.move_cursor_down()
        self._notify_changed()

    def on_left(self, event=None):
        self.move_cursor_left()
        self._notify_changed()

    def on_right(self, event=None):
        self.move_cursor_right()
        self._notify_changed()

    def on_key_press(self, event):
        if event.char != "" and event.keycode != 9:  # 9 = escape
            self.insert_char(event.char)
        self._notify_changed()


class DeleteBeforeActionChar(EditAction):
    def __init__(self, target: TextEditorModel, char: str, cursor_before: Location, cursor_after: Location):
        self._target: TextEditorModel = target
        self._char: str = char
        self._cursor_before: Location = cursor_before
        self._cursor_after: Location = cursor_after

    def execute_do(self):
        pass
        # self._target.set_cursor(self._cursor_before)
        # self._target.delete_before()

    def execute_undo(self):
        self._target.set_cursor(self._cursor_after)
        self._target.insert_char(self._char)


class DeleteBeforeActionLine(EditAction):
    def __init__(self, target: TextEditorModel, row: int, col: int):
        self._target = target
        self._row = row
        self._col = col

    def execute_do(self):
        pass

    def execute_undo(self):
        self._target.lines.insert(self._row, self._target.lines[self._row-1][self._col:])
        self._target.lines[self._row-1] = self._target.lines[self._row-1][:self._col]
        temp = self._target.get_cursor()
        temp.row = self._row
        temp.col = 0
        self._target._text_changed = True
        self._target._cursor_changed = True


class DeleteAfterActionChar(EditAction):
    def __init__(self, target: TextEditorModel, char: str, cursor: Location):
        self._target: TextEditorModel = target
        self._char: str = char
        self._cursor: Location = cursor

    def execute_do(self):
        pass

    def execute_undo(self):
        self._target.set_cursor(self._cursor)
        self._target.insert_char(self._char)
        self._target.move_cursor_left()


class DeleteAfterActionLine(EditAction):
    def __init__(self, target: TextEditorModel, row: int, col: int):
        self._target = target
        self._row = row
        self._col = col

    def execute_do(self):
        pass

    def execute_undo(self):
        self._target.lines.insert(self._row, self._target.lines[self._row-1][self._col:])
        self._target.lines[self._row-1] = self._target.lines[self._row-1][:self._col]
        temp = self._target.get_cursor()
        temp.row = self._row-1
        temp.col = self._col
        self._target._text_changed = True
        self._target._cursor_changed = True


class DeleteRangeAction(EditAction):
    def __init__(self, target: TextEditorModel, lines: str, range: LocationRange):
        self._target = target
        self._lines = lines
        self._range = range

    def execute_do(self):
        pass

    def execute_undo(self):
        self._target.set_cursor(deepcopy(self._range.start))
        self._target.insert_string(self._lines)
        # self._target.insert_string()
        # self


class InsertCharAction(EditAction):
    def __init__(self, target: TextEditorModel, char: str, before: Location):
        self._target = target
        self._char = char
        self._before = before

    def execute_do(self):
        pass

    def execute_undo(self):
        self._target.set_cursor(deepcopy(self._before))
        if self._char == '   ':
            self._target.delete_after()
            self._target.delete_after()
            self._target.delete_after()
        else:
            self._target.delete_after()


class InsertStringAction(EditAction):
    def __init__(self, target: TextEditorModel, lines: str, range: LocationRange):
        self._target = target
        self._lines = lines
        self._range = range

    def execute_do(self):
        pass

    def execute_undo(self):
        self._target.set_selection_range(self._range)
        self._target.delete_range()

