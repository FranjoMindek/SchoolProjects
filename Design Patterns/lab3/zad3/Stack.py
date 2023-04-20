class Stack:
    def __init__(self):
        self._stack = []

    def __len__(self):
        return len(self._stack)

    def is_empty(self):
        return len(self._stack) == 0

    def peek(self):
        return self._stack[len(self._stack) - 1]

    def push(self, element):
        self._stack.append(element)

    def pop(self):
        return self._stack.pop()

    def empty(self):
        del self._stack
        self._stack = []

