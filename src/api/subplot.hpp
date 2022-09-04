/*!
 * @file subplot.hpp
 *
 * @brief Contains the `cpt::Subplot` class.
 */
#ifndef CPT_SUBPLOT_H_INCLUDED
#define CPT_SUBPLOT_H_INCLUDED

#include "../graphics/plot_canvas.hpp"
#include "../graphics/subplot_texture.hpp"
#include "../plots/histogram.hpp"
#include "../plots/line_plot.hpp"
#include "../utils/plot_data.hpp"
#include <map>
#include <vector>

namespace cpt {

/*!
 * @brief Main interface to define plots.
 *
 * @details One `cpt::Figure` (one window) can display one or multiple
 * subplots. Each subplot has plot canvas with axis and labels. The 
 * `cpt::Subplot` class provides the necessary interface to define 
 * and customize plots that are later displayed on the figure window.
 *
 * Plots take as input data `cpt::ScienceDataArray` objects. They can
 * be constructed from a single collection or include a symmetric or 
 * two-sided error (x, x+-xerr or x+xerrp-xerrm).
 *
 * @sa The `cpt::ScienceDataArray` class.
 */
class Subplot : public SubplotTexture {

  public:

    /*!
     * @brief Default constructor.
     */
    Subplot();

    /*!
     * @brief Deleted copy constructor.
     */
    Subplot(Subplot const &) = delete;

    /*!
     * @brief Plots a function line using an array `y` function of `x`.
     *
     * @param x Data for x and its uncertainties (optional)
     * @param y Data for y and its uncertainties (optional)
     * @param config Configuration of the plot 
     *
     * @sa The `cpt::LinePlotConfig` class for configuration.
     */
    void plot_line(ScienceDataArray<float> x,
                   ScienceDataArray<float> y,
                   LinePlotConfig const   &config = {});

    void histogram(ScienceDataArray<float> x,
                   ScienceDataArray<float> y,
                   HistogramConfig const  &config = {});

    /*!
     * @brief Tells if the subplot extent is automatic or user-defined.
     *
     * @details The extent corresponds to the axis limits along x and y.
     *
     * @return \b True  If the extent is automatic.
     * @return \b False Otherwise.
     */
    bool has_auto_extent() const noexcept
    {
        return !_user_extent;
    }

    /*!
     * @brief Set the extent automatic.
     *
     * @details When the extent is set calling the function 
     * `Subplot::set_extent()`, the object considers the extent as
     * user-defined and will not readapt it for any reason. To 
     * allow the `Subplot` object to adapt the extent to the 
     * different plots, this function can be called.
     *
     * @note There is no boolean parameter to set a non-automatic 
     * extent as this can only be done defining the extent. This 
     * is therefore done by the `Subplot::set_extent()` function.
     */
    void set_auto_extent() noexcept
    {
        _user_extent = false;
    }

    /*!
     * @brief Return the subplots extent.
     *
     * @details If the extent is not user-defined, it is calculated
     * before being returned. The extent of several plots corresponds 
     * for each bound (top, left, right and bottom) to the maximum 
     * of this bound among the different plots.
     *
     * @return The extent for the subplot.
     */
    Extent<float> get_extent();

    /*!
     * @brief Set the extent explicitely.
     *
     * @details Once the extent on the x and y axis have been user-defined
     * through this function, it will stay fixed. When in need of making 
     * the extent automatic again, it is possible to call 
     * `Subplot::set_auto_extent()`.
     *
     * @param extent User-defined extent.
     */
    void set_extent(Extent<float> extent) noexcept;

    /*!
     * @brief Displays the subplot on a `sf::RenderTexture`. 
     *
     * @details Once displayed, the sprite can be used to draw on
     * the window and the individual plots no longer need to be 
     * calculated or drawn again.
     *
     * @sa The `cpt::SubplotTexture` class.
     */
    void display();

  private:
    void compute_extent();
    void setup_default_axis(cpt::Extent<float> const &extent);

  private:
    bool                                        _user_extent = false;
    Extent<float>                               _extent;
    std::vector<std::shared_ptr<cpt::PlotData>> _plots;
};
} // namespace cpt

#endif
