#include "common.h"
#include "window.h"


namespace Photon
{
    Window::Window(WindowDesc& windowDesc)
    {
        unsigned flags = SDL_WINDOW_OPENGL;

        if(windowDesc.isFullscreen)
            flags += SDL_WINDOW_FULLSCREEN;

        m_window = SDL_CreateWindow(
            windowDesc.title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowDesc.width,
            windowDesc.height,
            flags
        );

        m_isClosed = false;
    }

    Window::~Window()
    {
        if(m_window != nullptr)
            SDL_DestroyWindow(m_window);
    }

    void Window::update()
    {
        static SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                m_isClosed = true;
                break;
            }
        }
    }

    void Window::swap()
    {
        SDL_GL_SwapWindow(m_window);
    }

    SDL_Window* Window::getSDLWindow()
    {
        return m_window;
    }

    bool Window::isClosed()
    {
        return m_isClosed;
    }
}
