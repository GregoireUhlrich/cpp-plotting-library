#include "plotter/figure.hpp"
#include <iostream>

int main()
{
    cpt::Figure fig1(5, 5);
    cpt::Figure fign("My Fig", 10, 5);
    cpt::Figure fig2(5, 5);
    fign.set_blocking(true);

    fig1.show();
    std::cout << "Figure 1 and My Fig should be there but that's all" << std::endl; 
    fign.show();

    std::cout << "Here you should hae already close My Fig" << std::endl;
    fig2.show();

    std::cout << "End of program" << std::endl;

    return 0;
}