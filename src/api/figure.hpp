/*
 * @file figure.hpp
 *
 * @brief Contains the `cpt::Figure` class.
 */
#ifndef CPT_FIGURE_H_INCLUDED
#define CPT_FIGURE_H_INCLUDED

#include "subplot.hpp"
#include "grid_layout.hpp"
#include "../graphics/figure_window.hpp"
#include "../graphics/font_manager.hpp"

namespace cpt
{
    class Session;
    
    /*
     * @brief Main window for a figure, containing one or several subplots.
     *
     * @details This object manages a window and the different subplots 
     * rendered in it (using a default grid layout). Once created (using
     * the `cpt::Session` interface), it is possible to set global 
     * configurations for all subplots and access individual subplots for
     * further processing. For example:
     *
     *     cpt::Session session;
     *     cpt::Figure &figure = session.create_figure(10, 5); // 10x5 inches
     *     figure.create_subplots(1, 2); // 1 row x 2 columns of subplots
     *     // Setting all subplot fonts to arial, italic
     *     figure.set_font(session.get_font(cpt::font::arial, cpt::font::Italic));
     *
     *     cpt::Subplot &left  = figure.get_subplot(0, 0);
     *     cpt::Subplot &right = figure.get_subplot(0, 1);
     *     // Populate the subplots
     *     // ...
     *     figure.show(); // display the window
     *
     * Any configuration specific to a given subplot should be set **after** the
     * global setting (that superseeds any individual setting). As the figure 
     * created by the session, subplots may not be copied and one must use 
     * references when retrieving them from the figure object.
     *
     * @sa The `cpt::Session` and `cpt::Subplot` classes.
     */
    class Figure {

    public:
        Figure( 
            Session    &session,
            std::size_t width, 
            std::size_t height);

        Figure(
            Session         &session,
            std::string_view name, 
            std::size_t      width, 
            std::size_t      height);

        Figure(Figure const &) = delete;
        Figure(Figure &&) = default;

    public:

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

        cpt::Font const &get_font() const;
        void set_font(cpt::Font const &font);

        void show(bool blocking = false);

    private:
        cpt::FigureWindow _window;

        std::size_t _n_rows;
        std::size_t _n_columns;
        std::vector<cpt::Subplot> _subplots;

        cpt::Font const *_font;
    };
} // namespace cpt


#endif
