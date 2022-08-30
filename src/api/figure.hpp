#ifndef CPT_FIGURE_H_INCLUDED
#define CPT_FIGURE_H_INCLUDED

#include "subplot.hpp"
#include "grid_layout.hpp"
#include "../graphics/figure_window.hpp"
#include "../graphics/font_manager.hpp"

namespace cpt
{
    class Figure {

    public:
        Figure( 
            std::size_t width, 
            std::size_t height);

        Figure(
            std::string_view name, 
            std::size_t width, 
            std::size_t height);

        Figure(Figure const &) = delete;
        Figure(Figure &&) = default;

        ~Figure();

        void create_subplots(
            std::size_t n_rows, 
            std::size_t n_columns,
            cpt::GridLayoutConfig const &config = {});

        std::size_t get_n_rows() const noexcept { return _n_rows; }
        std::size_t get_n_columns() const noexcept { return _n_columns; }

        Subplot &get_subplot(std::size_t i_row, std::size_t i_col);
        Subplot const &get_subplot(std::size_t i_row, std::size_t i_col) const;

        Subplot &get_subplot();
        Subplot const &get_subplot() const;

        std::vector<Subplot> &get_subplots() noexcept;
        std::vector<Subplot> const &get_subplots() const noexcept;

        void set_font(sf::Font const &font);

        void show(bool blocking = false);

    private:
        cpt::FigureWindow _window;

        std::size_t _n_rows;
        std::size_t _n_columns;
        std::vector<cpt::Subplot> _subplots;

    private:
        static inline unsigned int n_figures = 0;
    };
} // namespace cpt


#endif
