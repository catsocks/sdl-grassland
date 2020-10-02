# SDL Grassland

An attempt at imitating the [RPG Maker](https://www.rpgmakerweb.com/) grid-based game feel using just C++17 and [SDL 2](https://www.libsdl.org/), with tilemaps made with [Tiled](https://www.mapeditor.org/), and tilesets free for commercial and personal use credited below.

You can walk and avoid obstacles in a 32x32 forest map while a companion follows you, it's not particularly entertaining yet.

## Screenshot

![Screenshot](screenshot.png)

## Building

Building should be possible in all major platforms and the following are required to compile this program:

* CMake 3.2 or higher
* Compiler with C++17 support
* Libraries SDL >= 2.0 and [SDL_image](https://www.libsdl.org/projects/SDL_image/) >= 2.0

On GNU/Linux Fedora 31 all necessary libraries may be installed with the command: `dnf install SDL2-devel SDL2_image-devel`.

Other systems' package managers and tools like [Vcpkg](https://github.com/microsoft/vcpkg) may be used to acquire the necessary libraries.

With requirements met, create a folder `build/`, make it the current directory, run `cmake ..` to generate the build files for your system and configuration, and then `cmake --build .` to build the project. Some additional steps may be necessary, specially on Windows.

## Gameplay

* <kbd>Up</kbd> <kbd>Down</kbd> <kbd>Left</kbd> <kbd>Right</kbd> Walk
* <kbd>Shift</kbd> + <kbd>Up</kbd> <kbd>Down</kbd> <kbd>Left</kbd> <kbd>Right</kbd> Walk in place

## Assets

Tiled, a lightweight cross-platform program that makes creating tilemaps easy, is used to generate the tilemap CSV files stored in `tilemaps/` and its tilemap (.tmx) and tileset (.tsx) source files are kept in `assets/`.

## Tools

* Normalize the filename of the CSV tilemaps exported from Tiled to `tilemaps/` by running `tools/rename_tilemaps.py`.

* Copy all files need to distribute the game to a single separate folder `dist/` by running `tools/distribute.py`.

Both tools require Python 3 and should be run from the project's root folder.

## TODO

* Add a menu with a button that starts the game
* Use SDL_mixer to add some ambient sounds

## Credits

* [FREE RPG Tileset 32x32 by pipoya](https://pipoya.itch.io/pipoya-rpg-tileset-32x32)
* [PIPOYA FREE RPG Character Sprites 32x32 by pipoya](https://pipoya.itch.io/pipoya-free-rpg-character-sprites-32x32)

## License

Everything with the exception of the contents of the tilesets and cmake folders are dedicated to the public domain under the CC0 1.0 Universal license.

## Resources

* [Introduction to the A* Algorithm](https://www.redblobgames.com/pathfinding/a-star/introduction.html) and [Implementation of A&ast;](
https://www.redblobgames.com/pathfinding/a-star/implementation.html)
* [APIByCategory - SDL Wiki'](https://wiki.libsdl.org/APIByCategory)
