#pragma once
namespace test
{
    struct spy
    {
        bool called = false;
        void operator () () { called = true; }
    };
}
