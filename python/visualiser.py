import emulator2 as emul
import tkinter as tk

FACE_POSITIONS = {
    emul.UP: (1, 0),
    emul.LEFT: (0, 1),
    emul.FRONT: (1, 1),
    emul.RIGHT: (2, 1),
    emul.DOWN: (1, 2),
    emul.BACK: (2, 2)
}
COLOURS = {
    emul.WHITE: "white",
    emul.GREEN: "green",
    emul.BLUE: "blue",
    emul.RED: "red",
    emul.YELLOW: "yellow",
    emul.ORANGE: "orange"
}


class CubeNetView(tk.Canvas):
    SIDE_LENGTH = 200

    def __init__(self, master, dim):
        super().__init__(master, bg="grey", width=600, height=600)
        self._cube = emul.CubeState(dim)
        self._sticker_length = self.SIDE_LENGTH // dim

    def reset_state(self):
        self._cube.reset_state()

    def apply_moves(self, moves: str):
        self._cube.parse_moves(moves)

    def draw(self):
        self.delete(tk.ALL)
        for face in FACE_POSITIONS:
            face_x, face_y = FACE_POSITIONS[face]
            face_x *= self.SIDE_LENGTH
            face_y *= self.SIDE_LENGTH
            for row_index, row in enumerate(self._cube.get_faces()[face]):
                for col_index, col in enumerate(row):
                    sticker_x1 = face_x + col_index * self._sticker_length
                    sticker_y1 = face_y + row_index * self._sticker_length
                    sticker_x2 = sticker_x1 + self._sticker_length
                    sticker_y2 = sticker_y1 + self._sticker_length
                    self.create_rectangle(sticker_x1, sticker_y1, sticker_x2, sticker_y2,
                                          fill=COLOURS[col])


class Visualiser(object):
    def __init__(self, master, new_dim):
        self._master = master
        self._frame = tk.Frame(self._master)
        self._frame.pack(side=tk.TOP)

        self._entry = tk.Entry(self._frame, width=50)
        self._entry.pack(side=tk.LEFT)
        self._move = tk.Button(self._frame, text="turn", command=self.move)
        self._move.pack(side=tk.LEFT)
        self._reset = tk.Button(self._frame, text="reset", command=self.reset)
        self._reset.pack(side=tk.LEFT)

        self._view = CubeNetView(self._master, new_dim)
        self._view.draw()
        self._view.pack(side=tk.TOP)

    def reset(self):
        self._view.reset_state()
        self._view.draw()

    def move(self):
        self._view.apply_moves(self._entry.get())
        self._view.draw()
        self._entry.config(text="")

def main():
    dim = int(input("dim: "))
    root = tk.Tk()
    app = Visualiser(root, dim)
    root.mainloop()


if __name__ == '__main__':
    main()
