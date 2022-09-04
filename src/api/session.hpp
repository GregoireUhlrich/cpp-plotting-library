/*!
 * @file session.hpp
 *
 * @brief Contains the `cpt::Session` class.
 */
#ifndef CPT_SESSION_H_INCLUDED
#define CPT_SESSION_H_INCLUDED

#include <map>
#include <concepts>
#include "figure.hpp"
#include "../graphics/font_manager.hpp"

/*!
 * @brief Contains all objects and functions of the 
 * C++ Plotting Library.
 */
namespace cpt
{
    /*!
     * @brief Session managing several `cpt::Figure` objects
     * and their common properties.
     *
     * @details A `cpt::Figure` should be created through the 
     * `Session::create_figure()` method and not directly. This 
     * allows the figures to be properly initialized using common
     * configuration (e.g. the default font).
     *
     * The `Session` class manages font objects. Each time a new font
     * is required, it is created inside the session class and all 
     * underlying graphical objects should refer to (through a pointer)
     * the `cpt::Font` object stored by the session. 
     *
     * The main use case for the session in the following:
     *
     *     cpt::Session session; // default constructed
     *     cpt::Figure &fig = session.create_figure(10, 5); // size 10x5
     * 
     * Do not forget the reference for the figure otherwise 
     * a compile-time error will be raised ! 
     *
     * @sa The `cpt::Figure` class and its constructors.
     */
    class Session {
    
    public:

        /*!
         * @brief Default and unique constructor.
         */
        Session();

        /*!
         * @brief Return the current font common to all figures.
         *
         * @details While the figures can be set individually, this
         * parameter determines the default font figures are created
         * with.
         *
         * @return A const reference to the default figure font.
         */
        cpt::Font const &get_main_font() const;

        /*!
         * @brief Return a reference to the font object corresponding
         * to a given family and class.
         *
         * @details The reference is guaranteed to refer to a valid 
         * `cpt::Font` object during the entire `Session` lifetime.
         *
         * @param family Font family 
         * @param class_ Class of the font (regular, bold, italic etc)
         *
         * @return A const reference to the corresponding `cpt::Font` object.
         */
        cpt::Font const &get_font(
            cpt::font::FontFamily const &family,
            cpt::font::Class             class_ = cpt::font::Regular
            );

        /*!
         * @brief Set the default font of the session.
         *
         * @details All subsequent figures will be created using this font.
         * Already created figures will keep the same font as before.
         *
         * @param family Font family 
         * @param class_ Class of the font (regular, bold, italic etc)
         */
        void set_main_font(
            cpt::font::FontFamily const &family,
            cpt::font::Class             class_ = cpt::font::Regular
            );

        /*!
         * @return The current number of figures in the session.
         */
        size_t get_n_figures() const noexcept {
            return _n_figures;
        }

        /*!
         * @brief Return a reference to the ith `cpt::Figure`.
         *
         * @details `i` should be in `[0, n_figures[`.
         *
         * @param i Position of the figure to retrieve.
         *
         * @return A reference to the `cpt::Figure` at position `i`.
         */
        Figure &get_figure(size_t i);

        /*!
         * @brief Return a const reference to the ith `cpt::Figure`.
         *
         * @details `i` should be in [0, n_figures[.
         *
         * @param i Position of the figure to retrieve.
         *
         * @return A const reference to the `cpt::Figure` at position `i`.
         */
        Figure const &get_figure(size_t i) const;

        /*!
         * @brief Create a new figure and return a reference to it.
         *
         * @details This template function may be called with any set of 
         * parameters that can be directly forwarded to one `cpt::Figure`
         * constructor. The new figure is created with the given parameters,
         * initialized by the session, and a reference is returned for 
         * further processing by the calling function.
         *
         * @tparam ...FigArgs Variadic template parameters
         * @param ...args Variadic parameters forwarded to the `cpt::Figure`
         * constructor.
         *
         * @return A reference to the newly created `cpt::Figure` object.
         */
        template<class ...FigArgs>
            requires std::constructible_from<cpt::Figure, cpt::Session&, FigArgs...>
        Figure &create_figure(FigArgs &&...args)
        {
            auto insertion_result = _figures.try_emplace(
                _n_figures++, 
                *this,
                std::forward<FigArgs>(args)...);
            cpt::Figure &fig = (insertion_result.first)->second;
            return fig;
        }

    private:

        FontManager               _font_manager;
        cpt::Font                *_main_font;
        std::map<size_t, Figure>  _figures;
        size_t                    _n_figures;
    };
} // namespace cpt

#endif // 
