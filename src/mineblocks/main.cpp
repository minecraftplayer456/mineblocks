#include <engine/core/engine.hpp>

#include "core/mineblocks.hpp"

int main(int argc, char** argv)
{
    mineblocks::core::Mineblocks mineblocks;

    engine::core::Engine engine(&mineblocks);

    engine.run();

    return 0;
}