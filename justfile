brew_dir := env_var("HOMEBREW_PREFIX")
files := "plotduck.cpp picture.cpp"
default: run
build:
    g++ --std=c++11 -L{{brew_dir}}/lib -I{{brew_dir}}/include  -lSDL2 -lSDL2_mixer {{files}} SDL_Plotter.cpp
run: build
    ./a.out
