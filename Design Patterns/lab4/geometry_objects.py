from __future__ import annotations


class Point:
    def __init__(self, x, y):
        self._x = x
        self._y = y

    def get_x(self):
        return self._x

    def get_y(self):
        return self._y

    def translate(self, dp: Point) -> Point:
        return Point(self._x + dp.get_x(), self._y + dp.get_y())

    def difference(self, p: Point) -> Point:
        return Point(self._x - p.get_x(), self._y - p.get_y())


class Rectangle:
    def __init__(self, x, y, width, height):
        self._x = x
        self._y = y
        self._width = width
        self._height = height

    def get_x(self):
        return self._x

    def get_y(self):
        return self._y

    def get_width(self):
        return self._width

    def get_height(self):
        return self._height

    def top_left(self) -> Point:
        return Point(self._x, self._y)

    def top_right(self) -> Point:
        return Point(self._x + self._width, self._y)

    def bot_left(self) -> Point:
        return Point(self._x, self._y + self._height)

    def bot_right(self) -> Point:
        return Point(self._x + self._width, self._y + self._height)

