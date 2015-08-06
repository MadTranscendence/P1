#ifndef GL_CONTEXT_HPP
#define GL_CONTEXT_HPP

#include "window.hpp"


namespace Photon
{
    class GlContext
    {
    public:
        GlContext(Window* window);
        ~GlContext();

        Window*       getWindow();
        const Window* getWindow() const;

    private:
        SDL_GLContext m_context;
        Window*       m_window;
    };
}

#endif
