from __future__ import annotations

import copy
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from geometry_objects import Rectangle
    from i_renderer import Renderer
    from i_graphical_object import GraphicalObject
    from graphical_model import GraphicalModel

from i_state import State
from geometry_objects import Point
from g2d_renderer import G2DRendererUtilities
from composite_shape import CompositeShape
from line_segment import LineSegment


class IdleState(State):
    def mouse_down(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        pass

    def mouse_up(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        pass

    def mouse_dragged(self, mouse_point: Point) -> None:
        pass

    def key_pressed(self, key_code: int) -> None:
        pass

    # called after canvas finished drawing graphical object in argument
    def after_draw(self, r: Renderer, go: GraphicalObject) -> None:
        pass

    def after_draw_all(self, r: Renderer) -> None:
        pass

    def on_leaving(self) -> None:
        pass

    def state(self) -> None:
        print("Idle")


class AddShapeState(State):
    def __init__(self, model: GraphicalModel, prototype: GraphicalObject) -> None:
        self._prototype: GraphicalObject = prototype
        self._model: GraphicalModel = model

    def mouse_down(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        obj: GraphicalObject = self._prototype.duplicate()
        obj.translate(mouse_point)
        self._model.add_graphical_object(obj)

    def mouse_up(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        pass

    def mouse_dragged(self, mouse_point: Point) -> None:
        pass

    def key_pressed(self, key_code: int) -> None:
        if key_code == 9:  # ESC
            self.context.switch_state(IdleState())

    # called after canvas finished drawing graphical object in argument
    def after_draw(self, r: Renderer, go: GraphicalObject) -> None:
        pass

    def after_draw_all(self, r: Renderer) -> None:
        pass

    def on_leaving(self) -> None:
        pass

    def state(self) -> None:
        print("AddShape", self._prototype.get_shape_name())


class SelectShapeState(State):
    def __init__(self, model: GraphicalModel) -> None:
        self._model = model
        self._dragged = None
        self._old = None
        self._scaling = False
        self._hot_point = -1

    def mouse_down(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        obj, obj_dist = self._model.find_selected_graphical_object(mouse_point)
        if obj is not None:
            if ctrl_down:
                obj.set_selected(True)
            else:
                self._model.clear_selected_objects()
                obj.set_selected(True)
        self._dragged = None
        self._old = None
        self._scaling = False

    def mouse_up(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        pass

    def mouse_dragged(self, mouse_point: Point) -> None:
        if self._dragged is None:
            self._dragged, obj_dist = self._model.find_selected_graphical_object(mouse_point)
            if self._dragged is not None:
                self._hot_point, hot_point_dist = self._model.find_selected_hot_point(self._dragged, mouse_point)
                # print("Obj dist:", obj_dist, " Hot point dist:", hot_point_dist)
                if hot_point_dist != -1:
                    self._scaling = True
        if self._dragged is not None:
            if not self._scaling:
                if self._old is None:
                    self._old = copy.deepcopy(mouse_point)
                elif self._dragged.is_selected() and len(self._model.get_selected_objects()) == 1:
                    dist = Point(mouse_point.get_x()-self._old.get_x(), mouse_point.get_y()-self._old.get_y())
                    self._old = copy.deepcopy(mouse_point)
                    self._dragged.translate(dist)
            else:
                self._dragged.set_hot_point(self._hot_point, copy.deepcopy(mouse_point))

    def key_pressed(self, key_code: int) -> None:
        print(key_code)
        if key_code == 9:  # ESC
            self._model.clear_selected_objects()
            self.context.switch_state(IdleState())
        elif key_code == 113:
            objs = self._model.get_selected_objects()
            for obj in objs:
                obj: GraphicalObject
                obj.translate(Point(-1, 0))
        elif key_code == 111:
            objs = self._model.get_selected_objects()
            for obj in objs:
                obj: GraphicalObject
                obj.translate(Point(0, -1))
        elif key_code == 114:
            objs = self._model.get_selected_objects()
            for obj in objs:
                obj: GraphicalObject
                obj.translate(Point(1, 0))
        elif key_code == 116:
            objs = self._model.get_selected_objects()
            for obj in objs:
                obj: GraphicalObject
                obj.translate(Point(0, 1))
        elif key_code == 86:
            objs = self._model.get_selected_objects()
            if len(objs) == 1:
                self._model.increase_z(objs[0])
        elif key_code == 82:
            objs = self._model.get_selected_objects()
            if len(objs) == 1:
                self._model.decrease_z(objs[0])
        elif key_code == 42:
            objs = self._model.get_selected_objects()
            composite = CompositeShape(objs)
            for i in reversed(range(len(objs))):
                self._model.remove_graphical_object(objs[i])
            self._model.add_graphical_object(composite)
            composite.set_selected(True)
        elif key_code == 30:
            objs = self._model.get_selected_objects()
            if len(objs) == 1 and objs[0].get_composite() is not None:
                composite: CompositeShape = objs[0]
                composite.set_selected(False)
                for obj in composite.get_leaves():
                    self._model.add_graphical_object(obj)
                    obj.set_selected(True)
                self._model.remove_graphical_object(composite)

    # called after canvas finished drawing graphical object in argument
    def after_draw(self, r: Renderer, go: GraphicalObject) -> None:
        pass

    def after_draw_all(self, r: Renderer) -> None:
        objs = self._model.get_selected_objects()
        for obj in objs:
            obj: GraphicalObject
            box: Rectangle = obj.get_bounding_box()
            G2DRendererUtilities.draw_bounding_box(box, r)
            if len(objs) == 1:
                for i in range(obj.get_number_of_hot_points()):
                    G2DRendererUtilities.draw_hotpoint_box(obj.get_hot_point(i), r)

    def on_leaving(self) -> None:
        pass

    def state(self) -> None:
        print("SelectShape")


class EraserState(State):
    def __init__(self, model: GraphicalModel) -> None:
        self._model: GraphicalModel = model
        self._old = None

    def mouse_down(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        pass

    def mouse_up(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        obj, obj_dist = self._model.find_selected_graphical_object(mouse_point)
        if obj is not None:
            self._model.remove_graphical_object(obj)
        ro_lines = self._model.get_eraser_lines()
        for i in range(len(ro_lines)):
            line: LineSegment = ro_lines[i]
            for index in range(line.get_number_of_hot_points()):
                obj, obj_dist = self._model.find_selected_graphical_object(line.get_hot_point(index))
                if obj is not None:
                    # delete it
                    self._model.remove_graphical_object(obj)
        self._model.clear_eraser_lines()
        self._old = None

    def mouse_dragged(self, mouse_point: Point) -> None:
        if self._old is None:
            self._old = copy.deepcopy(mouse_point)
        else:
            self._model.add_eraser_line(LineSegment(self._old, copy.deepcopy(mouse_point)))
            self._old = copy.deepcopy(mouse_point)

    def key_pressed(self, key_code: int) -> None:
        if key_code == 9:  # ESC
            self.context.switch_state(IdleState())

    # called after canvas finished drawing graphical object in argument
    def after_draw(self, r: Renderer, go: GraphicalObject) -> None:
        pass

    def after_draw_all(self, r: Renderer) -> None:
        pass

    def on_leaving(self) -> None:
        pass

    def state(self) -> None:
        print("EraserState")
