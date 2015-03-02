#include <array>

/* Index sequence */

template <unsigned int... Sequence>
struct sequence { };

template <unsigned int N, unsigned int... Rest>
struct make_sequence : make_sequence<N-1, N-1, Rest...> { };

template <unsigned int... Rest>
struct make_sequence<0, Rest...> : sequence<Rest...> { };

/* State data structure */

template <unsigned int N>
using State = std::array<bool, N>;

/* Cell evolution */

constexpr bool evolveCell(bool left, bool center, bool right) {
    return static_cast<bool>((110 >> ((left << 2) | (center << 1) | (right << 0))) & 0x1);
}

/* State evolution */

template <unsigned int N>
constexpr bool evolveCell(unsigned int index, const State<N> &state) {
    return evolveCell(state[(index-1) % N], state[index], state[(index+1) % N]);
}

template <unsigned int N, unsigned int... Indices>
constexpr State<N> _evolveState(sequence<Indices...> seq, const State<N> &state) {
    return {{evolveCell<N>(Indices, state)...}};
}

template <unsigned int N>
constexpr State<N> evolveState(const State<N> &state) {
    return _evolveState<N>(make_sequence<N>(), state);
}

/* State evolution for a specified number of generations */

template <unsigned int N>
constexpr State<N> _iterateEvolveState(sequence<> seq, const State<N> &initialState) {
    return initialState;
}

template <unsigned int N, unsigned int Generation, unsigned int... Rest>
constexpr State<N> _iterateEvolveState(sequence<Generation, Rest...> seq, const State<N> &initialState) {
    return evolveState<N>(_iterateEvolveState<N, Rest...>(sequence<Rest...>(), initialState));
}

template <unsigned int N, unsigned int Generations>
constexpr State<N> iterateEvolveState(const State<N> &initialState) {
    return _iterateEvolveState<N>(make_sequence<Generations>(), initialState);
}

/* State evolutions, recorded across a specified number of generations */

template <unsigned int N, unsigned int... Generations>
constexpr std::array<State<N>, sizeof...(Generations)> _evolve(sequence<Generations...> seq, const State<N> &initialState) {
    return {{iterateEvolveState<N, Generations>(initialState)...}};
}

template <unsigned int N, unsigned int Generations>
constexpr std::array<State<N>, Generations> evolve(const State<N> &initialState) {
    return _evolve<N>(make_sequence<Generations>(), initialState);
}

