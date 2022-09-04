/*!
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
    
    /*!
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
        /*!
         * @brief Constructs a figure with a given window size.
         *
         * @details The figure name is determined automatically following a 
         * convention of the type "Figure <i>" with "<i>" the figure number
         * in the current session.
         *
         * @param session  Session used to initialize the figure configuration.
         * @param width    Width (in inch = 96pix) of the window
         * @param heigth   Height (in inch = 96pix) of the window
         */
        Figure( 
            Session    &session,
            std::size_t width, 
            std::size_t height);

        /*!
         * @brief Constructs a figure with a given name and window size.
         *
         * @param session  Session used to initialize the figure configuration.
         * @param name     Figure name (name of the window in particular).
         * @param width    Width (in inch = 96pix) of the window
         * @param heigth   Height (in inch = 96pix) of the window
         */
        Figure(
            Session         &session,
            std::string_view name, 
            std::size_t      width, 
            std::size_t      height);

        /*!
         * @brief Deleted copy constructor.
         */
        Figure(Figure const &) = delete;

        /*!
         * @brief Defaulted move constructor.
         */
        Figure(Figure &&) = default;

    public:

        /*!
         * @brief Destructor.
         *
         * @details The destructor waits for the figure the be closed when 
         * the show() is non-blocking to prevent undefined behavior.
         */
        ~Figure();

        /*!
         * @brief Create the subplot grid for the figure.
         *
         * @details This function should be called only once to define 
         * the subplot grid (from a number of rows and columns). To create
         * a 2x2 grid of subplots for example:
         *
         *     figure.create_subplots(2, 2);
         *     cpt::Subplot &top_left     = figure.get_subplot(0, 0); 
         *     cpt::Subplot &top_right    = figure.get_subplot(0, 1); 
         *     cpt::Subplot &bottom_left  = figure.get_subplot(1, 0); 
         *     cpt::Subplot &bottom_right = figure.get_subplot(1, 1); 
         *
         * While for a unique plot in the figure there is no need to call 
         * `Figure::create_subplots()` or to give indices to `get_subplot()`:
         *
         *     cpt::Subplot &plot = figure.get_subplot();
         *
         * The reference should always be used as `cpt::Subplot` objects cannot 
         * be copied.
         */
        void create_subplots(
            std::size_t n_rows, 
            std::size_t n_columns,
            cpt::GridLayoutConfig const &config = {});

        /*!
         * @return The number of subplot rows.
         */
        std::size_t get_n_rows() const noexcept { return _n_rows; }
        /*!
         * @return The number of subplot columns.
         */
        std::size_t get_n_columns() const noexcept { return _n_columns; }

        /*!
         * @brief Return the subplot at a given position in the grid.
         *
         * @details `i_row` should be in `[0, n_rows[` and similarly 
         * `i_col` in `[0, n_cols[`.
         *
         * @param i_row Row index of the subplot to return.
         * @param i_col Column index of the subplot to return.
         *
         * @return A reference to the subplot in position `[i_row, i_col]`.
         */
        Subplot &get_subplot(std::size_t i_row, std::size_t i_col);
        /*!
         * @brief Return the subplot at a given position in the grid.
         *
         * @details `i_row` should be in `[0, n_rows[` and similarly 
         * `i_col` in `[0, n_cols[`.
         *
         * @param i_row Row index of the subplot to return.
         * @param i_col Column index of the subplot to return.
         *
         * @return A const reference to the subplot in position `[i_row, i_col]`.
         */
        Subplot const &get_subplot(std::size_t i_row, std::size_t i_col) const;

        /*!
         * @brief Return the unique subplot of the figure.
         *
         * @details If this function is called for a figure with more than
         * one subplot, an error will be raised.
         *
         * @return A reference to the unique subplot.
         */
        Subplot &get_subplot();
        /*!
         * @brief Return the unique subplot of the figure.
         *
         * @details If this function is called for a figure with more than
         * one subplot, an error will be raised.
         *
         * @return A const reference to the unique subplot.
         */
        Subplot const &get_subplot() const;

        /*!
         * @brief Return all the figure subplots.
         *
         * @details The index of a subplot in the vector is 
         * `i_row*n_columns + i_col`, i.e. the two following lines are
         * equivalent:
         *     
         *     cpt::Subplot &plot1 = figure.get_subplot(1, 2);
         *     cpt::Subplot &plot2 = figure.get_subplots()[1*figure.get_n_columns() + 2];
         *     assert(&plot1 == &plot2);
         *
         * To store the vector in a variable it is necessary to use a reference as the
         * `cpt::Subplot` objects are not copyable.
         *
         * @return A reference to the vector of subplots.
         */
        std::vector<Subplot> &get_subplots() noexcept;
        /*!
         * @brief Return all the figure subplots.
         *
         * @details The index of a subplot in the vector is 
         * `i_row*n_columns + i_col`, i.e. the two following lines are
         * equivalent:
         *     
         *     cpt::Subplot const &plot1 = figure.get_subplot(1, 2);
         *     cpt::Subplot const &plot2 = figure.get_subplots()[1*figure.get_n_columns() + 2];
         *     assert(&plot1 == &plot2);
         *
         * To store the vector in a variable it is necessary to use a reference as the
         * `cpt::Subplot` objects are not copyable.
         *
         * @return A const reference to the vector of subplots.
         */
        std::vector<Subplot> const &get_subplots() const noexcept;

        /*!
         * @brief Return the current default font of the figure.
         */
        cpt::Font const &get_font() const;
        /*!
         * @brief Set the default figure font. 
         *
         * @details All sub-objects (subplots, axis etc) are affected
         * by this configuration change. Any specific change for a part
         * of a figure should be done **after** setting the figure's font.
         *
         * @param font New default font for the figure.
         */
        void set_font(cpt::Font const &font);

        /*!
         * @brief Display the window with the plots.
         *
         * @details This function displays a window and can be blocking
         * or non-blocking. Blocking means the thread execution will stop 
         * at the `show()` call and restart only after the window has been
         * **closed**. 
         *
         * When the figure is non-blocking (default), the window is created 
         * in a separate thread and the execution continues immediately after
         * the `show()`. However, the execution will still be blocked at the 
         * figure destruction that will wait the window to be closed. Example:
         *
         *     int main()
         *     {
         *        cpt::Session session;
         *        { // blocking case
         *           cpt::Figure &fig = session.create_figure();
         *           fig.show(true); // set-blocking
         *           // Does not show before the window is closed
         *           std::cout << "Hello World!\n"; 
         *        }
         *        {
         *           cpt::Figure &fig = session.create_figure();
         *           fig.show(false); // non-blocking (default)
         *           // "Hello World!" displayed immediately
         *           std::cout << "Hello World!\n";
         *           // Execution does not block here as fig is just a reference
         *        }
         *        // Here the execution waits for the figure to close 
         *        // before destroying the session (and the underlying figures)
         *     }
         *
         * The figure destruction will happen when the session is destroyed. 
         * This means when the session object goes out of scope, all the figure
         * session (even the non-blocking ones) must be closed before 
         * continuing the thread execution.
         *
         * @param blocking Tell if the execution must block at the `show()` call 
         * (default is false, execution continues independently of the figure).
         */
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
