from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from i_graphical_object import GraphicalObject
    from i_renderer import Renderer

from copy import deepcopy

from abstract_graphical_object import AbstractGraphicalObject
from geometry_objects import Point, Rectangle
from geometry_utilities import GeometryUtil


class LineSegment(AbstractGraphicalObject):
    def __init__(self, s: Point = Point(0, 0), e: Point = Point(40, 20)):
        super().__init__([s, e])

    def selection_distance(self, mouse_point: Point) -> float:
        return GeometryUtil.distance_from_line_segment(mouse_point, self.get_hot_point(0), self.get_hot_point(1))  # FIXME: ako ne radi umjesto self.get... super().get...

    def get_bounding_box(self) -> Rectangle:
        min_p = max_p = None
        if self.get_hot_point(0).get_x() < self.get_hot_point(1).get_x() or \
                (self.get_hot_point(0).get_x() == self.get_hot_point(1).get_x() and
                 self.get_hot_point(0).get_y() < self.get_hot_point(1).get_y()):
            min_p = self.get_hot_point(0)
            max_p = self.get_hot_point(1)
        else:
            min_p = self.get_hot_point(1)
            max_p = self.get_hot_point(0)

        return Rectangle(min_p.get_x(), min_p.get_y(), max_p.get_x() - min_p.get_x(), max_p.get_y() - min_p.get_y())

    def duplicate(self) -> GraphicalObject:
        return deepcopy(self)

    def get_shape_name(self) -> str:
        return "Line"

    def render(self, r: Renderer):
        r.draw_line(self.get_hot_point(0), self.get_hot_point(1))

    def get_center(self) -> Point:
        return Point(abs(self.get_hot_point(0).get_x()+self.get_hot_point(1).get_x())/2,
                     abs(self.get_hot_point(0).get_y()+self.get_hot_point(1).get_y())/2)

    def get_shape_id(self) -> str:
        return f"@LINE {self.get_hot_point(0).get_x()} {self.get_hot_point(0).get_y()} {self.get_hot_point(1).get_x()} {self.get_hot_point(1).get_y()}\n"

    def save(self, rows: list):
        rows.append(self.get_shape_id())

    def load(self, stack: list, data: str):
        cords = data.split()[1:]
        line: GraphicalObject = LineSegment(Point(int(cords[0]), int(cords[1])),Point(int(cords[2]), int(cords[3])))
        stack.append(line)
