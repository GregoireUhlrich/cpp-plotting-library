#ifndef CPT_FIGURE_H_INCLUDED
#define CPT_FIGURE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <future>
#include "x11_threads.hpp"

namespace cpt
{
    static unsigned int pixels_per_inch()
    {
        return 96;
    }

    class Figure {
    
    public:

        Figure(std::string_view name, unsigned int width, unsigned int height)
            : _name(name),
              _width(width),
              _height(height)
        {

        }

        Figure(unsigned int width, unsigned int height)
            : Figure("Figure " + std::to_string(++n_figures), width, height)
        {

        }

        Figure(Figure const &) = delete;

        Figure(Figure &&) = default;

        ~Figure()
        {
            if (_execution_result.valid()) {
                _execution_result.wait();
            }
        }

        bool is_blocking() const noexcept {
            return _blocking;
        }

        void set_blocking(bool blocking) noexcept
        {
            _blocking = blocking;
        }

        void show()
        {
            _execution_result = std::async(std::launch::async, &Figure::launch, this);
            if (_blocking) {
                _execution_result.wait();
            }
        }

    protected:

        void launch()
        {
            _window.create(
                sf::VideoMode(_width*pixels_per_inch(), _height*pixels_per_inch()),
                _name,
                sf::Style::Close | sf::Style::Titlebar
                );
            while (_window.isOpen()) {
                sf::Event event;
                while (_window.waitEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        _window.close();
                }
            }
        }

    private:
        std::string       _name;
        unsigned int      _width;
        unsigned int      _height;
        sf::RenderWindow  _window;
        bool              _blocking = false;
        std::future<void> _execution_result;

    private:
        static inline unsigned int n_figures = 0;
    };
} // namespace cpt


#endif