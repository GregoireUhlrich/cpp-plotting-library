#ifndef CPT_X11_THREADS_H_INCLUDED
#define CPT_X11_THREADS_H_INCLUDED

#include <X11/Xlib.h>

namespace cpt
{
    inline bool _init_x11_threads()
    {
        XInitThreads();
        return true;
    }

    inline const bool _x11_threads_initialized = _init_x11_threads();

} // namespace cpt

#endif