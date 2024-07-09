#ifndef TIC_TAC_TOE_HPP_
#define TIC_TAC_TOE_HPP_

#define SIZE 3

#include <array>
#include <string>

#include "tic_tac_toe_compter.hpp"

class TicTacToe {
private:
    TicTacToeComputer cp_one = TicTacToeComputer('O', 'X');
    TicTacToeComputer cp_two = TicTacToeComputer('X', 'O');
    std::array<std::array<char, 3>, 3> m_matrix = {{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}};
    std::array<char, 2> m_symbols = {'X', 'O'};
    size_t m_player = 0;
    bool m_first = 0;
    size_t m_move_counter = 0;

    bool checkWin(size_t x, size_t y);
    bool validateMove(size_t x, size_t y);

public:
    int makeMove(size_t x, size_t y);
    std::string getMatrix() const;
    void reset();

    void run();
};


#endif