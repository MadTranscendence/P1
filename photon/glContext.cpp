#include "common.h"
#include "glContext.h"


namespace Photon
{
    GlContext::GlContext(Window* window)
    {
        m_window = window;
        m_context = SDL_GL_CreateContext(window->getSDLWindow());
    }

    GlContext::~GlContext()
    {
        SDL_GL_DeleteContext(m_context);
    }

    Window* GlContext::getWindow()
    {
        return m_window;
    }

    const Window* GlContext::getWindow() const
    {
        return m_window;
    }
}
