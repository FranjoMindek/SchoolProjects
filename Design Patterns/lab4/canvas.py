from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from graphical_model import GraphicalModel
    from read_only_proxy import ReadOnlyList
    from i_state import Context, State

from tkinter import *

from i_listener import GraphicalModelListener
from g2d_renderer import G2DRendererImpl
from geometry_objects import Point


class SVGCanvas(Canvas, GraphicalModelListener):
    def __init__(self, parent, model: GraphicalModel, context: Context, **kwargs):
        super().__init__(parent, **kwargs)
        self._model: GraphicalModel = model
        self._model.add_graphical_model_listener(self)
        self._context: Context = context
        self.focus_force()  # FIXME: otherwise doesnt work?
        # ALL THE BINDS
        self.bind("<KeyPress>", self.key_pressed)
        self.bind("<Button-1>", self.mouse_down)
        self.bind("<Shift-Button-1>", self.mouse_down_shift)
        self.bind("<Control-Button-1>", self.mouse_down_ctrl)
        self.bind("<Shift-Control-Button-1>", self.mouse_down_shift_ctrl)
        self.bind("<ButtonRelease-1>", self.mouse_up)
        self.bind("<Shift-ButtonRelease-1>", self.mouse_up_shift)
        self.bind("<Control-ButtonRelease-1>", self.mouse_up_ctrl)
        self.bind("<Shift-Control-ButtonRelease-1>", self.mouse_up_shift_ctrl)
        self.bind("<B1-Motion>", self.mouse_motion)

    def render(self) -> None:
        self.delete("all")  # mozda kasnije ne
        r = G2DRendererImpl(self)
        ro_list: ReadOnlyList = self._model.list()
        ro_eraser_lines: ReadOnlyList = self._model.get_eraser_lines()
        for index in range(len(ro_list)):
            ro_list[index].render(r)
            self._context.after_draw(r, ro_list[index])
        for index in range(len(ro_eraser_lines)):
            ro_eraser_lines[index].render(r)
        self._context.after_draw_all(r)

    def graphical_model_changed(self):
        self.render()

    def key_pressed(self, event) -> None:
        self._context.key_pressed(event.keycode)

    def mouse_down(self, event) -> None:
        self._context.mouse_down(Point(event.x, event.y), False, False)

    def mouse_down_shift(self, event) -> None:
        self._context.mouse_down(Point(event.x, event.y), True, False)

    def mouse_down_ctrl(self, event) -> None:
        self._context.mouse_down(Point(event.x, event.y), False, True)

    def mouse_down_shift_ctrl(self, event) -> None:
        self._context.mouse_down(Point(event.x, event.y), True, True)

    def mouse_up(self, event) -> None:
        self._context.mouse_up(Point(event.x, event.y), False, False)

    def mouse_up_shift(self, event) -> None:
        self._context.mouse_up(Point(event.x, event.y), True, False)

    def mouse_up_ctrl(self, event) -> None:
        self._context.mouse_up(Point(event.x, event.y), False, True)

    def mouse_up_shift_ctrl(self, event) -> None:
        self._context.mouse_up(Point(event.x, event.y), True, True)

    def mouse_motion(self, event) -> None:
        self._context.mouse_dragged(Point(event.x, event.y))