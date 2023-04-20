from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from geometry_objects import Point, Rectangle


class Renderer:
    def draw_line(self, s: Point, e: Point):
        pass

    def fill_polygon(self, points: list):
        pass
