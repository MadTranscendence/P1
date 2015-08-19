#include "../common.hpp"
#include "window.hpp"


namespace Photon
{
    Window::Window(WindowDesc& windowDesc) : m_window(nullptr, SDL_DestroyWindow)
    {
        unsigned flags = SDL_WINDOW_OPENGL;

        if(windowDesc.isFullscreen)
            flags += SDL_WINDOW_FULLSCREEN;

        m_window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
            SDL_CreateWindow(
                windowDesc.title.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                windowDesc.width,
                windowDesc.height,
                flags
            ), SDL_DestroyWindow);

        m_isClosed = false;

        std::cout << "Created window " << m_window.get() << '\n';
    }

    Window::~Window()
    {
        std::cout << "Destructed window " << m_window.get() << '\n';
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
        SDL_GL_SwapWindow(m_window.get());
    }

    void Window::setTitle(std::string title)
    {
        SDL_SetWindowTitle(m_window.get(), title.c_str());
    }

    SDL_Window* Window::getSDLWindow()
    {
        return m_window.get();
    }

    bool Window::isClosed()
    {
        return m_isClosed;
    }
}
