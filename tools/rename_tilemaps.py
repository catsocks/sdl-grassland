"""
Rename tilemaps exported from Tiled to the tilemaps folder from the format
World_Background.csv to background.csv.
"""
import os

if __name__ == "__main__":
    with os.scandir("tilemaps") as it:
        for entry in it:
            if entry.name.endswith(".csv") and entry.is_file():
                name = entry.name.lower()
                i = name.rfind("_")
                if i == -1 and entry.name == name:
                    continue
                name = name[i + 1 :]
                os.rename(entry.path, os.path.join("tilemaps", name))
