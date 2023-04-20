from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from geometry_objects import Point

import math


class GeometryUtil:

    @staticmethod
    def distance_from_point(p1: Point, p2: Point) -> float:
        # print("dist")
        # print(math.pow(p2.get_x()-p1.get_x(), 2))
        # print(math.pow(p2.get_y()-p1.get_y(), 2))
        return math.sqrt(math.pow(p2.get_x()-p1.get_x(), 2) + math.pow(p2.get_y()-p1.get_y(), 2))

    @staticmethod
    def distance_from_line_segment(p: Point, s_in: Point, e_in: Point) -> float:
        if s_in.get_x() < e_in.get_x() or (s_in.get_x() == e_in.get_x() and s_in.get_y() < e_in.get_y()):
            s = s_in
            e = e_in
        else:
            s = e_in
            e = s_in
        if s.get_x() != e.get_x():
            if p.get_x() < s.get_x():
                return GeometryUtil.distance_from_point(p, s)
            elif p.get_x() > e.get_x():
                return GeometryUtil.distance_from_point(p, e)
            else:
                return abs((e.get_x() - s.get_x())*(s.get_y() - p.get_y()) - (s.get_x() - p.get_x())*(e.get_y() - s.get_y()))\
                   / GeometryUtil.distance_from_point(s, e)
        elif s.get_y() != e.get_y():
            if p.get_y() < s.get_y():
                return GeometryUtil.distance_from_point(p, s)
            elif p.get_y() > e.get_y():
                return GeometryUtil.distance_from_point(p, e)
            else:
                return abs((e.get_x() - s.get_x())*(s.get_y() - p.get_y()) - (s.get_x() - p.get_x())*(e.get_y() - s.get_y()))\
                   / GeometryUtil.distance_from_point(s, e)
        else:
            return abs((e.get_x() - s.get_x())*(s.get_y() - p.get_y()) - (s.get_x() - p.get_x())*(e.get_y() - s.get_y()))\
                   / GeometryUtil.distance_from_point(s, e)
