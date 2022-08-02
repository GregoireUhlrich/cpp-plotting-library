#ifndef CPP_PLOT_ERROR_H_INCLUDED
#define CPP_PLOT_ERROR_H_INCLUDED

#include "printable.h"
#include <exception>
#include <sstream>

class Exception: public std::exception {
public:
    Exception(Printable auto &&...args)
    {
        std::ostringstream sout;
        (sout << ... << args);
        _message = sout.str();
    }

    char const *what() const noexcept {
        return _message.c_str();
    }
    
private:
    std::string _message;
};

#endif