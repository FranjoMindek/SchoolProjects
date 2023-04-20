from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from i_listener import GraphicalObjectListener
    from geometry_objects import Point

from i_graphical_object import GraphicalObject
from geometry_utilities import GeometryUtil


class AbstractGraphicalObject(GraphicalObject):
    def __init__(self, hot_points: list):
        self._hot_points: list = hot_points
        self._hot_point_selected: list = []  # bool for every hot point
        self._selected: bool = False
        self._listeners: list = []  # List<GraphicalObjectListener>

    def get_hot_point(self, index: int) -> Point:
        return self._hot_points[index]

    def set_hot_point(self, index: int, p: Point):
        self._hot_points[index] = p
        self.notify_listeners()

    def get_number_of_hot_points(self) -> int:
        return len(self._hot_points)

    def get_hot_point_distance(self, index: int, mouse_point: Point) -> float:
        if index < len(self._hot_points):
            return GeometryUtil.distance_from_point(self._hot_points[index], mouse_point)

    def is_hot_point_selected(self, index: int) -> bool:
        return self._hot_point_selected[index]

    def set_hot_point_selected(self, index: int, selected: bool):
        self._hot_point_selected = [False]*len(self._hot_points)
        self._hot_point_selected[index] = True
        self.notify_selection_listeners()

    def is_selected(self) -> bool:
        return self._selected

    def set_selected(self, selected: bool):
        self._selected = selected
        self.notify_selection_listeners()

    def translate(self, delta: Point):
        for i, point in enumerate(self._hot_points):
            self._hot_points[i] = point.translate(delta)
        self.notify_listeners()

    def add_graphical_object_listener(self, gol: GraphicalObjectListener):
        self._listeners.append(gol)

    def remove_graphical_object_listener(self, gol: GraphicalObjectListener):
        self._listeners.remove(gol)

    def notify_listeners(self):
        for listener in self._listeners:
            listener.graphical_object_changed(self)

    def notify_selection_listeners(self):
        for listener in self._listeners:
            listener.graphical_object_selection_changed(self)


