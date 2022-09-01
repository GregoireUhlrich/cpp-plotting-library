#ifndef CPT_FONT_MANAGER_H_INCLUDED
#define CPT_FONT_MANAGER_H_INCLUDED

#include "fonts.hpp"
#include <unordered_map>

namespace cpt
{
    class FontManager {
    public:

        sf::Font &get_font(
            cpt::font::FontFamily const &family,
            cpt::font::Class             class_ = cpt::font::Regular
            );

        sf::Font &get_font(cpt::Font const &font);

    private:
        std::unordered_map<std::string, sf::Font> _fonts;
    };
} // namespace cpt

#endif // !CPT_FONT_MANAGER_H_INCLUDED
