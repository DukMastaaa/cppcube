    def normal_to_cpp(normal: str) -> str:
        return ", ".join(
            move.replace("2", "").replace("\'", "")
                + ("--" if "\'" in move else "")
                + ("*2" if "2" in move else "")
            for move in normal.split(" ")
        )
