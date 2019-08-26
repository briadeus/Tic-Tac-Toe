#include "controller.h"
#include "solver.h"
#include "view.h"

int main()
{

    View v;

    v.initialize();

    Solver s;

    Controller controller(v, s);

    controller.execute();

    return 0;
}