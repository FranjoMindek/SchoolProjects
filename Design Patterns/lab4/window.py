from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from read_only_proxy import ReadOnlyList
import os


from tkinter import *
from tkinter import filedialog
from functools import partial

from canvas import SVGCanvas
from graphical_model import GraphicalModel
from state import IdleState, AddShapeState, SelectShapeState, EraserState
from i_state import Context
from svg_renderer import SVGRendererImpl


class App:
    def __init__(self, objects: list):
        self._objects = objects
        self._window = Tk()
        self._context = Context(IdleState())

        self._model = GraphicalModel()
        buttons = Frame(self._window)
        Button(buttons, text="Load", justify=LEFT, command=self._load).grid(row=0, column=0)
        Button(buttons, text="Save", justify=LEFT, command=self._save).grid(row=0, column=1)
        Button(buttons, text="SVG Export", justify=LEFT, command=self._export).grid(row=0, column=2)
        col = 3
        for item in objects:
            Button(buttons, text=item.get_shape_name(), justify=RIGHT, command=partial(self._add, item)).grid(row=0, column=col)
            col += 1
        Button(buttons, text="Select", justify=RIGHT, command=self._select).grid(row=0, column=3 + len(objects))
        Button(buttons, text="Eraser", justify=RIGHT, command=self._erase).grid(row=0, column=4 + len(objects))

        canvas = SVGCanvas(self._window, self._model, self._context, bg="white", height=640, width=800)

        buttons.pack(anchor="nw")
        canvas.pack(anchor="s")

    def _load(self):
        filetypes = (('SVG files', '*.csvg'), ('All files', '*.*'))
        filename = filedialog.askopenfilename(
            title='Open a file',
            initialdir=os.path.dirname(os.path.realpath(__file__)),
            filetypes=filetypes)
        print(filename)
        if filename != "()":
            stack = []
            file = open(filename, "r")
            lines = file.readlines()
            for line in lines:
                for obj in self._objects:
                    if line[:5] == obj.get_shape_id()[:5]:
                        obj.load(stack, line)
                        break
            for obj in stack:
                self._model.add_graphical_object(obj)

    def _save(self):
        files = [('CustomSVG files', '*.csvg'), ('All Files', '*.*')]
        filename = filedialog.asksaveasfile(filetypes=files).name
        if filename is not None:
            rows = []
            ro_list: ReadOnlyList = self._model.list()
            for i in range(len(ro_list)):
                ro_list[i].save(rows)
            file = open(filename, "w")
            file.writelines(rows)
            file.close()

    def _export(self):
        files = [('CustomSVG files', '*.svg'), ('All Files', '*.*')]
        filename = filedialog.asksaveasfile(filetypes=files).name
        r = SVGRendererImpl(filename)
        ro_list: ReadOnlyList = self._model.list()
        for i in range(len(ro_list)):
            ro_list[i].render(r)
        r.close()

    def _erase(self) -> None:
        self._context.switch_state(EraserState(self._model))

    def _select(self) -> None:
        self._context.switch_state(SelectShapeState(self._model))

    def _add(self, item) -> None:
        self._context.switch_state(AddShapeState(self._model, item))

    def start(self) -> None:
        self._window.mainloop()

