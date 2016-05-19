#include "../common.hpp"
#include "window.hpp"

#include <cassert>
#include <vector>


namespace Photon
{
    Window::Window(WindowDesc& windowDesc) : m_window(nullptr, SDL_DestroyWindow)
    {
        SDLLog(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3));
        SDLLog(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3));
        SDLLog(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,    1));
        SDLLog(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,    2));
        SDLLog(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,          1));
        SDLLog(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,           24));

        uint flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

        if(windowDesc.isFullscreen)
            flags |= SDL_WINDOW_FULLSCREEN;

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

        //////////////
        /// Test
        /// Waiting for rendering implementation
        ///
        std::vector<SDL_DisplayMode> displayModes;
        displayModes.reserve(20);

        int numVideoDisp = SDLLog(SDL_GetNumVideoDisplays());
        for(int i = 0; i < numVideoDisp; ++i)
        {
            const char* name = SDL_GetDisplayName(i);

            std::cout << '\n' << name << ":\n";

            int numDisp = SDLLog(SDL_GetNumDisplayModes(i));
            for(int j = 0; j < numDisp; ++j)
            {
                SDL_DisplayMode dispMode;
                SDLLog(SDL_GetDisplayMode(i, j, &dispMode));
                displayModes.push_back(dispMode);

                std::cout << '\t' << dispMode.w << " x " << dispMode.h << ", "
                          << dispMode.refresh_rate  << "Hz, " << dispMode.format << '\n';
            }
        }

        SDLLog(SDL_SetWindowDisplayMode(m_window.get(), &displayModes.front()));
        ///
        /// End Test
        //////////////
    }

    Window::~Window()
    {
        std::cout << "Destructed window " << m_window.get() << '\n';
    }

    void Window::processEvents()
    {
        static SDL_Event event;
        if(SDL_PollEvent(&event))
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
