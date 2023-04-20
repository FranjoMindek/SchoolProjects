from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from geometry_objects import Point

from i_renderer import Renderer


class SVGRendererImpl(Renderer):
    def __init__(self, file_name: str) -> None:
        self._file_name = file_name
        self.file = open(file_name, "w")
        self.file.write(f'<svg  xmlns="http://www.w3.org/2000/svg"\nxmlns:xlink="http://www.w3.org/1999/xlink">\n')

    def close(self):
        self.file.write("</svg>")
        self.file.close()

    def draw_line(self, s: Point, e: Point):
        self.file.write(f'<line x1="{s.get_x()}" y1="{s.get_y()}" x2="{e.get_x()}" y2="{e.get_y()}" style="stroke:blue; stroke-width=2;"/>\n')

    def fill_polygon(self, points: list):
        self.file.write('<polygon points="')
        for i, point in enumerate(points):
            self.file.write(f'{point.get_x()},{point.get_y()}')
            if i != len(points)-1:
                self.file.write(" ")
        self.file.write(f'" style="stroke:blue; fill:lightblue; stroke-width=2;"/>\n')
