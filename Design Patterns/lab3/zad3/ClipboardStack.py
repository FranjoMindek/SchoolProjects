from Observers import ClipboardObserver
from Stack import Stack


class ClipboardStack:
    def __init__(self):
        self._stack = Stack()
        self._observers = []

    def is_empty(self):
        return self._stack.is_empty()

    def peek(self):
        return self._stack.peek()

    def push(self, string: str):
        self._stack.push(string)
        self._notify_clipboard_observers()

    def pop(self):
        temp = self._stack.pop()
        self._notify_clipboard_observers()
        return temp

    def empty(self):
        self._stack.empty()

    def add_clipboard_observer(self, observer: ClipboardObserver):
        self._observers.append(observer)

    def remove_clipboard_observer(self, observer: ClipboardObserver):
        self._observers.remove(observer)

    def _notify_clipboard_observers(self):
        print("notifying cursor movement")
        for observer in self._observers:
            observer.update_clipboard()


