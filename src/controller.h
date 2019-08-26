#ifndef TIC_TAC_TOE_CONTROLLER_H
#define TIC_TAC_TOE_CONTROLLER_H

#include <SDL2/SDL.h>
#include "solver.h"

class Controller
{
private:
    int gridCellSize;
    int frameSize;
    int windowWidth;
    int windowHeight;
  

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Rect gridCursor;
    SDL_Rect gridCursorHoover;

    SDL_Color gridBackground;
    SDL_Color gridLineColor;
    SDL_Color gridCursorHooverColor;
    SDL_Color gridCursorColor;

    SDL_Surface *imageP1;
    SDL_Texture *textureP1;
    SDL_Surface *imageP2;
    SDL_Texture *textureP2;

    FieldType fieldTypeP1;
    FieldType fieldTypeP2;

    void waitForInput(bool &quit, bool &userPlayed);
    void drawGridState(Solver &solver);
    void drawGridLines();
    void makeFirstMove(Solver &solver, const FieldType type);

public:
    Controller(int frameSizeIn);
    ~Controller();

    /*
     * Constructs the visual representation,
     * should be used once to start the programm.
     */
    int initializeView();

    /*
     * Updates View on change
     */
    void updateView(Solver &solver);
};

#endif