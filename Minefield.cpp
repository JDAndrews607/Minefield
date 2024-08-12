//
//  main.cpp
//  Minesweeper
//
//  Created by Jeremy Andrews on 7/16/24.
//

#include <iostream> //basic input/output
#include <cstdlib>  //for rand() function

using namespace std;

//Classes

class Board {
    public:

    /*
    Initializer function for the player's game board and answer board
    will first set all slots in both boards to '_'
    Will then randomly place mines ('*') on the board
    */
    Board(int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                gameBoard[i][j] = '_';
                answerBoard[i][j] = '_';
            }
        }
        
        float mineProp = 0.2 * size * size;     //gives number of mines to be placed
        for (int i = 0; i <= mineProp; i++) {   //loop to set position of mines
            srand((unsigned) time(NULL));
            int pos1 = rand()%size;
            int pos2 = rand()%size;
            if (answerBoard[pos1][pos2] != '*') {
                answerBoard[pos1][pos2] = '*';
            }
            else {  //to offset incrementation in loop and reselect spot
                i--;
            }
        }
        
        printGameBoard(size);
    }
    
    void checkNeigbors(int pos1, int pos2) {    //checks individual spot for no mine, pair with clearNeighbors
        if (answerBoard[pos1][pos2] != '*') {
            if (   //pass condition with chosen slot as 1 tile away from mine
                     answerBoard[pos1][pos2] == '_' &&
                      (
                     answerBoard[pos1-1][pos2] == '*' ||
                     answerBoard[pos1+1][pos2] == '*' ||
                     answerBoard[pos1][pos2-1] == '*' ||
                     answerBoard[pos1][pos2+1] == '*' ||
                     answerBoard[pos1-1][pos2-1] == '*' ||
                     answerBoard[pos1-1][pos2+1] == '*' ||
                     answerBoard[pos1+1][pos2-1] == '*' ||
                     answerBoard[pos1+1][pos2+1] == '*'
                      )
                     ) {
                         gameBoard[pos1][pos2] = '1';    //action from else if loop
                       }
            else if (   //pass condition with chosen slot as 2 tiles away from mine
                     answerBoard[pos1][pos2] == '_' &&
                      (
                       answerBoard[pos1][pos2+2] == '*' ||
                       answerBoard[pos1][pos2-2] == '*' ||
                       answerBoard[pos1+2][pos2] == '*' ||
                       answerBoard[pos1-2][pos2] == '*' ||
                       answerBoard[pos1+1][pos2+2] == '*' ||
                       answerBoard[pos1+1][pos2-2] == '*' ||
                       answerBoard[pos1-1][pos2+2] == '*' ||
                       answerBoard[pos1-1][pos2-2] == '*' ||
                       answerBoard[pos1+2][pos2+1] == '*' ||
                       answerBoard[pos1+2][pos2-1] == '*' ||
                       answerBoard[pos1+2][pos2+1] == '*' ||
                       answerBoard[pos1+2][pos2-1] == '*' ||
                       answerBoard[pos1+2][pos2+2] == '*' ||
                       answerBoard[pos1+2][pos2-2] == '*' ||
                       answerBoard[pos1-2][pos2+2] == '*' ||
                       answerBoard[pos1-2][pos2-2] == '*'
                      )
                     ) {
                         gameBoard[pos1][pos2] = '2';
                     }
        }
    }
    
    void clearNeighbors(int pos1, int pos2) {   //checks each neighboring box for lack of mines
        checkNeigbors(pos1-1, pos2);
        checkNeigbors(pos1+1, pos2);
        checkNeigbors(pos1-1, pos2-1);
        checkNeigbors(pos1-1, pos2+1);
        checkNeigbors(pos1+1, pos2-1);
        checkNeigbors(pos1+1, pos2+1);
        checkNeigbors(pos1, pos2-1);
        checkNeigbors(pos1, pos2+1);
    }
    
    /*
    Compares boards to see if game is completed
    */
    int checkWin(int size) {
        int count = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (gameBoard[i][j] == answerBoard[i][j]) {
                    count++;
                }
            }
        }
        if (count == size * size) {
            return 1;   //player wins
        }
        else {
            return 0;   //player will continue for next turn
        }
    }
    
    int checkMine(int pos1, int pos2) {
        if (answerBoard[pos1][pos2] == '*') {
            printf("Mine discovered at coordinates {pos1}, {pos2}\n");
            gameBoard[pos1][pos2] = '*';
            return 1;
        }
        else {
            cout << "No mine located. You lose one stamina\n" << endl;
            return 0;
        }
    }
    
    
    /*
    will check the user's input and see if player has
    hit a mine or close to one
    */
    int checkAndUpdate(int pos1, int pos2) {
        if (answerBoard[pos1][pos2] == '*') {   //fail condition
            gameBoard[pos1][pos2] = '*';
            return -1;
        }
        else if (   //pass condition with chosen slot as 1 tile away from mine
                 answerBoard[pos1][pos2] == '_' &&
                  (
                 answerBoard[pos1-1][pos2] == '*' ||
                 answerBoard[pos1+1][pos2] == '*' ||
                 answerBoard[pos1][pos2-1] == '*' ||
                 answerBoard[pos1][pos2+1] == '*' ||
                 answerBoard[pos1-1][pos2-1] == '*' ||
                 answerBoard[pos1-1][pos2+1] == '*' ||
                 answerBoard[pos1+1][pos2-1] == '*' ||
                 answerBoard[pos1+1][pos2+1] == '*'
                  )
                 ) {
                     gameBoard[pos1][pos2] = '1';    //action from else if loop
                     return 0;
                   }
        else if (   //pass condition with chosen slot as 2 tiles away from mine
                 answerBoard[pos1][pos2] == '_' &&
                  (
                   answerBoard[pos1][pos2+2] == '*' ||
                   answerBoard[pos1][pos2-2] == '*' ||
                   answerBoard[pos1+2][pos2] == '*' ||
                   answerBoard[pos1-2][pos2] == '*' ||
                   answerBoard[pos1+1][pos2+2] == '*' ||
                   answerBoard[pos1+1][pos2-2] == '*' ||
                   answerBoard[pos1-1][pos2+2] == '*' ||
                   answerBoard[pos1-1][pos2-2] == '*' ||
                   answerBoard[pos1+2][pos2+1] == '*' ||
                   answerBoard[pos1+2][pos2-1] == '*' ||
                   answerBoard[pos1+2][pos2+1] == '*' ||
                   answerBoard[pos1+2][pos2-1] == '*' ||
                   answerBoard[pos1+2][pos2+2] == '*' ||
                   answerBoard[pos1+2][pos2-2] == '*' ||
                   answerBoard[pos1-2][pos2+2] == '*' ||
                   answerBoard[pos1-2][pos2-2] == '*'
                  )
                 ) {
                     gameBoard[pos1][pos2] = '2';
                     return 0;
                 }
        else {  //pass condition with no nearby mines
            gameBoard[pos1][pos2] = 'O';
            return 0;
        }
            
        
    }
    
    
    /*
    use to print the player's board
    will update every turn with player's choices
    */
    void printGameBoard(int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << ' ' << gameBoard[i][j] << ' ';
                if (j == size-1) {
                    cout << "\n\n";
                }
            }
        }
        cout << "\n";
    }
    
    /*
    Prints the original board with mine positions
    ::update to include player's choices::
    printed if game is lost
    */
    void printAnswerBoard(int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << ' ' << answerBoard[i][j] << ' ';
                if (j == size-1) {
                    cout << "\n\n";
                }
            }
        }
        cout << "\n";
    }
    
    int checkMove(int x_pos, int y_pos) {
        
        
        return 0;
    }
    
    
    
    private:
        
    char gameBoard[25][25];   //begins as blank, user fills in
    
    char answerBoard[25][25]; //hidden to player
    
};


//Functions

void playerTurn(Board playerBoard, int size) {
    int winCondition = 0;   //stays as 0 to continue game, -1 lose, +1 win
    
    int pos1, pos2, stamina = 3;
    string choice;
    cout << "Would you like to scan for a mine or identify the location of a mine?" << endl;
    cout << "(scan/identify)" << endl;
    cin >> choice;
    cout << "Enter the row where you want to check for a mine: " << endl;
    cin >> pos1;
    cout << "Enter the column where you want to check for a mine: " << endl;
    cin >> pos2;
    pos1 = int(pos1);
    pos2 = int(pos2);
    cout << endl;
    
    if (choice == "scan" || choice == "Scan" || choice == "SCAN") {
        winCondition = playerBoard.checkAndUpdate(pos1, pos2);      //checks player move and returns result of this turn
        playerBoard.clearNeighbors(pos1, pos2);
    }
    else if (choice == "identify" || choice == "Identify" || choice == "IDENTIFY") {
        playerBoard.checkMine(pos1, pos2);
    }
    else {
        cout << "Invalid entry, try again" << endl;
        playerTurn(playerBoard, size);
    }
    
    playerBoard.printGameBoard(size);
    
    if (playerBoard.checkWin(size) == 1) {  //compares boards to see if full match. Iff so, player wins game
        winCondition = 1;
    }
    
    if (winCondition == 0) {
        cout << "continue condition" << endl;
        playerTurn(playerBoard, size);
    }
    else if (winCondition == 1) {
        cout << "win condition" << endl;
    }
    else if (winCondition == -1 || stamina < 1) {
        cout << "lose condition" << endl;
        playerBoard.printAnswerBoard(size);
    }
}


//###MAIN###

int main() {
    
    cout << "Welcome to Minefield! This game plays similar to the classic minesweeper with slightly different rules" << endl;
    cout << "The Minefield will be a square board, with you deciding how large each side is" << endl;
    cout << "Each turn, you will choose whether to scan for a mine, or identify the position of a mine" << endl;
    cout << "When scanning for a mine, you will be told how close the nearest mine is" << endl;
    cout << "(Note that there may be multiple mines in the vicinity)" << endl;
    cout << "Each time you set off a mine or incorrectly identify a mine, you will lose stamina" << endl;
    cout << "If your stamina drops to zero, you lose the game" << endl;
    cout << "Once all mines have been found, you win the game!" << endl;
    cout << "_________________________________________________________________________________________" << endl;
    
    int size;
    cout << "How large would you like your board? (Enter a number less than 25" << endl;
    cin >> size;
    size = int(size);
    
    cout << "Your board will be a(n) " << size << " by " << size << " board" << endl;
    
    Board playerBoard(size);
    playerTurn(playerBoard, size);
    
    playerBoard.printAnswerBoard(size);
    
    return 0;
}
