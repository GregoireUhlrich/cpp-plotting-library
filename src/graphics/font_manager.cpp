#include "font_manager.hpp"

namespace cpt {

    sf::Font &FontManager::get_font(
        cpt::font::FontFamily const &family,
        cpt::font::Class             class_
        ) 
    {
        std::string const &name = family.get_font_file_name(class_);
        auto pos = _fonts.find(name);
        if (pos == _fonts.end()) {
            sf::Font &font = _fonts[name];
            cpt::font::load(font, name);
        }
        return _fonts[name];
    }

    sf::Font &FontManager::get_font(cpt::Font const &font)
    {
        return this->get_font(font.family, font.class_);
    }

} // namespace cpt
