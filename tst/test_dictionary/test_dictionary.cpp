//
// Created by peter on 3/29/15.
//

#include <iostream>
#include <memory>
#include <UnixDictionary.h>

int main(int argc, char **argv) {
    std::unique_ptr<Dictionary> dictionary(new UnixDictionary());
    std::cout << std::boolalpha << dictionary->check("hello") << "," << dictionary->check("frfrf") << std::endl;
    std::cout << dictionary->check("tricycle") << "," << dictionary->check("trombone") << std::endl;
    return 0;
}
