#include "session.hpp"
#include "../utils/error.hpp"

namespace cpt
{
    Session::Session()
    {
        set_main_font(cpt::font::arial, cpt::font::Regular);
    }

    sf::Font const &Session::get_font(
        cpt::font::FontFamily const &family,
        cpt::font::Class             class_
        )
    {
        return _font_manager.get_font(family, class_);
    }

    sf::Font const &Session::get_main_font() const 
    {
        return *_main_font;
    }

    void Session::set_main_font(
        cpt::font::FontFamily const &family,
        cpt::font::Class             class_
        )
    {
        _main_font = &_font_manager.get_font(family, class_);
    }

    cpt::Figure const &Session::get_figure(size_t i) const
    {
        if (i >= _n_figures) {
            throw cpt::IndexError(
                "Index ", i, " out of bounds for session ",
                "with ", _n_figures, " figures.");
        }
        auto pos = _figures.find(i);
        return pos->second;
    }

    cpt::Figure &Session::get_figure(size_t i)
    {
        return const_cast<cpt::Figure&>(
            const_cast<Session const*>(this)->get_figure(i));
    }

} // namespace cpt
