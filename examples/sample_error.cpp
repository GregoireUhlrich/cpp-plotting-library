#include "utils/error.h"

struct IndexError: public Exception {
    using Exception::Exception;
};

int main()
{
    try {
        throw IndexError("Index ", 5, " out of bounds for container of size ", 10);
    }
    catch (IndexError const &exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}