from Location import Location


class CursorObserver:
    def update_cursor_location(self, loc: Location):
        pass


class TextObserver:
    def update_text(self):
        pass


class ClipboardObserver:
    def update_clipboard(self):
        pass
