#include "figure.hpp"


namespace cpt
{
    static unsigned int pixels_per_inch()
    {
        return 96;
    }

    Figure::Figure(std::string_view name, unsigned int width, unsigned int height)
        : _name(name),
            _width(width),
            _height(height)
    {

    }

    Figure::Figure(unsigned int width, unsigned int height)
        : Figure("Figure " + std::to_string(++n_figures), width, height)
    {

    }

    Figure::~Figure()
    {
        if (_execution_result.valid()) {
            _execution_result.wait();
        }
    }

    bool Figure::is_blocking() const noexcept {
        return _blocking;
    }

    void Figure::set_blocking(bool blocking) noexcept
    {
        _blocking = blocking;
    }

    void Figure::show()
    {
        if (_execution_result.valid()) {
            throw FigureConcurrencyError(
                "Cannot show a figure twice (tried for \"",
                _name, "\")!");
        }
        _execution_result = std::async(std::launch::async, &Figure::launch, this);
        if (_blocking) {
            _execution_result.wait();
        }
    }

    void Figure::launch()
    {
        std::lock_guard<std::mutex> guard(_mutex);
        Figure::create_window(
            _window,
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

    void Figure::create_window(
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
