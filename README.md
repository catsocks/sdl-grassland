# SDL Grassland

An unfinished attempt at imitating the [RPG Maker](https://www.rpgmakerweb.com/)
grid-based game look using C++17 and [SDL 2](https://www.libsdl.org/)

In this demo you can walk in a 32x32 forest world with some obstacles while a
companion character follows you. It's not particularly entertaining yet.

The tilesets used are freely available and are credited in the
[Credits](#Credits) section below. The tilemaps were created with
[Tiled](https://www.mapeditor.org).

## Screenshot

![Screenshot](screenshot.png)

## Building

It should be possible to build this project on Windows, macOS and GNU/Linux.

### Requirements

#### Programs

* CMake >= 3.2 (guess)
* C++ compiler with C++17 support
* Python 3 (optional, needed to run the scripts in the _tools_ folder)
* Tiled (optional, needed to edit the tilemap and tileset files in the _assets_
folder)

#### Libraries

* SDL >= 2.0 (guess)
* [SDL_image](https://www.libsdl.org/projects/SDL_image) >= 2.0 (guess)

On GNU/Linux Fedora the libraries may be installed with the following command:

```sh
$ sudo dnf install SDL2-devel SDL2_image-devel
````

On Windows you can use a tool like [Vcpkg](https://github.com/microsoft/vcpkg)
to install the libraries.

### Instructions

With the necessary programs and libraries installed you may configure a build
in a folder named _build_ using CMake from the project's root folder with the
following command:

```sh
$ cmake -S . -B build
```

With a successfully configured build you may build the project by running the
following command:

```sh
$ cmake --build build
```

With a successful build you may run the game from the project's root folder.

## Gameplay

* <kbd>Up</kbd> <kbd>Down</kbd> <kbd>Left</kbd> <kbd>Right</kbd> Walk
* <kbd>Shift</kbd> + <kbd>Up</kbd> <kbd>Down</kbd> <kbd>Left</kbd>
<kbd>Right</kbd> Walk in place

## Assets

The program Tiled is used to generate the tilemap CSV files stored in the
_tilemaps_ folder, and their tilemap (.tmx) and tileset (.tsx) source files are
kept in the _assets_ folder.

## Tools

* Convert the filename of the CSV tilemaps that Tiled exports to the format that
the game expects in the _tilemaps_ folder by running _tools/rename_tilemaps.py_.

* Copy the executable from the _build_ folder and the _tilemaps_ and _tilesets_
folders to a folder named _dist_ by running _tools/distribute.py_.

Both tools should be run from the project's root folder.

## TODO

* Add a start screen with a button to start the game
* Add ambient sounds with a library like SDL_mixer

## Credits

* [FREE RPG Tileset 32x32 by pipoya](https://pipoya.itch.io/pipoya-rpg-tileset-32x32)
* [PIPOYA FREE RPG Character Sprites 32x32 by pipoya](https://pipoya.itch.io/pipoya-free-rpg-character-sprites-32x32)

## License

Everything with the exception of the contents of the _tilesets_ and cmake
folders is dedicated to the public domain under the CC0 1.0 Universal license.

## Resources

* [Introduction to the A* Algorithm](https://www.redblobgames.com/pathfinding/a-star/introduction.html)
* [Implementation of A](https://www.redblobgames.com/pathfinding/a-star/implementation.html)
* [APIByCategory - SDL Wiki'](https://wiki.libsdl.org/APIByCategory)
