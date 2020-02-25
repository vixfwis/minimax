#include <iostream>
#include "board.hpp"
using namespace std;

constexpr int numpad[] = {-1,6,7,8,3,4,5,0,1,2};

int main() {
    Board b;
    int pmove, amove;
    int result;
    while(true){

        cout << endl << b << endl;
        cout << "Your turn [numpad]: ";
        while(true){
            cin >> pmove;
            if(b.getValue(numpad[pmove]) != Board::EMPTY){
                cout << "Cell already occupied! Try again: ";
            }else{
                break;
            }
        }
        b.setValue(numpad[pmove], Board::PLAYER);
        if((result = b.isGameEnded()) != Board::UNDEFINED)
            break;

        amove = b.findMove();
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
