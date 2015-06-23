#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include "window.h"


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
