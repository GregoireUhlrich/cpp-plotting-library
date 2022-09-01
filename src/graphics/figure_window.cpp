#include "figure_window.hpp"

namespace cpt
{
    static unsigned int pixels_per_inch()
    {
        return 96;
    }

    FigureWindow::FigureWindow(
        std::string_view name, 
        std::size_t width, 
        std::size_t height)
        : _name(name),
          _width(width),
          _height(height)
    {

    }

    FigureWindow::~FigureWindow()
    {
        wait_for_close();
    }

    void FigureWindow::wait_for_close() const
    {
        if (_execution_result.valid()) {
            _execution_result.wait();
        }
    }


    sf::Vector2f FigureWindow::get_size() const noexcept
    {
        auto size = get_usize();
        return {
            static_cast<float>(size.x),
            static_cast<float>(size.y)
        };
    }

    sf::Vector2u FigureWindow::get_usize() const noexcept
    {
        return {
            static_cast<unsigned int>(_width) * pixels_per_inch(),
            static_cast<unsigned int>(_height) * pixels_per_inch(),
        };
    }

    bool FigureWindow::is_blocking() const noexcept {
        return _blocking;
    }

    void FigureWindow::set_blocking(bool blocking) noexcept
    {
        _blocking = blocking;
    }

    void FigureWindow::show(
        std::function<void(sf::RenderTarget&)> draw_callback)
    {
        if (_execution_result.valid()) {
            throw FigureConcurrencyError(
                "Cannot show a figure twice (tried for \"",
                _name, "\")!");
        }
        _execution_result = std::async(std::launch::async, 
            &FigureWindow::launch, this, draw_callback);
        if (_blocking) {
            _execution_result.wait();
        }
    }

    void FigureWindow::launch(
        std::function<void(sf::RenderTarget&)> draw_callback)
    {
        std::lock_guard<std::mutex> guard(_mutex);
        auto size = get_usize();
        FigureWindow::create_window(
            _window,
            sf::VideoMode(size.x, size.y),
            _name,
            sf::Style::Close | sf::Style::Titlebar
            );
        while (_window.isOpen()) {
            _window.clear(sf::Color::White);
            draw_callback(_window);
            _window.display();
            sf::Event event;
            while (_window.waitEvent(event)) {
                if (event.type == sf::Event::Closed)
                    _window.close();
            }
        }
    }

    void FigureWindow::create_window(
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
