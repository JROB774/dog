#include "main_web.hpp"

void main_loop ()
{
    // @Incomplete: ...
}

int main (int argc, char** argv)
{
    InitWindow();
    emscripten_set_main_loop(main_loop, -1, 1);

    return 0;
}
