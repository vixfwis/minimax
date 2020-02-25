#pragma once
#include <iostream>

class Board{
    int *data;
    constexpr static int linesCount = 8;
    constexpr static int lines[linesCount][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6},
    };

public:
    Board(){
        data = new int[9];
        for(int i = 0; i < 9; ++i)
            data[i] = EMPTY;
    }

    Board(const Board& b){
        data = new int[9];
        for(int i = 0; i < 9; ++i)
            data[i] = b.data[i];
    }

    virtual ~Board(){
        delete[] data;
    }

    enum Status{
        PLAYER,
        AI,
        EMPTY,
        UNDEFINED
    };

    int findMove(){
        int best_value = -1;
        bool first = true;
        int best_move = -1;
        for(int i = 0; i < 9; ++i) {
            if (data[i] == EMPTY) {
                int value = maxi(*this, i);
                if (first || value < best_value) {
                    best_value = value;
                    best_move = i;
                    first = false;
                }
            }
        }
        return best_move;
    }

    static int maxi(const Board& b, int index, int depth = 0) {
        Board iter(b);
        if(index != -1) {
            iter.setValue(index, AI);
        }
        if (iter.isGameEnded() != UNDEFINED)
            return iter.evaluate()+depth;
        int max_value = INT32_MIN;
        int best_move = -1;
        for(int i = 0; i < 9; ++i) {
            if (iter.data[i] == EMPTY) {
                int value = mini(iter, i, ++depth);
                if (value > max_value) {
                    max_value = value;
                }
            }
        }
        return max_value;
    }

    static int mini(const Board& b, int index, int depth = 0) {
        Board iter(b);
        if(index != -1) {
            iter.setValue(index, PLAYER);
        }
        if (iter.isGameEnded() != UNDEFINED)
            return iter.evaluate()-depth;
        int min_value = INT32_MAX;
        int best_move = -1;
        for(int i = 0; i < 9; ++i) {
            if (iter.data[i] == EMPTY) {
                int value = maxi(iter, i, ++depth);
                if (value < min_value) {
                    min_value = value;
                }
            }
        }
        return min_value;
    }

    bool contains(int a, int b, int c, Status val1, Status val2 = UNDEFINED, Status val3 = UNDEFINED) const{
        bool out = false;
        int buf[] = {data[a], data[b], data[c]};
        for(int i = 0; i < 3; ++i)
            if(buf[i] == val1) {
                out = true;
                buf[i] = UNDEFINED;
                break;
            }

        if(out && val2 != UNDEFINED) {
            out = false;
            for (int i = 0; i < 3; ++i)
                if (buf[i] == val2) {
                    out = true;
                    buf[i] = UNDEFINED;
                    break;
                }
        }

        if(out && val3 != UNDEFINED) {
            out = false;
            for (int i = 0; i < 3; ++i)
                if (buf[i] == val3) {
                    out = true;
                    buf[i] = UNDEFINED;
                    break;
                }
        }
        return out;
    }

    int isUniform(int a, int b, int c) const{
        int out = UNDEFINED, tmp = data[a];
        if(tmp == data[b] && tmp == data[c])
            if(tmp != EMPTY)
                out = tmp;
        return out;
    }

    int isGameEnded(){
        int out = UNDEFINED;
        for(int i = 0; i < linesCount; ++i){
            out = isUniform(lines[i][0], lines[i][1], lines[i][2]);
            if(out != UNDEFINED)
                return out;
        }
        for(int i = 0; i < 9; ++i)
            if(data[i] == EMPTY)
                return out;
        return EMPTY; // draw
    }

    int evaluate() {
        int score[] = {0, 0};

        for(int i = 0; i < linesCount; ++i)
            if(contains(lines[i][0], lines[i][1], lines[i][2], PLAYER, PLAYER, EMPTY))
                score[0] += 10;
        for(int i = 0; i < linesCount; ++i)
            if(contains(lines[i][0], lines[i][1], lines[i][2], AI, AI, EMPTY))
                score[1] += 10;


        for(int i = 0; i < linesCount; ++i)
            if(PLAYER == isUniform(lines[i][0], lines[i][1], lines[i][2]))
                score[0] += 100;
        for(int i = 0; i < linesCount; ++i)
            if(AI == isUniform(lines[i][0], lines[i][1], lines[i][2]))
                score[1] += 100;

        return score[0] - score[1];
    }

    void setValue(int index, Status value){
        if(index < 9 && index >= 0)
            data[index] = value;
        else
            throw std::runtime_error("setValue: index out of range");
    }

    int getValue(int index){
        if(index < 9 && index >= 0)
            return data[index];
        else
            throw std::runtime_error("getValue: index out of range");
    }

    friend std::ostream& operator<<(std::ostream& os, Board& b) {
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                int val = b.data[i*3+j];
                switch (val){
                    case Board::PLAYER:
                        os << "X" << "\t";
                        break;
                    case Board::AI:
                        os << "O" << "\t";
                        break;
                    default:
                        os << "-" << "\t";
                }
            }
            os << std::endl;
        }
        return os;
    }
};
