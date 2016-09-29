#include <iostream>

//#include "spdlog/spdlog.h"

#include "src/index/Worker.h"
#include "Engine.h"

using namespace std;
//using namespace spdlog;

int main (int argc, char *argv[]) {
    cout << "Hello, world!\n";

    Engine e;

    e.start ();

    return 0;
}
