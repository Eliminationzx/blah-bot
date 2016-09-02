#include <iostream>

//#include "spdlog/spdlog.h"

#include "src/index/Worker.h"

using namespace std;
//using namespace spdlog;

int main (int argc, char *argv[]) {
    cout << "Hello, world!\n";
    cout << "Vasya\n";

    Worker w;

    w.start ();

    return 0;
}
