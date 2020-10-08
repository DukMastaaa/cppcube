import numpy as np
import random
from typing import Optional

WHITE = 0
GREEN = 1
RED = 2
BLUE = 3
ORANGE = 4
YELLOW = 5
UP = "U"
FRONT = "F"
RIGHT = "R"
BACK = "B"
LEFT = "L"
DOWN = "D"
DEFAULT_COLOURS = {
    UP: WHITE,
    FRONT: GREEN,
    RIGHT: RED,
    BACK: BLUE,
    LEFT: ORANGE,
    DOWN: YELLOW
}

CYCLES = {
    UP: [(FRONT, 'd', 'i'), (LEFT, 'd', 'i'), (BACK, 'd', 'i'), (RIGHT, 'd', 'i')],
    DOWN: [(FRONT, '-1-d', 'i'), (RIGHT, '-1-d', 'i'), (BACK, '-1-d', 'i'), (LEFT, '-1-d', 'i')],
    RIGHT: [(FRONT, 'i', '-1-d'), (UP, 'i', '-1-d'), (BACK, '-1-i', 'd'), (DOWN, 'i', '-1-d')],
    LEFT: [(FRONT, 'i', 'd'), (DOWN, 'i', 'd'), (BACK, '-1-i', '-1-d'), (UP, 'i', 'd')],
    FRONT: [(UP, '-1-d', 'i'), (RIGHT, 'i', 'd'), (DOWN, 'd', '-1-i'), (LEFT, '-1-i', '-1-d')],
    BACK: [(UP, 'd', 'i'), (LEFT, '-1-i', 'd'), (DOWN, '-1-d', '-1-i'), (RIGHT, 'i', '-1-d')]
}

SCRAMBLE_INIT_LENGTHS = {
    2: 11,
    3: 25,
    4: 45,
}

PROBABILITY_3x3 = {
    1: "", 2: "2", 3: "\'"
}

PROBABILITY_4x4 = {
    1: "", 2: "", 3: "w",
    4: "w2", 5: "w\'", 6: "2",
    7: "2", 8: "\'", 9: "\'"
}


class CubeState(object):
    """Represents the state of a cube."""
    def __init__(self, dim: int):
        self._dim = dim
        self._idim = dim - 1  # shorthand for array indexing
        self._faces = {}
        self.reset_state()

    def reset_state(self, dim: Optional[int] = None):
        if dim is not None:
            self._dim = dim  # todo: bad smh
            self._idim = dim - 1
        for face in DEFAULT_COLOURS:
            self._faces[face] = np.full((self._dim, self._dim), DEFAULT_COLOURS[face], int)

    def cycle(self, face: str, reverse: bool = False, depth: int = 0):
        """cycles stickers not on the turning face.

        :param face: h
        :param reverse: h
        :param depth: uhh int in [0, dim-2] corresponding to the depth of the slice turn
        """
        assert 0 <= depth <= self._dim - 2
        d = depth  # shorthand for eval()
        # substitution goes backwards - easier to make it default reversed
        cycle_list = CYCLES[face] if reverse else CYCLES[face][::-1]
        for i in range(self._dim):
            # buffer taken from first element of reversed list
            buffer_face, buffer_row, buffer_column = cycle_list[0]
            buffer = self._faces[buffer_face][eval(buffer_row), eval(buffer_column)]

            # stops at second last instruction to not raise IndexError
            for instruction_index in range(len(cycle_list) - 1):
                this_face, this_row, this_column = cycle_list[instruction_index]
                next_face, next_row, next_column = cycle_list[instruction_index + 1]

                # assigns colour at next location to sticker at current location
                self._faces[this_face][eval(this_row), eval(this_column)] = \
                    self._faces[next_face][eval(next_row), eval(next_column)]

            # fixes the cycle by substituting the buffer at the last swap location
            last_face, last_row, last_column = cycle_list[-1]
            self._faces[last_face][eval(last_row), eval(last_column)] = buffer

    def rotate(self, face: str, reverse: bool = False, depth: int = 0) -> None:
        if depth == 0:
            # maybe inefficient?
            self._faces[face] = np.rot90(self._faces[face], 1 if reverse else 3)
        self.cycle(face, reverse, depth)

    def parse_moves(self, moves: str):
        move_list = moves.split(' ')
        for move in move_list:
            reverse = move.endswith("\'")
            double = move.endswith("2")
            if 'w' in move:
                depth = int(move[0]) - 1 if move[0].isdigit() else 1
            else:
                depth = 0
            face = [char.upper() for char in move if char.isalpha()]
            if "W" in face:
                face.remove('W')
            face = "".join(face)
            for i in range(2 if double else 1):
                for depth_i in range(depth + 1):
                    self.rotate(face, reverse, depth_i)

    def get_faces(self):
        return self._faces


def list_remove_multiple(input_list: list, *args):
    copy_list = input_list.copy()
    for element in args:
        if element in copy_list:
            copy_list.remove(element)
    return copy_list


def generate_scramble_seq(dim: int):
    scramble = []
    moves_list = [FRONT, RIGHT, UP] if dim <= 2 else [FRONT, RIGHT, UP, LEFT, DOWN, BACK]
    prev = None
    prev2 = None
    if dim <= 4:  # todo: include dim >= 5
        for count in range(SCRAMBLE_INIT_LENGTHS[dim]):
            prev2 = prev
            removed_list = list_remove_multiple(moves_list, prev, prev2)
            next_move = random.choice(removed_list)
            prev = next_move
            if dim == 4 and count >= 20:
                next_move += PROBABILITY_4x4[random.randint(1, 9)]
            else:
                next_move += PROBABILITY_3x3[random.randint(1, 3)]
            scramble.append(next_move)
    return " ".join(scramble)
