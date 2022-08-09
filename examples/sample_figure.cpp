#include "plotter/figure.hpp"
#include <iostream>

int main()
{
    cpt::Figure fig1(5, 5);
    cpt::Figure fign("My Fig", 10, 5);
    cpt::Figure fig2(5, 5);
    fign.create_subplots(2, 2);
    for (std::size_t i = 0; i != fign.get_n_rows(); ++i) {
        for (std::size_t j = 0; j != fign.get_n_columns(); ++j) {
            cpt::Subplot &sub = fign.get_subplot(i, j);
            auto pos  = sub.get_position();
            auto size = sub.get_size();
            std::cout << "Subplot (" << i << ", " << j << "):\n";
            std::cout << "  -> pos  = (" << pos.x << ", " << pos.y << ")\n";
            std::cout << "  -> size = (" << size.x << ", " << size.y << ")\n";
        }
    }

    fig1.show();
    std::cout << "Figure 1 and My Fig should be there but that's all" << std::endl; 
    fign.show(true);

    std::cout << "Here you should hae already close My Fig" << std::endl;
    fig2.show();

    std::cout << "End of program" << std::endl;

    return 0;
}