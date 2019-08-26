#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <random>
#include "controller.h"

Controller::Controller(const int frameSizeIn) : fieldTypeP1(FieldType::CIRCLE),
                                                fieldTypeP2(FieldType::CROSS), gridCellSize(72), frameSize(frameSizeIn)
{

    // + 1 so that the last grid lines fit in the screen.
    windowWidth = (frameSize * gridCellSize) + 1;
    windowHeight = (frameSize * gridCellSize) + 1;
}
Controller::~Controller()
{
    SDL_DestroyTexture(textureP1);
    SDL_FreeSurface(imageP1);
    SDL_DestroyTexture(textureP2);
    SDL_FreeSurface(imageP2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*
 * Grid Design adapted from
 * https://github.com/catsocks/sdl-grid
 */
int Controller::initializeView()
{

    // Place the grid cursor in the middle of the screen.
    gridCursor = {
        .x = ((frameSize - 1) / 2 * gridCellSize),
        .y = ((frameSize - 1) / 2 * gridCellSize),
        .w = gridCellSize,
        .h = gridCellSize,
    };

    // The cursor ghost is a cursor that always shows in the cell below the
    // mouse cursor.
    gridCursorHoover = {gridCursor.x, gridCursor.y, gridCellSize,
                        gridCellSize};

    SDL_Color gridBackground = {255, 255, 255, 255};  // Barely Black
    SDL_Color gridLineColor = {22, 22, 22, 255};      // Dark grey
    SDL_Color gridCursorColor = {255, 255, 255, 255}; // White

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return EXIT_FAILURE;
    }

    if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window,
                                    &renderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, GAME_TITLE.c_str());

    // Draw grid background.
    SDL_SetRenderDrawColor(renderer, gridBackground.r, gridBackground.g,
                           gridBackground.b, gridBackground.a);

    imageP1 = SDL_LoadBMP((RES_ROOT_PATH + IMAGE_P1).c_str());
    textureP1 = SDL_CreateTextureFromSurface(renderer, imageP1);

    imageP2 = SDL_LoadBMP((RES_ROOT_PATH + IMAGE_P2).c_str());
    textureP2 = SDL_CreateTextureFromSurface(renderer, imageP2);

    SDL_RenderClear(renderer);
    drawGridLines();
}

void Controller::updateView(Solver &solver)
{

    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool quit = false;
    bool gameOver = false;
    bool userPlayed = false;
    SDL_bool mouse_active = SDL_FALSE;
    SDL_bool mouse_hover = SDL_FALSE;

    makeFirstMove(solver, fieldTypeP2);
    drawGridState(solver);
    drawGridLines();
    SDL_RenderPresent(renderer);

    while (!quit)
    {

        frame_start = SDL_GetTicks();

        waitForInput(quit, userPlayed);

        if (userPlayed && !gameOver)
        {
            int selectedIndex = (gridCursor.x / gridCellSize) + ((gridCursor.y / gridCellSize) * (frameSize));

            if (solver.isEmptyField(selectedIndex))
            {

                if (solver.isWinningField(selectedIndex, fieldTypeP1))
                {
                    SDL_SetWindowTitle(window, (GAME_TITLE + " MEAT WON ").c_str());
                    solver.setFieldValue(selectedIndex, fieldTypeP1);
                    gameOver = true;
                }
                else
                {
                    solver.setFieldValue(selectedIndex, fieldTypeP1);
                    std::cout << "Solving \n";
                    int response = solver.solve(fieldTypeP2, 2);
                    std::cout << "Solved " << response << " \n";
                    if (solver.getWinningIndex() >= 0)
                    {
                        solver.setFieldValue(solver.getWinningIndex(), fieldTypeP2);
                    }
                }
            }

            drawGridState(solver);

            // Draw grid lines.
            drawGridLines();
            SDL_RenderPresent(renderer);
            userPlayed = false;
        }

        // Draw grid cursor.

        //SDL_RenderPresent(renderer);

        frame_end = SDL_GetTicks();
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000)
        {

            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        std::size_t kFramesPerSecond{60};
        std::size_t target_frame_duration{1000 / kFramesPerSecond};

        if (frame_duration < target_frame_duration)
        {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

/* PRIVATE */

void Controller::waitForInput(bool &quit, bool &userPlayed)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

        switch (event.type)
        {

        case SDL_MOUSEBUTTONDOWN:

            userPlayed = true;
            gridCursor.x = (event.motion.x / gridCellSize) * gridCellSize;
            gridCursor.y = (event.motion.y / gridCellSize) * gridCellSize;
            break;
        case SDL_QUIT:

            quit = true;
            break;
        }
    }
}

void Controller::drawGridLines()
{
    SDL_SetRenderDrawColor(renderer, gridLineColor.r, gridLineColor.g,
                           gridLineColor.b, gridLineColor.a);
    for (int x = 0; x < 1 + frameSize * gridCellSize;
         x += gridCellSize)
    {
        SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);
    }

    for (int y = 0; y < 1 + frameSize * gridCellSize;
         y += gridCellSize)
    {
        SDL_RenderDrawLine(renderer, 0, y, windowWidth, y);
    }
}

/*
 * Using uniform distribution, the first move is just a random field.
 * https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
 */
void Controller::makeFirstMove(Solver &solver, const FieldType type)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, (frameSize * frameSize) - 1);
    int startingPosition = dis(gen);
    solver.setFieldValue(3, type);
}

void Controller::drawGridState(Solver &solver)
{

    gridCursor.x = 0;
    gridCursor.y = 0;

    for (int i = 0; i < frameSize * frameSize; i++)
    {

        int shiftX = i % frameSize;
        int shiftY = i / frameSize;
        gridCursor.x = (gridCellSize * shiftX);
        gridCursor.y = (gridCellSize * shiftY);

        if (!solver.isEmptyField(i))
        {

            SDL_Rect dstrect = {gridCursor.x, gridCursor.y, gridCellSize, gridCellSize};
            if (solver.getFieldState(i) == fieldTypeP1)
            {
                SDL_RenderCopy(renderer, textureP1, NULL, &dstrect);
            }
            else
            {
                SDL_RenderCopy(renderer, textureP2, NULL, &dstrect);
            }

            SDL_RenderPresent(renderer);
        }
        else
        {

            SDL_SetRenderDrawColor(renderer, 255,
                                   255, 255,
                                   gridCursorColor.a);
            SDL_RenderFillRect(renderer, &gridCursor);
            SDL_RenderPresent(renderer);
        }
    }
}