from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from geometry_objects import Point, Rectangle
    from i_renderer import Renderer
    from i_listener import GraphicalObjectListener


class GraphicalObject:
    # object modifying
    def is_selected(self) -> bool:
        pass

    def set_selected(self, selected: bool):
        pass

    def get_number_of_hot_points(self) -> int:
        pass

    def get_hot_point(self, index: int) -> Point:
        pass

    def set_hot_point(self, index: int, p: Point):
        pass

    def is_hot_point_selected(self, index: int) -> bool:
        pass

    def set_hot_point_selected(self, index: int, selected: bool):
        pass

    def get_hot_point_distance(self, index: int, mouse_point: Point) -> float:
        pass

    # geometry operations
    def translate(self, delta: Point):
        pass

    def get_bounding_box(self) -> Rectangle:
        pass

    def selection_distance(self, mouse_point: Point) -> float:
        pass

    # drawing
    def render(self, r: Renderer):
        pass

    # observers
    def add_graphical_object_listener(self, gol: GraphicalObjectListener):
        pass

    def remove_graphical_object_listener(self, gol: GraphicalObjectListener):
        pass

    # prototype support
    def get_shape_name(self) -> str:
        pass

    def duplicate(self) -> GraphicalObject:
        pass

    # load and save support
    def get_shape_id(self) -> str:
        pass

    def load(self, stack: list, data: str):  # Stack<GraphicalObject> stack
        pass

    def save(self, rows: list):  # List<String> rows
        pass

    def get_center(self) -> Point:
        pass

    def get_composite(self):
        pass

