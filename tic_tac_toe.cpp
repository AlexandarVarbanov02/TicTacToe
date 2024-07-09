#include "tic_tac_toe.hpp"

#include <iostream>
#include <thread>
#include <chrono>

std::string TicTacToe::getMatrix() const {
    std::string line_seperator(SIZE * 4, '-');
    std::string result = "";
    for (size_t i = 0; i < SIZE; ++i) {
        result += "\n" + line_seperator + "\n";
        result += "|";
        for (size_t j = 0; j < SIZE; ++j) {
            result += " ";
            result += m_matrix[i][j];
            result += " |";
        }
    }
    result += "\n" + line_seperator;
    return result;
}

bool TicTacToe::checkWin(size_t x, size_t y) {
    char player_symbol = m_matrix[x][y];
    unsigned int ch_sum = player_symbol * SIZE;
    unsigned int row_sum = 0;
    unsigned int col_sum = 0;
    bool diag_win = (x == y);
    bool reverse_diag_win = (x + y == SIZE - 1);
    // row and column search
    for (size_t i = 0; i < SIZE; ++i) {
        row_sum += m_matrix[x][i];
        col_sum += m_matrix[i][y];

        // checks for diagonal win condition
        if (diag_win && x == y) {
            if (player_symbol != m_matrix[i][i]) {
                diag_win = false;
            }
        }
        // checks for reverse diagonal win condition
        if (reverse_diag_win && x + y == SIZE - 1) {
            if (player_symbol != m_matrix[i][SIZE - 1 - i]) {
                reverse_diag_win = false;
            }
        }
    }
    // implement diagonal search(can be implemented in seperate loops aswell don't know what is better/faster)
    return col_sum == ch_sum || row_sum == ch_sum || diag_win || reverse_diag_win;
}

bool TicTacToe::validateMove(size_t x, size_t y) {
    if (x >= 0 && y >= 0 && x < 3 && y < 3) {
        return m_matrix[x][y] == ' ';
    }
    return false;
}

int TicTacToe::makeMove(size_t x, size_t y) {
    if (m_move_counter < (SIZE * SIZE) && validateMove(x, y)) {
        m_move_counter++;
        m_matrix[x][y] = m_symbols[(++m_player) % 2];
        if (m_move_counter == 9) {
            m_player = -1;
            return 1;
        }
        return checkWin(x, y);
    }
    return -1;
}

void TicTacToe::run() {
    size_t x,y;
    int flag = 0;
    int counter = 0;
    std::cout << getMatrix() << std::endl;
    while (flag != 1) {
        if (counter % 2 == 1) {
            std::pair<size_t, size_t> move = cp_two.getBestMove(m_matrix, m_move_counter);
            x = move.first;
            y = move.second; 
        }
        else {
            std::pair<size_t, size_t> move = cp_one.getBestMove(m_matrix, m_move_counter);
            x = move.first;
            y = move.second;   
        }
        counter++;
        flag = makeMove(x, y);
        std::cout << m_move_counter << std::endl;
        std::cout << getMatrix() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    if (m_player == -1) {
        std::cout << "\nGame has ended with no winner.\n";
    }
    else {
        std::cout << "\nPlayer " << ((m_player + 1) % 2) + 1 << " has won the game!\n";
    }
}

void TicTacToe::reset() {
    m_matrix = {{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}};
    m_move_counter = 0;
    m_player = 2;
}



