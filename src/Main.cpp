#include "Mineblocks/Common/Error.hpp"

EXCEPTION(Mineblocks::Exception, TestException);

int main()
{
    try{
        THROW(TestException, "Alarm!!!");
    }
    catch (const Mineblocks::Exception& e) {
        LOG_CRITICAL(All, e.what());
    }

    return 0;
}
