from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from i_listener import GraphicalModelListener
    from i_graphical_object import GraphicalObject
    from geometry_objects import Point

from i_listener import GraphicalObjectListener
from read_only_proxy import ReadOnlyList


class GraphicalModel:
    SELECTION_PROXIMITY: int = 10
    HOT_POINT_PROXIMITY: int = 20

    def __init__(self):
        self._objects: list = []
        self._ro_objects: ReadOnlyList = ReadOnlyList(self._objects)
        self._selected_objects: list = []
        self._ro_selected_objects: ReadOnlyList = ReadOnlyList(self._selected_objects)
        self._listeners: list = []
        self._go_listener: GraphicalObjectListener = GraphicalObjectListener()
        self._go_listener.graphical_object_changed = self.graphical_object_changed  # TODO: check if this works
        self._go_listener.graphical_object_selection_changed = self.graphical_object_selection_changed
        self._eraser_lines: list = []
        self._ro_eraser_lines: ReadOnlyList = ReadOnlyList(self._eraser_lines)

    def get_eraser_lines(self):
        return self._ro_eraser_lines

    def add_eraser_line(self, go: GraphicalObject):
        self._eraser_lines.append(go)
        self.notify_listeners()

    def clear_eraser_lines(self):
        self._eraser_lines.clear()
        self.notify_listeners()

    def graphical_object_changed(self, go: GraphicalObject):  # TODO: send changed obj ref? -> 1 re-redner instead whole scene
        self.notify_listeners()

    def graphical_object_selection_changed(self, go: GraphicalObject):
        if go.is_selected():
            self._selected_objects.append(go)
        else:
            self._selected_objects.remove(go)
        self.notify_listeners()

    def clear(self) -> None:  # clear all objects, remove all listeners beforehand, notify all model listeners
        for obj in self._objects:
            self.remove_graphical_object(obj)
        self.notify_listeners()  # notify that there are no objects anymore

    def add_graphical_object(self, go: GraphicalObject) -> None:
        go.add_graphical_object_listener(self._go_listener)  # add self as listener for graphical object
        self._objects.append(go)
        # self._ro_objects = tuple(self._objects)
        self.notify_listeners()  # notify listeners that new object is added

    def remove_graphical_object(self, go: GraphicalObject) -> None:
        go.remove_graphical_object_listener(self._go_listener)
        if go.is_selected():
            self._selected_objects.remove(go)
            go.set_selected(False)
        self._objects.remove(go)
        self.notify_listeners()

    def list(self) -> ReadOnlyList:  # allows only __getitem__ for now
        return self._ro_objects

    def get_selected_objects(self) -> ReadOnlyList:
        return self._ro_selected_objects

    def clear_selected_objects(self) -> None:
        for obj in self._selected_objects:
            obj: GraphicalObject
            obj.set_selected(False)
        self._selected_objects.clear()
        self.notify_listeners()

    def add_graphical_model_listener(self, gml: GraphicalModelListener) -> None:
        self._listeners.append(gml)

    def remove_graphical_model_listener(self, gml: GraphicalModelListener) -> None:
        self._listeners.remove(gml)

    def notify_listeners(self) -> None:
        for listener in self._listeners:
            listener: GraphicalModelListener  # TODO: does this even work?
            listener.graphical_model_changed()

    def increase_z(self, go: GraphicalObject) -> None:
        index = self._objects.index(go)
        if index < len(self._objects)-1:
            self._objects[index], self._objects[index+1] = self._objects[index+1], self._objects[index]
        self.notify_listeners()  # possible re-rendering needed

    def decrease_z(self, go: GraphicalObject) -> None:
        index = self._objects.index(go)
        if index > 0:
            self._objects[index], self._objects[index-1] = self._objects[index-1], self._objects[index]
        self.notify_listeners()

    def find_selected_graphical_object(self, mouse_point: Point) -> tuple[GraphicalObject | None, float]:  # in py > 3.10
        closest: GraphicalObject | None = None                                               # in py > 3.7 with from __future__ import annotations
        min_distance: float = 0
        for g_object in self._objects:
            g_object: GraphicalObject
            distance = g_object.selection_distance(mouse_point)
            if distance < GraphicalModel.SELECTION_PROXIMITY and (closest is None or distance < min_distance):
                closest = g_object
                min_distance = distance
        return closest, min_distance

    def find_selected_hot_point(self, go: GraphicalObject, mouse_point: Point) -> tuple[int, float]:
        closest: int = -1
        min_distance: float = -1
        for i in range(go.get_number_of_hot_points()):
            distance = go.get_hot_point_distance(i, mouse_point)
            # print(distance)
            if (distance < GraphicalModel.SELECTION_PROXIMITY and min_distance == -1) or distance < min_distance:
                closest = i
                min_distance = distance
        return closest, min_distance
