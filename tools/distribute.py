"""
Copy all files needed to distribute the game into a single separate
folder.
"""
import os
import shutil

DEST = "dist"

if __name__ == "__main__":
    try:
        os.mkdir(DEST)
    except FileExistsError:
        pass

    # TODO: Check that this works when building is done with MSVC.
    shutil.copyfile(os.path.join("build", "grassland"), os.path.join(DEST, "grassland"))

    try:
        shutil.copytree("tilemaps", os.path.join(DEST, "tilemaps"))
    except FileExistsError:
        pass
    try:
        shutil.copytree("tilesets", os.path.join(DEST, "tilesets"))
    except FileExistsError:
        pass
