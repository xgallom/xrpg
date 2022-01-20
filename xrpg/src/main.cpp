#include <core/error.h>
#include "run/run.h"

int main()
{
    const auto init = engine::init();
    const auto &context = init.context;

    if (init.wasSuccessful)
        engine::run(context, run::XrpgRunHandlers);
    else
        printSdlError();

    engine::deinit(context);
    return 0;
}
