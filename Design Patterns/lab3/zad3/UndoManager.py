from Stack import Stack


class EditAction:
    def execute_do(self):
        pass

    def execute_undo(self):
        pass


class UndoManager(object):
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(UndoManager, cls).__new__(cls)
        return cls._instance

    def __init__(self):
        self._undo_stack = Stack()
        self._redo_stack = Stack()

    def undo(self):
        if not self._undo_stack.is_empty():
            action: EditAction = self._undo_stack.pop()
            self._redo_stack.push(action)
            action.execute_undo()
        else:
            print("Undo stack is empty")

    def redo(self):
        if not self._redo_stack.is_empty():
            action: EditAction = self._redo_stack.pop()
            self._undo_stack.push(action)
            action.execute_do()
        else:
            print("Redo stack is empty")

    def push(self, action: EditAction):
        self._redo_stack.empty()
        self._undo_stack.push(action)

