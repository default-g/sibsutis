import tkinter as tk


class Vertex:
    def __init__(self, data, *children):
        self.data = data
        self.children = list(children)


class GraphicalTree:
    def __init__(self, tree, title=None, width=800, height=600):
        self.tree = tree
        self.title = title
        self.width = width
        self.height = height

    def _scroll(self, event):
        if event.num == 4 or event.delta == 120:
            self.canvas.scale("all", event.x, event.y, 1.1, 1.1)
        elif event.num == 5 or event.delta == -120:
            self.canvas.scale("all", event.x, event.y, 0.9, 0.9)

    def _drag_start(self, event):
        self.canvas.scan_mark(event.x, event.y)

    def _drag_move(self, event):
        self.canvas.scan_dragto(event.x, event.y, gain=1)
        self.canvas.update()

    def _draw_vertex(self, data, x, y):
        radius = 15
        self.canvas.create_oval(x - radius, y - radius, x + radius, y + radius, fill="white")
        self.canvas.create_text(x, y, text=data, font=(None, round(20)))

    def _draw_tree(self, vertex, level=1, margin=1):
        width = 0
        cell_size = 40
        for child in vertex.children:
            self.canvas.create_line(margin * cell_size, level * cell_size, (margin + width) * cell_size,
                                    (level + 1) * cell_size)
            width += self._draw_tree(child, level + 1, margin + width)
        self._draw_vertex(vertex.data, margin * cell_size, level * cell_size)

        return width if width else 1

    def start(self):
        self.window = tk.Tk()
        self.window.title(self.title)
        self.canvas = tk.Canvas(self.window, width=self.width, height=self.height)
        self.canvas.pack()
        self.canvas.bind("<Button-4>", self._scroll)
        self.canvas.bind("<Button-5>", self._scroll)
        self.canvas.bind("<ButtonPress-1>", self._drag_start)
        self.canvas.bind("<B1-Motion>", self._drag_move)
        self.update()
        self.window.mainloop()

    def update(self):
        self.canvas.delete("all")
        self._draw_tree(self.tree)
        self.canvas.update()
