from __future__ import annotations
from typing import TYPE_CHECKING
from abc import ABC, abstractmethod
if TYPE_CHECKING:
    from geometry_objects import Point
    from i_renderer import Renderer
    from i_graphical_object import GraphicalObject


class Context:
    _state = None

    def __init__(self, state: State) -> None:
        self.switch_state(state)

    def switch_state(self, state: State) -> None:
        self._state = state
        self._state.context = self
        self._state.state()

    def mouse_down(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        self._state.mouse_down(mouse_point, shift_down, ctrl_down)

    def mouse_up(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        self._state.mouse_up(mouse_point, shift_down, ctrl_down)

    def mouse_dragged(self, mouse_point: Point) -> None:
        self._state.mouse_dragged(mouse_point)

    def key_pressed(self, key_code: int) -> None:
        self._state.key_pressed(key_code)

    # called after canvas finished drawing graphical object in argument
    def after_draw(self, r: Renderer, go: GraphicalObject) -> None:
        self._state.after_draw(r, go)

    def after_draw_all(self, r: Renderer) -> None:
        self._state.after_draw_all(r)

    def on_leaving(self) -> None:
        self._state.on_leaving()

    def state(self) -> None:
        self._state.state()


class State(ABC):
    @property
    def context(self) -> Context:
        return self._context

    @context.setter
    def context(self, context: Context) -> None:
        self._context = context

    @abstractmethod
    def mouse_down(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        pass

    @abstractmethod
    def mouse_up(self, mouse_point: Point, shift_down: bool, ctrl_down: bool) -> None:
        pass

    @abstractmethod
    def mouse_dragged(self, mouse_point: Point) -> None:
        pass

    @abstractmethod
    def key_pressed(self, key_code: int) -> None:
        pass

    # called after canvas finished drawing graphical object in argument
    @abstractmethod
    def after_draw(self, r: Renderer, go: GraphicalObject) -> None:
        pass

    @abstractmethod
    def after_draw_all(self, r: Renderer) -> None:
        pass

    @abstractmethod
    def on_leaving(self) -> None:
        pass

    @abstractmethod
    def state(self) -> None:
        pass
