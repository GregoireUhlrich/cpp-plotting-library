#ifndef CPT_FONT_MANAGER_H_INCLUDED
#define CPT_FONT_MANAGER_H_INCLUDED

#include "fonts.hpp"
#include <unordered_map>

namespace cpt
{
    class FontManager {
    public:

        cpt::Font &get_font(
            cpt::font::FontFamily const &family,
            cpt::font::Class             class_ = cpt::font::Regular
            );

    private:
        std::unordered_map<std::string, cpt::Font> _fonts;
    };
} // namespace cpt

#endif // !CPT_FONT_MANAGER_H_INCLUDED
