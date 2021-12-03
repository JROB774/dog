# A Game by Its Cover Jam 2020 (DOG!)

This project was made for 2020's **[A Game by Its Cover Jam](https://itch.io/jam/a-game-by-its-cover-2020)**.
It is a simple 2D platformer game with a couple of levels and some achievements to be collected. A download
for the game can be found over on **[itch.io](https://jrob774.itch.io/dog)**, the game is also playable in
browser on the same page.

## Development

The game was developed in C++17 using the **[SDL2](https://libsdl.org/)** library. Not long after the jam
was completed the game was ported to the web using **[emscripten](https://github.com/emscripten-core/emscripten)**.

## Building

### Windows

Run the `build/win32/build.bat` file in order to build the application.
The script supports Visual Studio. By commenting out certain lines in the file
`build/win32/utility/buildvars.bat` you can control which type of build to
compile (Debug/Release x86/x64). C++17 is required and all of the external
dependencies are provided with the repo.

### Web

Run the `build/web/build.bat` file in order to build the application. This
requires *emscripten* to be setup in order for the build to work. C++17 is
required and all of the external dependencies are provided with the repo.

## License

The project's code is available under the **[MIT License](https://github.com/JROB774/agbicjam2020/blob/master/LICENSE)**.
