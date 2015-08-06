#include "common.hpp"
#include "glContext.hpp"


namespace Photon
{
    GlContext::GlContext(Window* window)
    {
        m_window = window;
        m_context = SDL_GL_CreateContext(window->getSDLWindow());

        SDLLog(SDL_GL_SetSwapInterval(1));

        SDLLog(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,    1));
        SDLLog(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,    2));
        SDLLog(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3));
        SDLLog(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3));
        SDLLog(SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,    1));

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
