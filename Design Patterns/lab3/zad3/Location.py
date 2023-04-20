class Location:
    def __init__(self, row, col):
        self.row: int = row
        self.col: int = col


class LocationRange:
    def __init__(self, start: Location or None, end: Location or None):
        self.start: Location = start
        self.end: Location = end

