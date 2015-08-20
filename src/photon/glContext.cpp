#include "../common.hpp"
#include "glContext.hpp"


namespace Photon
{
    GlContext::GlContext(Window* window)
    {
        m_window = window;
        m_context = SDL_GL_CreateContext(window->getSDLWindow());

        SDLLog(SDL_GL_SetSwapInterval(1));

        std::cout << "Created gl context with window " << m_window->getSDLWindow() << '\n';
    }

    GlContext::~GlContext()
    {
        SDL_GL_DeleteContext(m_context);

        std::cout << "Destructed gl context with window " << m_window->getSDLWindow() << '\n';
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
