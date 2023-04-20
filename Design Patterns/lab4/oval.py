from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from i_renderer import Renderer
    from i_graphical_object import GraphicalObject

from math import sqrt
from copy import deepcopy

from abstract_graphical_object import AbstractGraphicalObject
from geometry_objects import Point, Rectangle
from geometry_utilities import GeometryUtil


class Oval(AbstractGraphicalObject):
    def __init__(self, right: Point = Point(20, 0), bottom: Point = Point(0, 20)):
        super().__init__([right, bottom])

    def selection_distance(self, mouse_point: Point) -> float:
        box = self.get_bounding_box()
        if box.get_x() < mouse_point.get_x() < box.get_x() + box.get_width() and box.get_y() < mouse_point.get_y() < box.get_y() + box.get_height():
            return 0
        # print("mouse get x", mouse_point.get_x(), " box get x", box.get_x())
        if mouse_point.get_x() < box.get_x():
            return GeometryUtil.distance_from_line_segment(mouse_point, box.top_left(), box.bot_left())
        elif mouse_point.get_x() > box.get_x()+box.get_width():
            return GeometryUtil.distance_from_line_segment(mouse_point, box.top_right(), box.bot_right())
        elif mouse_point.get_y() < box.get_y():
            return GeometryUtil.distance_from_line_segment(mouse_point, box.top_left(), box.top_right())
        else:
            return GeometryUtil.distance_from_line_segment(mouse_point, box.bot_left(), box.bot_right())

    def get_bounding_box(self) -> Rectangle:
        bottom = right = None
        # if self.get_hot_point(0).get_x() < self.get_hot_point(1).get_x() or \
        #         (self.get_hot_point(0).get_x() == self.get_hot_point(1).get_x() and
        #          self.get_hot_point(0).get_y() > self.get_hot_point(1).get_y()):
        right = self.get_hot_point(0)
        bottom = self.get_hot_point(1)
        # else:
        #     right = self.get_hot_point(1)
        #     bottom = self.get_hot_point(0)

        # print("right x =", right.get_x(), " bottom x =", bottom.get_x())
        delta_x = abs(right.get_x() - bottom.get_x())
        delta_y = abs(bottom.get_y() - right.get_y())

        return Rectangle(right.get_x() - 2*delta_x, bottom.get_y() - 2*delta_y, 2*delta_x, 2*delta_y)

    def duplicate(self):  # "-> GraphicalObject:
        return deepcopy(self)

    def get_shape_name(self) -> str:
        return "Oval"

    def render(self, r: Renderer):
        precision = 20  # Number of dots = (precision-1)*2
        right = self.get_hot_point(0)
        bottom = self.get_hot_point(1)
        width = abs(right.get_x() - bottom.get_x())*2
        height = abs(right.get_y() - bottom.get_y())*2
        a = width/2
        b = height/2
        top = []
        bot = []
        for i in range(precision+1):
            if i == 0:  # only 1 point on left and right side
                bot.append(Point(right.get_x(), right.get_y()))
            elif i == precision:
                x = right.get_x() - (i / precision * width)
                bot.append(Point(x, right.get_y()))
            else:
                x = a - (i/precision * width)
                y = sqrt((1 - x**2/a**2) * b**2)  # elipse formula, calculates positive solution
                bot.append(Point(bottom.get_x() + x, right.get_y() + y))
                top.insert(0, Point(bottom.get_x() + x, right.get_y() - y))
        r.fill_polygon(bot + top)

    def get_center(self) -> Point:
        return Point(min(self.get_hot_point(0).get_x(), self.get_hot_point(1).get_x()),
                     min(self.get_hot_point(0).get_y(), self.get_hot_point(1).get_y()))

    def set_hot_point(self, index: int, p: Point):
        # right
        # print("here")
        if index == 0 and (p.get_x() > self.get_hot_point(1).get_x() and p.get_y() < self.get_hot_point(1).get_y()):
            super().set_hot_point(index, p)
        # bot
        elif index == 1 and (p.get_x() < self.get_hot_point(0).get_x() and p.get_y() > self.get_hot_point(0).get_y()):
            super().set_hot_point(index, p)

    def get_shape_id(self) -> str:
        return f"@OVAL {self.get_hot_point(0).get_x()} {self.get_hot_point(0).get_y()} {self.get_hot_point(1).get_x()} {self.get_hot_point(1).get_y()}\n"

    def save(self, rows: list):
        rows.append(self.get_shape_id())

    def load(self, stack: list, data: str):
        cords = data.split()[1:]
        oval: GraphicalObject = Oval(Point(int(cords[0]), int(cords[1])),Point(int(cords[2]), int(cords[3])))
        stack.append(oval)

