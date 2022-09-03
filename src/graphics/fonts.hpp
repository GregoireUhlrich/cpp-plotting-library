#ifndef CPT_FONTS_H_INCLUDED
#define CPT_FONTS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <array>
#include "../utils/error.hpp"

namespace cpt
{
    using Font = sf::Font;
} // namespace cpt

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
            _family[Regular]    = (absolute_path_location / _family_name / family.regular).string();
            _family[Bold]       = (absolute_path_location / _family_name / family.bold).string();
            _family[Italic]     = (absolute_path_location / _family_name / family.italic).string();
            _family[ItalicBold] = (absolute_path_location / _family_name / family.italic_bold).string();
        }

        std::string const &get_family_name() const noexcept {
            return _family_name;
        }
        
        std::string const &get_font_file_name(Class class_) const {
            return _family[class_];
        }

    private:
        std::string                _family_name;
	    std::array<std::string, 4> _family;
    };

    inline void load(cpt::Font &font, std::string const &file_name)
    {
        if (!font.loadFromFile(file_name)) {
            throw InvalidFontFileError(
                std::quoted(file_name),
                " does not exist or is an invalid font file."
            );
        }
    }

    inline const FontFamily arial(
        "arial",
        {
            .regular     = "arial.ttf",
            .bold        = "arialbd.ttf",
            .italic      = "ariali.ttf",
            .italic_bold = "arialbi.ttf"
        }
    );

} // namespace cpt::font


#endif
