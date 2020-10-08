import emulator2 as emul
import time

scrambles_5 = [
    "Dw' R F2 U2 L2 Fw' F' R2 Uw' R Dw2 L' Fw D2 U2 L2 D Uw2 B2 D2 Dw' U' Bw F U F Uw' L' U Fw' Uw F' Uw2 Bw Fw2 Uw' U2 Lw R2 Dw2 B' Fw' Lw2 Fw Rw2 D Dw' F U R' U Lw F2 Rw2 R2 Uw F2 L2 Dw' Lw'",
    "Dw L Lw2 Bw' F' Lw' Rw U2 F' D Bw F D Rw2 B' U Rw' Uw' B2 L' U Rw' Uw Fw2 L2 Lw2 R' Dw L' R B' Lw' B2 Bw' Lw' U2 B2 F Lw' B L' Bw2 Uw R2 U B D' Bw' Lw' Dw' Fw Dw' Uw' Fw L Lw' R2 Uw F' U2",
    "U2 L' Lw' F U B' Lw' D' Dw U B Bw2 L D F U' Bw Rw2 Bw Fw' D2 Dw B2 L Uw B' U' L Rw Bw' D' Fw2 U2 B' Bw R2 Dw2 Fw F' Dw' Uw2 Bw2 Fw' D Uw' Bw' Rw2 F' L Bw' Fw F' Rw' F' Lw2 Rw2 Bw L' B2 Dw'",
    "R2 U' Lw R' Bw Rw' B' Bw' Rw' Fw L' R2 Dw U L' R2 B' F' Dw B2 D' Lw' F Uw2 L' Dw2 B' Lw2 Dw' Fw' F' D2 L' Lw2 Rw Bw' D Lw R F Rw2 Fw2 F' Dw2 Uw Lw Dw2 Uw B2 Dw L' Uw' F D B Bw Fw2 R Dw2 Fw",
    "F' Lw2 R2 U2 R2 U' Bw Lw2 R' F L B2 D Uw2 B2 F' Dw2 Lw U2 L2 Bw2 Fw2 F' Dw2 Rw2 R2 Uw' Lw' B2 Uw Bw Uw' Fw' L2 F' Dw Uw' Lw B2 Bw Dw' U2 L' Lw Dw' L2 B D' B D2 Rw2 D U L D2 Fw U2 Fw2 Lw' F",
    "B' Bw Fw2 F2 Lw2 R' F U' B2 D' B2 F2 Uw2 Lw2 F2 Rw2 Dw' U Bw2 Fw2 F' D Uw2 U F' L' Fw2 D2 Uw2 B2 Dw' U2 Fw' Rw' Dw Uw Rw' Fw' Lw2 F2 Uw B' Bw2 Dw B' Fw' F' Lw R2 B' Fw U Lw2 D U' B' L Lw D L'",
    "Fw' Uw2 F2 Uw2 Lw Rw Uw2 Fw2 U Lw2 R F' D Uw' Fw2 F L2 U' Rw2 B Dw' U2 Bw D2 Dw B' D2 B' F2 U L Dw Uw2 Rw U' Bw2 Lw Rw D' U2 Fw2 F Uw B L R' B2 Bw' L Rw Uw2 L D' Uw2 Rw2 B Lw2 Uw' F D2",
    "Dw U2 Bw' Fw2 D' U' Lw U2 R2 D Dw' L' U Lw D F L2 F2 Dw U2 Fw2 F' Uw Bw' Dw2 Bw' Rw2 R2 B Lw B Dw Lw' U2 F2 Lw' D Uw2 Fw2 Lw Dw U2 Lw' B2 Rw B2 R2 Bw2 Dw2 Lw2 Rw' Uw R' Fw2 L' Lw' Fw L2 Fw2 Dw'",
    "U2 F Dw Lw2 D' Dw Rw2 B' Uw2 L U2 L' Lw' B' Bw2 Fw F' L Lw D2 Uw Fw' D Uw2 U' B' Bw' R Dw2 Uw' U' Lw Fw' L B' Bw Fw2 L2 D Uw Rw B R' B U' F2 L D2 U' R' Dw2 B' Fw Rw2 Bw2 Dw' Lw2 F Dw R'",
    "Fw Rw2 Fw' Rw R F' R2 D' Dw Uw L Lw2 Rw' R Dw U' L Rw' Fw2 Rw2 B2 Rw2 Bw Fw2 Dw2 R Dw' Uw Fw2 Dw' L Rw' R2 B2 Bw' Lw Uw' F D R' Bw Dw2 U B' Dw' Uw' L2 Lw Dw2 Bw2 F Dw Uw U B' Rw' F2 Uw' U Rw'"
]

cube = emul.CubeState(5)
times = []

for scramble in scrambles_5:
    cube.reset_state()
    ti = time.perf_counter()
    cube.parse_moves(scramble)
    tf = time.perf_counter()
    times.append(round(tf - ti, 4))

print(times)
print(f"{round(sum(times) / len(times), 4)}")

