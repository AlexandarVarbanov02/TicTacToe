#ifndef TIC_TAC_TOE_COMPUTER_HPP_
#define TIC_TAC_TOE_COMPUTER_HPP_

#include <utility>
#include <string>
#include <array>


class TicTacToeComputer {
private:
    int m_move_counter;
    char m_computer;
    char m_opponent;

    int minimax(std::array<std::array<char, 3>, 3> board, int depth, int alpha, int beta, bool player);
    int evaluate(std::array<std::array<char, 3>, 3> board);
    bool roll();

public:
    TicTacToeComputer(char comp, char opp) : m_computer(comp), m_opponent(opp) {};
    std::pair<size_t, size_t> getBestMove(std::array<std::array<char, 3>, 3> board, int move_counter);
};


#endif