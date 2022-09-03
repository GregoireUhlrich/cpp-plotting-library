#include "font_manager.hpp"

namespace cpt {

    cpt::Font &FontManager::get_font(
        cpt::font::FontFamily const &family,
        cpt::font::Class             class_
        ) 
    {
        std::string const &name = family.get_font_file_name(class_);
        auto pos = _fonts.find(name);
        if (pos == _fonts.end()) {
            cpt::Font &font = _fonts[name];
            cpt::font::load(font, name);
        }
        return _fonts[name];
    }

} // namespace cpt
