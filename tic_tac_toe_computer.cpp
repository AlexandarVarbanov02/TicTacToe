#include "tic_tac_toe_computer.hpp"

#include <iostream>
#include <utility>
#include <array>
#include <chrono>
#include <thread>

void print(std::array<std::array<char, 3>, 3> board) {
    for (auto arr : board) {
        for (auto elem : arr) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "\n";
}

int TicTacToeComputer::evaluate(std::array<std::array<char, 3>, 3> board) {
    for (size_t i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == m_computer) return 100;
            else if(board[i][0] == m_opponent) return -100;
        }

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == m_computer) return 100;
            else if(board[0][i] == m_opponent) return -100;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == m_computer) return 100;
        else if(board[0][0] == m_opponent) return -100;
    }

    if (board[0][2] == board[1][1] && board[2][0] == board[1][1]) {
        if (board[0][2] == m_computer) return 100;
        else if(board[0][2] == m_opponent) return -100;
    }

    return 0;
}

int TicTacToeComputer::minimax(std::array<std::array<char, 3>, 3> board, int depth, int alpha, int beta, bool player) {
    int score = evaluate(board);
    
    if (score == 100 || score == -100) {
        if (score == 100) {
            return score;
        } else {
            return score;
        }
        return score;
    }

    if (m_move_counter + depth + 1 >= 9) {
        return 0;
    }
    int eval;
    int combinations = 0;
    if (player) {
        int max_eval = INT_MIN;

        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = m_computer;
                    eval = minimax(board, depth + 1, alpha, beta, false);
                    max_eval = std::max(max_eval, eval);
                    board[i][j] = ' ';

                    alpha = std::max(eval, alpha);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            if (beta <= alpha) break;
        }
        return max_eval + combinations;
    }
    else {
        int min_eval = INT_MAX;

        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = m_opponent;
                    eval = minimax(board, depth + 1, alpha, beta, true);
                    min_eval = std::min(min_eval, eval);

                    board[i][j] = ' ';

                    beta = std::min(eval, beta);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            if (beta <= alpha) break;
        }
        return min_eval;
    }
}

bool TicTacToeComputer::roll() {
    auto now = std::chrono::system_clock::now();
    
    // Convert to milliseconds since epoch
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    
    //std::cout << "roll is used and resulted in: " << (millis % 2 == 0) << std::endl;
    // Return true if milliseconds is divisible by 2, otherwise false
    return (millis % 2 == 0);
}

std::pair<size_t, size_t> TicTacToeComputer::getBestMove(std::array<std::array<char, 3>, 3> board, int move_counter) {
    m_move_counter = move_counter;
    int max_eval = INT_MIN;
    std::pair<size_t, size_t> best_move = {0, 0};

    if (move_counter == 0) {
        best_move.first = 1;
        best_move.second = 1;
        return best_move;
    }

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = m_computer;
                int move_eval = minimax(board, 0, INT_MIN, INT_MAX, false);
                board[i][j] = ' ';

                if (move_eval == max_eval && roll()) {
                    best_move.first = i;
                    best_move.second = j;
                    max_eval = move_eval;
                }
                
                if (move_eval > max_eval) {
                    best_move.first = i;
                    best_move.second = j;
                    max_eval = move_eval;
                }
            }
        }
    }
    return best_move; 
}
