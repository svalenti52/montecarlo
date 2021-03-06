/**
 * \file State.h
 * \date 8-Jul-2017
 *
 * \brief Represents a single state, with transition vector and uniform
 * integer distribution across the transition vector.
 *
 * \details state_ID can be any integral value but should ideally be
 * identified with the position within the StateMatrix vector. The
 * transitions within the vector below MUST BE ALIGNED with the
 * state's position in the StateMatrix's state vector. Note that i_min
 * should be zero and that i_max should be be one less than the length
 * of the transitions vector. Use case is DuellingIdiots/blind_spider_MCS.
 */

#ifndef MONTECARLO_STATE_H
#define MONTECARLO_STATE_H

#include <vector>
#include <random>

class State {
public:
    int state_ID;
    std::vector<int> transitions; ///> Aligned with vector position in StateMatrix.
    std::uniform_int_distribution<int> uid; ///> Based on length of transitions.

    State(int _state_ID,
            const std::vector<int>& _transitions)
            : state_ID(_state_ID), transitions(_transitions),
              uid(0, static_cast<int>(_transitions.size()-1)) {}

    int get_next_state(std::default_random_engine& dre) {
        return transitions[uid(dre)];
    }

    friend std::ostream& operator << (std::ostream& o, State& s);
};

std::ostream& operator << (std::ostream& o, State& s) {

    o << s.state_ID << " - ";
    for ( int tx_id : s.transitions )
        o << tx_id << " ";
    o << '\n';
    return o;
}

#endif //MONTECARLO_STATE_H
