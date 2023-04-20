from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from geometry_objects import Rectangle

from i_renderer import Renderer
from geometry_objects import Point


class G2DRendererImpl(Renderer):
    def __init__(self, graphics):
        self._graphics = graphics

    def draw_line(self, s: Point, e: Point):
        self._graphics.create_line(s.get_x(), s.get_y(), e.get_x(), e.get_y(), fill="blue", width=2)

    def fill_polygon(self, points: list):
        coordinates = []
        for point in points:
            point: Point
            coordinates.append(point.get_x())
            coordinates.append(point.get_y())
        self._graphics.create_polygon(coordinates, fill="lightblue", outline="blue", width=2)


class G2DRendererUtilities:
    @staticmethod
    def draw_bounding_box(box: Rectangle, r: Renderer) -> None:
        r.draw_line(box.top_left(), box.top_right())
        r.draw_line(box.top_right(), box.bot_right())
        r.draw_line(box.bot_right(), box.bot_left())
        r.draw_line(box.bot_left(), box.top_left())

    @staticmethod
    def draw_hotpoint_box(hot_point: Point, r: Renderer) -> None:
        box_size = 4
        tl = hot_point.translate(Point(-box_size, box_size))
        tr = hot_point.translate(Point(box_size, box_size))
        bl = hot_point.translate(Point(-box_size, -box_size))
        br = hot_point.translate(Point(box_size, -box_size))
        r.draw_line(tl, tr)
        r.draw_line(tr, br)
        r.draw_line(br, bl)
        r.draw_line(bl, tl)

