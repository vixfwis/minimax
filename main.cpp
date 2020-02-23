#include <iostream>
#include "board.hpp"
using namespace std;

int main() {
    Board b;
    int pmove, amove;
    int result;
    while(true){

        cout << endl << b << endl;
        cout << "Your turn [1-9]: ";
        while(true){
            cin >> pmove;
            if(b.getValue(pmove-1) != Board::EMPTY){
                cout << "Cell already occupied! Try again: ";
            }else{
                break;
            }
        }
        b.setValue(pmove-1, Board::PLAYER);
        if((result = b.isGameEnded()) != Board::UNDEFINED)
            break;

        amove = -1;
        Board::mini(b, amove);
        if(amove != -1)
            b.setValue(amove, Board::AI);
        if((result = b.isGameEnded()) != Board::UNDEFINED)
            break;
    }
    cout << endl << b << endl;
    switch (result){
        case Board::PLAYER:
            cout << "Player wins!" << endl;
            break;
        case Board::AI:
            cout << "AI wins!" << endl;
            break;
        default:
            cout << "Draw!" << endl;
    }
    return 0;
}
