#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <memory>
#include <SDL2/SDL.h>
#include <string>


namespace Photon
{
    struct WindowDesc
    {
        int         width;
        int         height;
        std::string title;
        bool        isFullscreen;
    };

    class Window
    {
    public:
        Window(WindowDesc& windowDesc);
        ~Window();

        void update();
        void swap();

        void setTitle(std::string title);

        SDL_Window* getSDLWindow();
        bool isClosed();

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
        bool m_isClosed;
    };
}

#endif
