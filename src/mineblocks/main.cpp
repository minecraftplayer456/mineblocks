#include <spdlog/spdlog.h>

#include <engine/core/engine.hpp>

#include "mineblocks/core/mineblocks.hpp"

int main(int argc, char** argv)
{
    engine::core::Engine engine(new mineblocks::core::Mineblocks);

    engine.run();

    return 0;
}