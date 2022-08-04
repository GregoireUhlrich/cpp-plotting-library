#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "axis.hpp"
#include "drawable.hpp"
#include "pad.hpp"
#include "plotline.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <array>

namespace cpt {

class SubPlot : public Drawable {
  private:
    Pad                 pad;
    std::array<Axis, 2> axis;
    std::vector<PlotLine> lines;

    void init() override;

  public:
    SubPlot();
    SubPlot(Pad &pad);
    virtual ~SubPlot();

    template<class T, class U>
    void plot(LineData<T, U> const &data) {
        lines.push_back(PlotLine{data});
    }

    void draw(sf::RenderTarget &target) override;
};

void SubPlot::init()
{
    for (size_t d = 0; d != axis.size(); ++d) {
        axis[d] = Axis(Coordinate(d));
    }
}

SubPlot::SubPlot()
{
    init();
}

SubPlot::SubPlot(Pad &pad) : pad(pad)
{
    init();
}

SubPlot::~SubPlot()
{
}

void SubPlot::draw(sf::RenderTarget &target)
{
    pad.draw(target);
    for (Axis &a : axis) {
        a.draw(target);
    }
    for (const auto &plot : lines) {
        plot.draw(target);
    }
}

} // namespace cpt

#endif // CIRCLE_HPP
