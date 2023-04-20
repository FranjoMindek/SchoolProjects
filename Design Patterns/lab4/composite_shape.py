from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from i_graphical_object import GraphicalObject
    from i_renderer import Renderer
    from geometry_objects import Point

from abstract_graphical_object import AbstractGraphicalObject
from geometry_objects import Rectangle
from geometry_utilities import GeometryUtil


class CompositeShape(AbstractGraphicalObject):
    def __init__(self, leaves):
        super().__init__([])
        self._leaves = []
        for i in range(len(leaves)):
            self._leaves.append(leaves[i])

    def get_composite(self):
        return self

    def get_leaves(self):
        return self._leaves

    def translate(self, delta: Point):
        for leaf in self._leaves:
            leaf: GraphicalObject
            leaf.translate(delta)
        self.notify_listeners()

    def selection_distance(self, mouse_point: Point) -> float:
        box = self.get_bounding_box()
        if box.get_x() < mouse_point.get_x() < box.get_x() + box.get_width() and box.get_y() < mouse_point.get_y() < box.get_y() + box.get_height():
            return 0
        if mouse_point.get_x() < box.get_x():
            return GeometryUtil.distance_from_line_segment(mouse_point, box.top_left(), box.bot_left())
        elif mouse_point.get_x() > box.get_x()+box.get_width():
            return GeometryUtil.distance_from_line_segment(mouse_point, box.top_right(), box.bot_right())
        elif mouse_point.get_y() < box.get_y():
            return GeometryUtil.distance_from_line_segment(mouse_point, box.top_left(), box.top_right())
        else:
            return GeometryUtil.distance_from_line_segment(mouse_point, box.bot_left(), box.bot_right())

    def get_bounding_box(self) -> Rectangle:
        max_x = max_y = min_x = min_y = None
        for leaf in self._leaves:
            leaf: GraphicalObject
            box = leaf.get_bounding_box()
            if min_x is None or box.get_x() < min_x:
                min_x = box.get_x()
            if min_y is None or box.get_y() < min_y:
                min_y = box.get_y()
            if max_x is None or box.get_x() + box.get_width() > max_x:
                max_x = box.get_x() + box.get_width()
            if max_y is None or box.get_y() + box.get_height() > max_y:
                max_y = box.get_y() + box.get_height()
        return Rectangle(min_x, min_y, max_x - min_x, max_y - min_y)

    def get_shape_name(self) -> str:
        return "Composite"

    def render(self, r: Renderer):
        for leaf in self._leaves:
            leaf: GraphicalObject
            leaf.render(r)

    def get_shape_id(self) -> str:
        return f"@COMP {len(self._leaves)}\n"

    def save(self, rows: list):
        for leaf in self._leaves:
            leaf: GraphicalObject
            leaf.save(rows)
        rows.append(self.get_shape_id())

    def load(self, stack: list, data: str):
        num = int(data.split()[1])
        leaves = []
        for i in range(num):
            leaves.append(stack.pop())
        composite = CompositeShape(leaves)
        stack.append(composite)





