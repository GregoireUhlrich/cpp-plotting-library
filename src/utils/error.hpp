#ifndef CPT_ERROR_H_INCLUDED
#define CPT_ERROR_H_INCLUDED

#include "printable.hpp"
#include <exception>
#include <sstream>

namespace cpt
{
   
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

class IndexError: public cpt::Exception {
    using Exception::Exception;
};

} // namespace cpt


#endif