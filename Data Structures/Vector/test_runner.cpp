#include "test_runner.h"

//----------------------------------------------------------------------------------------------------
void ASSERT(bool b, const std::string& hint)
{
    ASSERT_EQUAL(b, true, hint);
}
//----------------------------------------------------------------------------------------------------
TestRunner::~TestRunner()
{
    if (fail_count > 0)
    {
        std::cerr << "========================================" << "\n"
                  << "FAILED (failures = " << fail_count << ")" << "\n"
                  << "========================================" << std::endl;
        exit(1);
    }
    else
    {
        std::cerr << "========================================" << "\n"
                  << "OK" << "\n"
                  << "========================================" << std::endl;
    }
}
//----------------------------------------------------------------------------------------------------