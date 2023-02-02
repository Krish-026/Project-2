#include <bits/stdc++.h>
#define rep(a, b, c) for (long long a = b; a <= c; ++a)
#define repr(a, b, c) for (long long a = b; a >= c; --a)
using namespace std;
char board[9] = {' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' '};
void show_board();

void get_x_player_choice();
void get_o_player_choice();
void get_computer_choice();

int count_board(char symbol);
char check_winner();
void computer_vs_player();
void player_vs_player();

int minMax(char board[], int, bool);

int main(){
    // system("cls");
    //     for(int i = 0; i < 9; ++i)
    //         board[i] = i+48;
    int choice;
    do{
        system("cls");
        for(int i = 0; i < 9; ++i)
            board[i] = ' ';
        cout << "1. Computer Vs Player." << endl;
        cout << "2. Player Vs Player." << endl;
        cout << "3. Exit" << endl;
        cin >> choice;
        switch(choice){
            case 1:
                computer_vs_player();
                break;
            case 2:
                player_vs_player();
                break;
            case 3: 
                cout << "***** Game Exit *****" << endl;
                break;
            default:
                cout << "Please Select Valid Game Mode." << endl;
                system("pause");
                break;
        }
    }while(choice != 3);

    return 0;
}

void show_board(){
    string s = "         ";
    cout << s <<  "-----------------------" << endl;
    cout << s <<  "|  " << "    |   " << "    |      |" << endl;
    cout << s <<  "|  " << board[0] << "   |   " << board[1] << "   |   " << board[2] << "  |" << endl;
    cout << s <<  "|  " << "   1|   " << "   2|     3|" << endl;
    cout << s <<  "-----------------------" << endl;
    cout << s <<  "|  " << "    |   " << "    |      |" << endl;
    cout << s <<  "|  " << board[3] << "   |   " << board[4] << "   |   " << board[5] << "  |" <<endl;
    cout << s <<  "|  " << "   4|   " << "   5|     6|" << endl;
    cout << s <<  "-----------------------" << endl;
    cout << s <<  "|  " << "    |   " << "    |      |" << endl;
    cout << s <<  "|  " << board[6] << "   |   " << board[7] << "   |   " << board[8] <<"  |" << endl;
    cout << s <<  "|  " << "   7|   " << "   8|     9|" << endl;
    cout << s <<  "-----------------------" << endl;
}

int minMax(char borad[], int depth, bool isMax){
    char res = check_winner();
    if(res == 'D') // Tie = 0
        return 0;
    else if(res == 'X') // If Minimizer Wor
        return -1;
    else if(res == 'O') // If Maximizer Won
        return 1;

    if(isMax){
        int choice, bestScore = INT_MIN;
        //AI turn;
        for(int i = 0; i < 9; ++i){
            if(board[i] == ' '){
                board[i] = 'O'; //ai
                int score = minMax(board, depth+1, false);
                board[i] = ' ';
                bestScore = max(bestScore, score);
            }
        }
        return bestScore;
    }
    else{
        int choice, bestScore = INT_MAX;
        //Human turn;
        for(int i = 0; i < 9; ++i){
            if(board[i] == ' '){
                board[i] = 'X'; //Human
                int score = minMax(board, depth+1, true);
                board[i] = ' ';
                bestScore = min(score, bestScore);
            }
        }
        return bestScore;
    }
    
}


void get_computer_choice(){
    // srand(time(0)); // Learn about this
    // int choice;
    // do{
    //     choice = rand()%10;
    // } while(board[choice] != ' ');
    // board[choice] = 'O';

    int choice, bestScore = INT_MIN;
    //AI turn;
    for(int i = 0; i < 9; ++i){
        if(board[i] == ' '){
            board[i] = 'O'; //ai
            int score = minMax(board, 0, false);
            board[i] = ' ';
            if(score > bestScore){
                bestScore = score;
                choice = i;
            }
        }
    }
    board[choice] = 'O';
}

void get_x_player_choice(){
    while(1){
        cout << "Select Your Position (1 - 9) : " ;
        int choice;
        cin >> choice;
        choice--;
        if(choice < 0 or choice > 8){
            cout << "Please Select Your Choice From (1 - 9)." << endl;
        }
        else if(board[choice] != ' '){
            cout << "Please Select An Empty Position." << endl;
        }
        else{
            board[choice] = 'X';
            break;
        }
    }
}


void get_o_player_choice(){
    while(1){
        cout << "Select Your Position (1 - 9) : " ;
        int choice;
        cin >> choice;
        choice--;
        if(choice < 0 or choice > 8){
            cout << "Please Select Your Choice From (1 - 9)." << endl;
        }
        else if(board[choice] != ' '){
            cout << "Please Select An Empty Position." << endl;
        }
        else{
            board[choice] = 'O';
            break;
        }
    }
}

int count_board(char symbol){
    int total = 0;
    for(int i = 0; i < 9; ++i){
        if(board[i] == symbol)
            ++total;
    }
    return total;
}


char check_winner(){
    // 0  1  2
    // 3  4  5
    // 6  7  8
    //Row Wise
    for(int i = 0; i <= 6; i += 3){
        if(board[i] != ' '){
            if(board[i] == board[i+1] and board[i+1] == board[i+2])
                return board[i];
        }
    }

    // 0  1  2
    // 3  4  5
    // 6  7  8
    //Coloumn Wise
    for(int i = 0; i <= 2; i += 1){
        if(board[i] != ' '){
            if(board[i] == board[i+3] and board[i+3] == board[i+6])
                return board[i];
        }
    }

    // 0  1  2
    // 3  4  5
    // 6  7  8
    // Diagonal
    if(board[0] != ' '){
        if(board[0] == board[4] and board[4] == board[8])
            return board[0];
    }
    if(board[2] != ' '){
        if(board[2] == board[4] and board[4] == board[6])
            return board[2];
    }

    if(count_board('X') + count_board('O') < 9)
        return 'C'; // Continue Game
    else
        return 'D'; // Drawn Game
}

void computer_vs_player(){
    string player_name;
    cout << "Enter Your Name: " ;
    cin >> player_name;
    while(1){
        system("cls");
        show_board();
        if(count_board('X') == count_board('O')){
            cout << player_name << "'s Turn." << endl;
            get_x_player_choice();
        }
        else{
            get_computer_choice();
            system("pause");
        }
        char winner = check_winner();
        if(winner == 'X'){
            system("cls");
            show_board();
            cout << player_name << " Won the Game." << endl;
            system("pause");
            break;
        }
        else if(winner == 'O'){
            system("cls");
            show_board();
            cout << "Computer Won the Game." << endl;
            system("pause");
            break;
        }
        else if(winner == 'D'){
            system("cls");
            show_board();
            cout << "Tie!!!" << endl;
            system("pause");
            break;
        }
    }
}

void player_vs_player(){
    string x_player_name, o_player_name;
    cout << "Enter X Player Name : ";
    cin >> x_player_name;
    cout << "Enter Y Plyer Name : ";
    cin >> o_player_name;
    while(1){
        system("cls");
        show_board();
        if(count_board('X') == count_board('O')){
            cout << x_player_name << "'s Turn." << endl;
            get_x_player_choice();
        }
        else{
            cout << o_player_name << "'s Turn." << endl;
            get_o_player_choice();
        } 
        
        char winner = check_winner();
        if(winner == 'X'){
            system("cls");
            show_board();
            cout << x_player_name << " Won the Game." << endl;
            system("pause");
            break;
        }
        else if(winner == 'O'){
            system("cls");
            show_board();
            cout << o_player_name << " Won the Game." << endl;
            system("pause");
            break;
        }
        else if(winner == 'D'){
            system("cls");
            show_board();
            cout << "Tie!!!" << endl;
            system("pause");
            break;
        }      
    }
}