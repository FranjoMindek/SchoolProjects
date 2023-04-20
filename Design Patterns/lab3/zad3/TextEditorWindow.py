import tkinter as tk
from tkinter import filedialog as fd
from InfoPanel import InfoPanel
import os
import importlib

from TextEditorModel import TextEditorModel
from TextEditor import TextEditor


class PluginWindow(tk.Menu):
    def __init__(self, plugin, tem: TextEditorModel, root, **kwargs):
        super().__init__(root, **kwargs)
        self._plugin = plugin
        self._tem = tem
        self.name: str = plugin.get_name(plugin)
        self.add_command(label="Execute", command=self.execute)
        self.add_command(label="Desc", command=self.get_description)

    def execute(self):
        self._plugin.execute(self._plugin, self._tem, self._tem.undo_manager, self._tem.clipboard_stack)

    def get_description(self):
        self._plugin.get_description(self._plugin)


class TextEditorWindow:
    def __init__(self):
        self.window = tk.Tk()
        self.tem = TextEditorModel("Ovo je test\nIli mozda ipak nije\nJe!\niiiiiiiiiiiiiiii iliti monospace test"
                                   "\nKoji ima jaaaaaaaaaaaaako? puno tekst <>!#")
        # Menu
        menu = tk.Menu(self.window)
        self.window.config(menu=menu)
        file_menu = tk.Menu(menu)
        edit_menu = tk.Menu(menu)
        move_menu = tk.Menu(menu)
        plugins_menu = tk.Menu(menu)
        menu.add_cascade(label="File", menu=file_menu)
        menu.add_cascade(label="Edit", menu=edit_menu)
        menu.add_cascade(label="Move", menu=move_menu)
        menu.add_cascade(label="Plugins", menu=plugins_menu)
        file_menu.add_command(label="Open", command=self.select_file_open)
        file_menu.add_command(label="Save", command=self.select_file_save)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.window.quit)
        edit_menu.add_command(label="Undo", command=self.tem.on_undo)
        edit_menu.add_command(label="Redo", command=self.tem.on_redo)
        edit_menu.add_command(label="Cut", command=self.tem.on_cut)
        edit_menu.add_command(label="Copy", command=self.tem.on_copy)
        edit_menu.add_command(label="Paste", command=self.tem.on_paste)
        edit_menu.add_command(label="Paste and take", command=self.tem.on_shift_paste)
        edit_menu.add_command(label="Delete selection", command=self.tem.on_delete_section)
        edit_menu.add_command(label="Clear document", command=self.tem.on_clear)
        move_menu.add_command(label="Cursor to document start", command=self.tem.on_start)
        move_menu.add_command(label="Cursor to document end", command=self.tem.on_end)
        # Plugins
        plugins = [filename[:-3] for filename in os.listdir(".") if filename.startswith("p_")]
        self.plugins = []
        for i, plugin in enumerate(plugins):
            obj = getattr(importlib.import_module(plugin), 'Plugin')
            self.plugins.append(obj)
            plugin_menu = PluginWindow(obj, self.tem, plugins_menu, tearoff=0)
            plugins_menu.add_cascade(label=plugin_menu.name, menu=plugin_menu)
        # Frames
        drawing_frame = tk.Frame(self.window)
        drawing_frame.pack(side=tk.TOP, fill="both", expand=True)
        info_frame = InfoPanel(self.tem, self.window)
        info_frame.pack(side=tk.BOTTOM)
        # Hotkey binds
        self.window.bind("<Left>", self.tem.on_left)
        self.window.bind("<Right>", self.tem.on_right)
        self.window.bind("<Up>", self.tem.on_up)
        self.window.bind("<Down>", self.tem.on_down)
        self.window.bind("<Delete>", self.tem.on_delete)
        self.window.bind("<BackSpace>", self.tem.on_backspace)
        self.window.bind("<KeyPress-Shift_L>", self.tem.on_shift_press)
        self.window.bind("<KeyRelease-Shift_L>", self.tem.on_shift_release)  # NE RADI
        self.window.bind("<KeyPress>", self.tem.on_key_press)
        self.window.bind("<Return>", self.tem.on_enter)
        self.window.bind("<Control-c>", self.tem.on_copy)
        self.window.bind("<Control-x>", self.tem.on_cut)
        self.window.bind("<Control-v>", self.tem.on_paste)
        self.window.bind("<Shift-Control-V>", self.tem.on_shift_paste)
        self.window.bind("<Control-z>", self.tem.on_undo)
        self.window.bind("<Control-y>", self.tem.on_redo)
        # TextEditor(Canvas) - renders information
        te = TextEditor(drawing_frame, bg="white", height=640, width=800, model=self.tem)
        te.pack(fill="both", expand=True)

    def loop(self):
        self.window.mainloop()

    def select_file_save(self):
        files = [('All Files', '*.*'),
                 ('Python Files', '*.py'),
                 ('Text Document', '*.txt')]
        filename = fd.asksaveasfile(filetypes=files).name
        self.tem.on_save(filename)

    def select_file_open(self):
        filetypes = (('text files', '*.txt'), ('All files', '*.*'))
        filename = fd.askopenfilename(
            title='Open a file',
            initialdir='/',
            filetypes=filetypes)
        self.tem.on_open(filename)





