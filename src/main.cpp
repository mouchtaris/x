#include <iostream>
#include "command.h"
#include "write::tuple.h"

struct poo_t { };
int main(int, char**)
{
    command_t<poo_t, int, double> comm { 12, 12.12l };
    std::cout << comm << '\n';
    return 0;
}
