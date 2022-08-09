#include "grid_layout.hpp"
#include "../utils/error.hpp"
#include "figure.hpp"

namespace cpt
{
    class InvalidLayoutError: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    static void checkLayout(
        sf::FloatRect              bounds,
        std::size_t                n_rows,
        std::size_t                n_columns,
        GridLayoutConfig    const &config
    )
    {
        float hsize = bounds.width * (1 - config.offset_left - config.offset_right
                - config.hspace * static_cast<float>(n_columns - 1));
        if (hsize / static_cast<float>(n_columns) < static_cast<float>(min_subplot_n_pix)) {
            throw InvalidLayoutError("Figure too small, there is not enough",
            " space (", hsize, ") to have at least ", 
            min_subplot_n_pix, " pixels per subplot ",
            "horizontally. Consider crating a bigger figure or changing the ",
            "layout configuration.");
        }
        float vsize = bounds.height * (1 - config.offset_top - config.offset_bottom
                - config.vspace * static_cast<float>(n_rows - 1));
        if (vsize / static_cast<float>(n_rows) < static_cast<float>(min_subplot_n_pix)) {
            throw InvalidLayoutError("Figure too small, there is not enough",
            " space (", vsize, ") to have at least ", 
            min_subplot_n_pix, " pixels per subplot ",
            "vertically. Consider crating a bigger figure or changing the ",
            "layout configuration.");
        }
    }

    void apply_grid_layout(
        sf::FloatRect           bounds,
        cpt::Figure            &figure,
        GridLayoutConfig const &config)
    {
        std::cout << figure.get_size().x << " " << figure.get_size().y << '\n';
        std::size_t n_rows = figure.get_n_rows();
        std::size_t n_columns = figure.get_n_columns();
        checkLayout(bounds, n_rows, n_columns, config);
        float Lx = bounds.width * (1 - config.offset_left - config.offset_right
                - config.hspace * static_cast<float>(n_columns - 1)); 
        float Ly = bounds.height * (1 - config.offset_top - config.offset_bottom
                - config.vspace * static_cast<float>(n_rows - 1));
        float sx = Lx / static_cast<float>(n_columns);
        float sy = Ly / static_cast<float>(n_rows);

        float y = bounds.top + bounds.height * config.offset_top;
        for (std::size_t i = 0; i != n_rows; ++i) {
            float x = bounds.left + bounds.width * config.offset_left;
            for (std::size_t j = 0; j != n_columns; ++j) {
                cpt::Subplot &sub = figure.get_subplot(i, j);
                sub.set_position(x, y);
                sub.set_size(sx, sy);
                x += sx + bounds.width * config.hspace;
            }
            y += sy + bounds.height * config.vspace;
        }
    }

} // namespace cpt
