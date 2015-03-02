#include <iostream>

#include "rule110.hpp"

int main() {
    /* Evolve initial state of 50 cells for 45 generations */
    constexpr std::array<State<50>, 45> states = evolve<50, 45>(State<50>{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}});

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

