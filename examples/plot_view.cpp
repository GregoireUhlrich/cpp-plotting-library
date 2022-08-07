#include <SFML/Graphics.hpp>

#include "math_views.hpp"

auto create_texture(sf::RenderTexture &texture, float width, float height)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = sf::RenderTexture::getMaximumAntialiasingLevel();
    texture.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height), settings);
}

class ArrayMismatchError: public cpt::Exception {
    using cpt::Exception::Exception;
};

struct MinMax {
    float min;
    float max;
};

MinMax get_min_max(cpt::Array<float> const &x)
{
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::min();
    for (float xi : x) {
        if (xi > max) max = xi;
        if (xi < min) min = xi;
    }
    return MinMax{.min = min, .max = max};
}

void plot(
    sf::RenderTarget     &target, 
    cpt::View auto const &xview, 
    cpt::View auto const &yview,
    const float           offset_ratio = 0.1f,
    const float           marker_size = 3.5f
    )
{
    if (std::ranges::size(xview) != std::ranges::size(yview)) {
        throw ArrayMismatchError(
            "Sizes for x and y must be equal for plot, found ",
            std::ranges::size(xview), " and ",
            std::ranges::size(yview), "..."
        );
    }
    const cpt::Array<float> x = cpt::collect<float>(xview);
    const cpt::Array<float> y = cpt::collect<float>(yview);
    const sf::Vector2f target_size = {
        static_cast<float>(target.getSize().x), 
        static_cast<float>(target.getSize().y)
    };
    const auto x_min_max = get_min_max(x);
    const auto y_min_max = get_min_max(y);
    const float lx = x_min_max.max - x_min_max.min;
    const float ly = y_min_max.max - y_min_max.min;
    const float offset_x = target_size.x * offset_ratio;
    const float offset_y = target_size.y * offset_ratio;
    const float x_aspect_ratio = (lx == 0.f) ? 1.f : std::abs((1 - 2*offset_ratio)*target_size.x / lx);
    const float y_aspect_ratio = (ly == 0.f) ? 1.f : std::abs((1 - 2*offset_ratio)*target_size.y / ly);

    for (std::size_t i = 0; i != x.size(); ++i) {
        sf::CircleShape circle(marker_size);
        circle.setFillColor(sf::Color(0, 64, 128));
        const float xi = ((x[i] - x_min_max.min) * x_aspect_ratio) + offset_x;
        const float yi = ((y[i] - y_min_max.min) * y_aspect_ratio) + offset_y;
        circle.setPosition(xi - marker_size/2.f, target_size.y - (yi - marker_size/2.f));
        target.draw(circle);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "i3Float");

    float ratio = 0.9f;
    sf::Vector2f windowSize = {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)};
    sf::RenderTexture texture;
    create_texture(
        texture, 
        ratio*windowSize.x, ratio*windowSize.y
    );
    sf::Sprite sprite;
    sprite.setTexture(texture.getTexture());
    sprite.setPosition(sf::Vector2f((1.f - ratio)*windowSize.x / 2.f, (1.f - ratio)*windowSize.y / 2.f));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        texture.clear(sf::Color(186, 186, 186));
        const auto x = cpt::linspace(0, 10, 100);
        plot(texture, x, cpt::sin(x) + x*x/50 - cpt::exp(-x));
        texture.display();

        window.draw(sprite);
        window.display();
    }

    return 0;
}
