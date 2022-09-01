#include "figure.hpp"
#include "session.hpp"
#include "../utils/error.hpp"
#include "../graphics/fonts.hpp"

namespace cpt
{
    Figure::Figure( 
        Session    &session,
        std::size_t width, 
        std::size_t height)
        : Figure(
            session, 
            "Figure " + std::to_string(session.get_n_figures()), 
            width, height)
    {

    }

    Figure::Figure(
        Session         &session,
        std::string_view name, 
        std::size_t      width, 
        std::size_t      height)
        : _window(
            name, 
            width, 
            height)
    {
        create_subplots(1, 1);
        set_font(session.get_main_font());
    }

    Figure::~Figure()
    {
        _window.wait_for_close();
    }

    void Figure::create_subplots(
        std::size_t n_rows, 
        std::size_t n_columns,
        cpt::GridLayoutConfig const &config)
    {
        _subplots = std::vector<Subplot>(n_rows * n_columns);
        for (auto &subplot : _subplots) {
            subplot.set_font(get_font());
        }
        _n_rows = n_rows;
        _n_columns = n_columns;
        sf::Vector2f size = _window.get_size();
        apply_grid_layout(
            sf::FloatRect(0.f, 0.f, size.x, size.y),
            *this,
            config);
    }

    Subplot const &Figure::get_subplot(
        std::size_t i_row, 
        std::size_t i_col) const
    {
        if (i_row >= _n_rows) {
            throw cpt::IndexError("Index ", i_row, " out of bounds ",
            "of figure subplots with ", _n_rows, " rows.");
        }
        if (i_col >= _n_columns) {
            throw cpt::IndexError("Index ", i_col, " out of bounds ",
            "of figure subplots with ", _n_columns, " columns.");
        }
        auto index = i_row * _n_columns + i_col;
        return _subplots[index];
    }

    Subplot &Figure::get_subplot(
        std::size_t i_row, 
        std::size_t i_col)
    {
        return const_cast<Subplot&>(
            const_cast<const Figure*>(this)->get_subplot(i_row, i_col)
            );
    }

    Subplot const &Figure::get_subplot() const
    {
        if (_n_rows > 1 || _n_columns > 1) {
            throw cpt::IndexError("Cannot call Figure::get_subplot() ",
            "with no index for a figure with more than one (",
            _n_columns*_n_rows, ") subplots. Use ",
            "Figure::getSubplot(std::size_t, std::size_t) instead.");
        }
        return _subplots[0];
    }

    Subplot &Figure::get_subplot()
    {
        return const_cast<Subplot&>(
            const_cast<const Figure*>(this)->get_subplot()
            );
    }

    std::vector<Subplot> const &Figure::get_subplots() const noexcept
    {
        return _subplots;
    }

    std::vector<Subplot> &Figure::get_subplots() noexcept
    {
        return const_cast<std::vector<Subplot>&>(
            const_cast<const Figure*>(this)->get_subplots()
            );
    }

    sf::Font const &Figure::get_font() const 
    {
        return *_font;
    }

    void Figure::set_font(sf::Font const &font)
    {
        _font = &font;
        for (auto &subplot : _subplots) {
            subplot.set_font(font);
        }
    }

    void Figure::show(bool blocking) 
    {
        _window.set_blocking(blocking);
        for (auto &subplot : _subplots) {
            subplot.display();
        }
        _window.show([this](sf::RenderTarget &target) {
            for (const auto &subplot : _subplots) {
                target.draw(subplot.get_sprite());
            }
        });
    }

} // namespace cpt
