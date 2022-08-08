#ifndef CPT_FIGURE_H_INCLUDED
#define CPT_FIGURE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <future>
#include <mutex>
#include "internal/x11_threads.hpp"
#include "../utils/error.hpp"

namespace cpt
{
    class FigureConcurrencyError: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    class Figure {
    
    public:

        Figure(std::string_view name, unsigned int width, unsigned int height);

        Figure(unsigned int width, unsigned int height);

        Figure(Figure const &) = delete;

        Figure(Figure &&) = default;

        ~Figure();

        bool is_blocking() const noexcept;

        void set_blocking(bool blocking) noexcept;

        void show();

    protected:

        void launch();

        static void create_window(
            sf::RenderWindow          &window,
            sf::VideoMode       const &mode,
            std::string         const &name,
            uint32_t                   style,
            sf::ContextSettings const &settings = sf::ContextSettings());

    private:
        std::string       _name;
        unsigned int      _width;
        unsigned int      _height;
        sf::RenderWindow  _window;
        bool              _blocking = false;
        std::future<void> _execution_result;
        std::mutex        _mutex;

    private:
        static inline unsigned int n_figures = 0;
    };
} // namespace cpt


#endif