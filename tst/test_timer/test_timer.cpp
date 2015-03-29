//
// Created by peter on 3/29/15.
//

#include <Timer.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char **argv) {
    Timer timer;
    timer.start();
    ::sleep(1);
    std::cout << timer.elapsedNs() << std::endl;
    timer.start();
    ::sleep(2);
    std::cout << timer.elapsedNs() << std::endl;
    return 0;
}

