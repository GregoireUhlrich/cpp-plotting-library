#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "axis.hpp"
#include "pad.hpp"
#include "plotline.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <array>

namespace cpt {

class SubPlot : public sf::Drawable {
  private:
    Pad                   pad;
    std::array<Axis, 2>   axis;
    std::vector<PlotLine> lines;

    void init();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  public:
    SubPlot();
    SubPlot(Pad &pad);
    virtual ~SubPlot();

    template <class T, class U>
    void plot(LineData<T, U> const &data)
    {
        lines.push_back(PlotLine{data});
    }
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

void SubPlot::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(pad, states);
    for (const Axis &a : axis) {
        target.draw(a, states);
    }

    for (const auto &plot : lines) {
        plot.draw(target, states);
    }
}

} // namespace cpt

#endif // CIRCLE_HPP
