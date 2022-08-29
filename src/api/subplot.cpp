#include "subplot.hpp"

namespace cpt {

    void Subplot::plot_line(
        ScienceDataArray<float> x,
        ScienceDataArray<float> y,
        LinePlotConfig   const &config
    )
    {
        _plots.push_back(std::make_shared<LinePlot>(
            std::move(x),
            std::move(y),
            config
        ));
    }

    Extent<float> Subplot::get_extent()
    {
        if (_user_extent) {
            return _extent;
        }
        compute_extent();
        return _extent;
    }

    void Subplot::set_extent(Extent<float> extent) noexcept
    {
        _extent = std::move(extent);
        _user_extent = true;
    }

    template<std::floating_point T>
    static void ensure_non_zero_extent(T &min, T &max) noexcept {
        if (max - min < std::numeric_limits<T>::min()) {
            min -= static_cast<T>(1.);
            max += static_cast<T>(1.);
        }
    }

    void Subplot::compute_extent() 
    {
        if (_plots.empty()) {
            _extent = {-1.f, 1.f, -1.f, 1.f};
            return;
        }
        auto iter = _plots.begin();
        _extent = (**iter).get_extent();
        while (++iter != _plots.end()) {
            _extent = combine(_extent, (**iter).get_extent());
        }
        ensure_non_zero_extent(_extent.xmin, _extent.xmax);
        ensure_non_zero_extent(_extent.ymin, _extent.ymax);
        auto dx = _extent.xmax - _extent.xmin;
        auto dy = _extent.ymax - _extent.ymin;
        _extent.xmin -= 0.1f * dx;
        _extent.xmax += 0.1f * dx;
        _extent.ymin -= 0.1f * dy;
        _extent.ymax += 0.1f * dy;
    }

    void Subplot::set_font(sf::Font const &font)
    {
        for (auto &ax : axis) {
            ax.set_font(font);
        }
    }

    void Subplot::display()
    {
        _canvas.clear();
        _canvas.set_extent(get_extent());
        for (const auto &plot : _plots) {
            plot->draw_plot(_canvas);
        }
        _canvas.display();
    }

} // namespace cpt
