#ifndef CPT_FIGURE_H_INCLUDED
#define CPT_FIGURE_H_INCLUDED

#include "subplot.hpp"
#include "window.hpp"

namespace cpt
{
    class Figure: public Window {
    public:
        Figure( 
            std::size_t width, 
            std::size_t height);

        Figure(
            std::string_view name, 
            std::size_t width, 
            std::size_t height);

        void create_subplots(std::size_t n_rows, std::size_t n_columns);

        Subplot &get_subplot(std::size_t i_row, std::size_t i_col);
        Subplot const &get_subplot(std::size_t i_row, std::size_t i_col) const;

        Subplot &get_subplot();
        Subplot const &get_subplot() const;

    private:

        std::size_t _n_rows;
        std::size_t _n_columns;
        std::vector<cpt::Subplot> _subplots;

    private:
        static inline unsigned int n_figures = 0;
    };
} // namespace cpt


#endif