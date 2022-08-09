#ifndef CPT_SUBPLOT_H_INCLUDED
#define CPT_SUBPLOT_H_INCLUDED

namespace cpt
{
    class Subplot {
    public:
        Subplot() = default;
        Subplot(Subplot const &) = delete;
        Subplot(Subplot &&) noexcept = default;
    };
} // namespace cpt

#endif