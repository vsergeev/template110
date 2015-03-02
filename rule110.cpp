#include <iostream>

#include "rule110.hpp"

int main() {
    /* Evolve initial state of 25 cells for 30 generations */
    constexpr std::array<State<25>, 30> states = evolve<25, 30>(State<25>{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}});

    /* Print out the state from each generation */
    for (const auto &state : states) {
        for (const auto &elem : state) {
            if (elem)
                std::cout << "*";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

