build:
    g++ --std=c++11 -L/opt/homebrew/lib -I/opt/homebrew/include  -lSDL2 -lSDL2_mixer sample.cpp SDL_Plotter.cpp
run: build
    ./a.out
    
