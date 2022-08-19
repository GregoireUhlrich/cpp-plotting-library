#ifndef CPT_FONTS_H_INCLUDED
#define CPT_FONTS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <filesystem>
#include "../utils/error.hpp"

namespace cpt::font
{
    class InvalidFontFileError: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    enum Class {
        Regular, Bold, Italic, ItalicBold
    };

    class FontFamily {

    public:
        static inline const std::filesystem::path absolute_path_location 
            = CPT_ABSOLUTE_FONT_PATH;

        struct FontFamilyData {
            std::string_view regular, bold, italic, italic_bold;
        };
    
    public:
        FontFamily(
            std::string_view      family_name,
            FontFamilyData const &family
        )
            : _family_name(family_name)
        {
            load_font(_family[Regular],    family.regular);
            load_font(_family[Bold],       family.bold);
            load_font(_family[Italic],     family.italic);
            load_font(_family[ItalicBold], family.italic_bold);
        }

        std::string const &get_family_name() const noexcept {
            return _family_name;
        }
        
        sf::Font const &get_font(Class class_) const {
            return _family[class_];
        }

    private:
        std::string _family_name;
        sf::Font    _family[4];

    private:
        void load_font(sf::Font &font, std::string_view file_name)
        {
            std::string path 
                = (absolute_path_location / _family_name / file_name).string();
            if (!font.loadFromFile(path)) {
                throw InvalidFontFileError(
                    std::quoted(path),
                    " does not exist or is an invalid font file."
                );
            }
        }
    };

    inline const FontFamily arial(
        "arial",
        {
            .regular     = "arial.ttf",
            .bold        = "arialbd.ttf",
            .italic      = "ariali.ttf",
            .italic_bold = "arialbi.ttf"
        }
    );

} // namespace cpt


#endif