# from __future__ import annotations
# from typing import TYPE_CHECKING
# if TYPE_CHECKING:
#     from i_graphical_object import GraphicalObject
#     from i_state import Context
#     from graphical_model import GraphicalModel
#
# from tkinter import *
#
# from state import AddShapeState
#
#
# class Buttons(Frame):
#     def __init__(self, parent, objects, context, model, **kwargs):
#         super().__init__(parent, **kwargs)
#         self._objects: list = objects
#         self._context: Context = context
#         self._model: GraphicalModel = model
#         Button(self, text="Load", justify=LEFT).grid(row=0, column=0)
#         Button(self, text="Save", justify=LEFT).grid(row=0, column=1)
#         Button(self, text="SVG Export", justify=LEFT).grid(row=0, column=2)
#         col = 3
#         for item in objects:
#             item: GraphicalObject
#             Button(self, text=item.get_shape_name(), justify=RIGHT, command=self.add).grid(row=0, column=col)
#             # Button(self, text=item.get_shape_name(), justify=RIGHT, command=context.switch_state(AddShapeState(model, item))).grid(row=0, column=col)
#             col += 1
#         Button(self, text="Select", justify=RIGHT).grid(row=0, column=3 + len(objects))
#         Button(self, text="Eraser", justify=RIGHT).grid(row=0, column=4 + len(objects))
#
#     def add(self):
#         self._context.switch_state(item, self._model)