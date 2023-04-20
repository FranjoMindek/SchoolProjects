from __future__ import annotations
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from i_graphical_object import GraphicalObject


class GraphicalObjectListener:
    def graphical_object_changed(self, go: GraphicalObject):
        pass

    def graphical_object_selection_changed(self, go: GraphicalObject):
        pass


class GraphicalModelListener:
    def graphical_model_changed(self):
        pass

