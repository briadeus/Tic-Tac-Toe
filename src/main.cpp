#include "controller.h"
#include "solver.h"
int main()
{

    int frameSize = 3;
    int wininningSize = 3;
    Controller controller(frameSize);

    controller.initializeView();

    Solver s(frameSize, wininningSize);

    // plays -on click get value
    // set display, update state
    // compute next move
    // update display
    // tell if end or continue
    controller.updateView(s);

    return 0;
}