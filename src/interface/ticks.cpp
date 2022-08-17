#include "ticks.hpp"
#include <cmath>

namespace cpt
{
    static std::pair<float, float> calculate_ticks_bounds(
        float xmin,
        float xmax,
        float dx
    )
    {
        const float first = dx * std::ceil(xmin / dx);
        const float last  = dx * std::floor(xmax / dx);
        return {first, last};
    }

    static int calculate_n_ticks(
        float xmin,
        float xmax,
        float dx
    )
    {
        if (dx < std::numeric_limits<float>::min()) {
            return std::numeric_limits<int>::max();
        }
        const auto [first, last] = calculate_ticks_bounds(xmin, xmax, dx);
        return 1 + static_cast<int>(std::round((last - first) / dx)); 
    }

    bool is_better_n_ticks(
        int n, 
        int n_old,
        AutoTicksCongifuration const &config
    )
    {
        auto is_valid = [&config](int n) {
            return n >= config.min_n_ticks && n <= config.max_n_ticks;
        };
        auto is_better = [&config](int n1, int n2) {
            auto diff1 = std::abs(n1 - config.ideal_n_ticks);
            auto diff2 = std::abs(n2 - config.ideal_n_ticks);
            auto comp = diff1 <=> diff2;
            if (comp < 0)      return true;
            else if (comp > 0) return false;
            return n1 > config.ideal_n_ticks && n2 < config.ideal_n_ticks;
        };
        if (!is_valid(n_old)) {
            return true;
        }
        return is_valid(n) && is_better(n, n_old);
    }

    static float calculate_best_dx(
        float xmin,
        float xmax,
        AutoTicksCongifuration const &config
    )
    {
        constexpr static auto next_greater = {2.f, 2.5f, 5.f};
        constexpr static auto next_lower   = {.5f, .25f, .2f};
        const float Dx = xmax - xmin;
        float dx_guess = std::pow(10.f, std::floor(std::log10(Dx)));
        int n_ticks = calculate_n_ticks(xmin, xmax, dx_guess);
        if (n_ticks == config.ideal_n_ticks) {
            return dx_guess;
        }
        auto const &next = (n_ticks < config.ideal_n_ticks ? next_lower : next_greater);
        float previous_guess = dx_guess;
        for (float factor : next) {
            int new_n_ticks = calculate_n_ticks(xmin, xmax, factor*dx_guess);
            if (!is_better_n_ticks(new_n_ticks, n_ticks, config)) {
                return previous_guess;
            }
            n_ticks = new_n_ticks;
            previous_guess = factor * dx_guess;
        }
        throw InvalidTicksConfiguration(
            "Could not calculate ticks between ", xmin, " and ", xmax,
            " for a configuration requiring n_ticks in [", config.min_n_ticks,
            ", ", config.max_n_ticks, "] with an ideal of ", config.ideal_n_ticks
        );
    }

    cpt::Array<float> calculate_ticks(
        float xmin,
        float xmax,
        AutoTicksCongifuration const &config
    )
    {
        if (xmax < xmin) { 
            return calculate_ticks(xmax, xmin, config);
        }   
        float dx = calculate_best_dx(xmin, xmax, config);
        auto [first, last] = calculate_ticks_bounds(xmin, xmax, dx);
        std::size_t n_ticks = static_cast<std::size_t>(
            calculate_n_ticks(xmin, xmax, dx));
        cpt::Array<float> res(n_ticks);
        for (std::size_t i = 0; i != n_ticks; ++i) {
            res[i] = first + dx*static_cast<float>(i);
        }
        return res;
    }

} // namespace cpt
