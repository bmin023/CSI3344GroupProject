brew_dir := env_var("HOMEBREW_PREFIX")

build:
    g++ --std=c++11 -L{{brew_dir}}/lib -I{{brew_dir}}/include  -lSDL2 -lSDL2_mixer sample.cpp SDL_Plotter.cpp
run: build
    ./a.out
