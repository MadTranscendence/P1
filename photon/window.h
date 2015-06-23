#ifndef WINDOW_H
#define WINDOW_H

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

        SDL_Window* getSDLWindow();
        bool isClosed();

    private:
        SDL_Window* m_window;
        bool m_isClosed;
    };
}

#endif
