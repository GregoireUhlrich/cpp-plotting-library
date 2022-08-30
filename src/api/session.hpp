#ifndef CPT_SESSION_H_INCLUDED
#define CPT_SESSION_H_INCLUDED

#include <map>
#include <concepts>
#include "figure.hpp"
#include "../graphics/font_manager.hpp"

namespace cpt
{
    class Session {
    
    public:

        Session();

        sf::Font const &get_main_font() const;

        sf::Font const &get_font(
            cpt::font::FontFamily const &family,
            cpt::font::Class             class_ = cpt::font::Regular
            );

        void set_main_font(
            cpt::font::FontFamily const &family,
            cpt::font::Class             class_ = cpt::font::Regular
            );

        size_t get_n_figures() const noexcept {
            return _n_figures;
        }

        Figure &get_figure(size_t i);

        Figure const &get_figure(size_t i) const;

        template<class ...FigArgs>
            requires std::constructible_from<cpt::Figure, cpt::Session&, FigArgs...>
        Figure &create_figure(FigArgs &&...args)
        {
            auto insertion_result = _figures.try_emplace(
                _n_figures++, 
                *this,
                std::forward<FigArgs>(args)...);
            cpt::Figure &fig = (insertion_result.first)->second;
            return fig;
        }

    private:

        FontManager              _font_manager;
        sf::Font                *_main_font;
        std::map<size_t, Figure> _figures;
        size_t                   _n_figures;
    };
} // namespace cpt

#endif // 
