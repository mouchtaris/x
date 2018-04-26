#include <tuple>
#include <functional>
#include <iostream>
#include <cassert>

#include "execution_context.h"
#include "execution_context_spec.h"

using std::move,
      std::get
      ;


namespace
{
    template <typename T> void run_test(T = {});
}
int main(int, char**)
{
    run_test<execution_context_spec::data>();
    return 0;
}
///
namespace
{
    template <
        typename T
        >
    void run_test(T test)
    {
        initialize(test);
        std::cerr << " *** TEST " << name(test) << " ***\n";

        std::cerr << "   . . . setting up . . .\n";
        setup(test);

        std::cerr << "   . . . running . . .\n";
        run(test);

        std::cerr << "   . . . result: " << 
            (check(test)? "success" : "FAILURE");

        std::cerr << std::endl;
    }
}
