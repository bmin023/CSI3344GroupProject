brew_dir := env_var("HOMEBREW_PREFIX")
files := "plotduck.cpp picture.cpp piece.cpp"
default: run
[macos]
build:
    g++ --std=c++11 -L{{brew_dir}}/lib -I{{brew_dir}}/include  -lSDL2 -lSDL2_mixer {{files}} SDL_Plotter.cpp
[macos]
run: build
    ./a.out
[windows]
build:
    set shell := ["powershell.exe", "-c"]
    C:\msys64\mingw64\bin\g++.exe -std=c++11 {{files}} .\SDL_Plotter.cpp -LC:\msys64\mingw64\lib -IC:\msys64\mingw64\include -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -o a.exe
[windows]
run: build
    set shell := ["powershell.exe", "-c"]
    .\a.exe