#include "window.hpp"

namespace cpt
{
    static unsigned int pixels_per_inch()
    {
        return 96;
    }

    Window::Window(std::string_view name, std::size_t width, std::size_t height)
        : _name(name),
            _width(width),
            _height(height)
    {

    }

    Window::~Window()
    {
        if (_execution_result.valid()) {
            _execution_result.wait();
        }
    }


    sf::Vector2f Window::get_size() const noexcept
    {
        auto size = get_usize();
        return {
            static_cast<float>(size.x),
            static_cast<float>(size.y)
        };
    }

    sf::Vector2u Window::get_usize() const noexcept
    {
        return {
            static_cast<unsigned int>(_width) * pixels_per_inch(),
            static_cast<unsigned int>(_height) * pixels_per_inch(),
        };
    }

    bool Window::is_blocking() const noexcept {
        return _blocking;
    }

    void Window::set_blocking(bool blocking) noexcept
    {
        _blocking = blocking;
    }

    void Window::show()
    {
        if (_execution_result.valid()) {
            throw WindowConcurrencyError(
                "Cannot show a figure twice (tried for \"",
                _name, "\")!");
        }
        _execution_result = std::async(std::launch::async, &Window::launch, this);
        if (_blocking) {
            _execution_result.wait();
        }
    }

    void Window::launch()
    {
        std::lock_guard<std::mutex> guard(_mutex);
        auto size = get_usize();
        Window::create_window(
            _window,
            sf::VideoMode(size.x, size.y),
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

    void Window::create_window(
        sf::RenderWindow          &window,
        sf::VideoMode       const &mode,
        std::string         const &name,
        uint32_t                   style,
        sf::ContextSettings const &settings)
    {
        static std::mutex _mutex;
        std::lock_guard<std::mutex> lock(_mutex);
        window.create(mode, name, style, settings);
    }

} // namespace cpt
