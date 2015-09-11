#include "../common.hpp"
#include "game.hpp"

#include "../core/core.hpp"
#include "../core/frameTimer.hpp"

#include "../photon/glContext.hpp"
#include "../photon/photon.hpp"
#include "../photon/window.hpp"


Game::Game()
{
    std::cout << "Super creative indie puzzle adventure GNU/Game v0.0.2\n";
}

Game::~Game()
{

}

int Game::run()
{
    Core::Core core;

    Photon::Photon photon;

    Photon::WindowDesc windowDesc;
    windowDesc.width  = 800;
    windowDesc.height = 600;
    windowDesc.isFullscreen = false;
    windowDesc.title  = "P1";

    Photon::Window    window(windowDesc);
    Photon::GlContext glContext(&window);

    Core::FrameTimer frameTimer;
    frameTimer.start();

    while(!window.isClosed())
    {
        frameTimer.update();
        if(frameTimer.didFpsChanged())
            window.setTitle("P1 \t" + std::to_string(lrint(frameTimer.getFps())) + " fps");

        window.processEvents();
        window.swap();
    }

    return 0;
}
