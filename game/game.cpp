#include "common.h"
#include "game.h"

#include "../photon/glContext.h"
#include "../photon/photon.h"
#include "../photon/window.h"


Game::Game()
{

}

Game::~Game()
{

}

int Game::run()
{
    std::cout << "Super creative indie puzzle adventure GNU/Game v0.0.1";

    Photon::init();

    Photon::WindowDesc windowDesc;
    windowDesc.width  = 800;
    windowDesc.height = 600;
    windowDesc.isFullscreen = false;
    windowDesc.title = "P1";

    Photon::Window    window(windowDesc);
    Photon::GlContext glContext(&window);

    while(!window.isClosed())
    {
        window.update();
        window.swap();
    }

    Photon::release();

    return 0;
}
