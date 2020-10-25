#include <spdlog/spdlog.h>

#include <engine/core/engine.hpp>

#include "mineblocks/core/mineblocks.hpp"

int main(int argc, char** argv)
{
    engine::core::Engine::get()->run(new mineblocks::core::Mineblocks);

    return 0;
}