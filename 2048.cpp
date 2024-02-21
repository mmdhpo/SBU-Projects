#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // for color
int **gameBoard;
int n;
int score = 0;
string name;
int totalPlayers;

struct Player
{
    string name;
    int score;
    int boardSize;
};
void up(int **&board);
void sumUp(int **&board, bool boardValue);
void down(int **&board);
void sumDown(int **&board, bool boardValue);
void right(int **&board);
void sumRight(int **&board, bool boardValue);
void left(int **&board);
void sumLeft(int **&board, bool boardValue);
int zeroCount();
void numGenerator();
void displayMenu();
void playGame(int);
void displayGameBoard();
void deleteBoard(int **&board);
bool equalCheck(int **gameBoardCopy);
bool moveCheck(int **gameBoardCopy, char x);
bool gameOver();
bool winner();
void bubbleSort(Player *&leaderBoard, int playerCount);
void readFromFile(Player *&leaderBoard);
void writeToFile(Player *leaderBoard);
void playerCount();
int samePlayerAddress();
void appendToLeaderboard(Player *&leaderBoard);
void printFromFile();

void welcome();
void win();
void gameover();
void goodLuck();

int main()
{
    displayMenu();
    return 0;
}

// move all my gameBoard's elements up
void up(int **&board)
{
    for (int j = 0; j < n; j++)
    {
        int countZero = 0;
        for (int i = 0; i < n; i++)
        {
            if (board[i][j] == 0)
            {
                countZero++;
            }
            else if (countZero == 0)
            {
                continue;
            }
            else
            {
                board[i - countZero][j] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
}

// first use up function then sum the elements if possible then use up again
void sumUp(int **&board, bool boardValue)
{
    up(board);
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            if (board[i][j] == board[i + 1][j])
            {
                board[i][j] *= 2;
                if (boardValue)
                {
                    score += board[i][j];
                }
                board[i + 1][j] = 0;
            }
        }
    }
    up(board);
}

// move all my gameBoard's elements down
void down(int **&board)
{
    for (int j = 0; j < n; j++)
    {
        int countZero = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (board[i][j] == 0)
            {
                countZero++;
            }
            else if (countZero == 0)
            {
                continue;
            }
            else
            {
                board[i + countZero][j] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
}
// move all elements down with down function
void sumDown(int **&board, bool boardValue)
{
    down(board);
    for (int j = 0; j < n; j++)
    {
        for (int i = n - 1; i > 0; i--)
        {
            if (board[i][j] == board[i - 1][j])
            {
                board[i][j] *= 2;
                if (boardValue)
                {
                    score += board[i][j];
                }
                board[i - 1][j] = 0;
            }
        }
    }
    down(board);
}

// move all my gameBoard's elements right
void right(int **&board)
{
    for (int i = 0; i < n; i++)
    {
        int countZero = 0;
        for (int j = n - 1; j >= 0; j--)
        {
            if (board[i][j] == 0)
            {
                countZero++;
            }
            else if (countZero == 0)
            {
                continue;
            }
            else
            {
                board[i][j + countZero] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
}

void sumRight(int **&board, bool boardValue)
{
    right(board);
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > 0; j--)
        {
            if (board[i][j] == board[i][j - 1])
            {
                board[i][j] *= 2;
                if (boardValue)
                {
                    score += board[i][j];
                }
                board[i][j - 1] = 0;
            }
        }
    }
    right(board);
}

// move all my gameBoard's elements left
void left(int **&board)
{
    for (int i = 0; i < n; i++)
    {
        int countZero = 0;
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 0)
            {
                countZero++;
            }
            else if (countZero == 0)
            {
                continue;
            }
            else
            {
                board[i][j - countZero] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
}

void sumLeft(int **&board, bool boardValue)
{
    left(board);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == board[i][j + 1])
            {
                board[i][j] *= 2;
                if (boardValue)
                {
                    score += board[i][j];
                }
                board[i][j + 1] = 0;
            }
        }
    }
    left(board);
}

// puting a random number between 2 & 4 in a random element of gameBoard array
void numGenerator()
{
    if (zeroCount() == 0)
        return;
    srand(static_cast<unsigned int>(time(nullptr)));
    int randNum = rand() % 4 + 1;
    int randRow, randCol;
    while (true)
    {
        randRow = rand() % n;
        randCol = rand() % n;
        if (gameBoard[randRow][randCol] == 0)
            break;
    }
    if (randNum == 4)
        gameBoard[randRow][randCol] = 4;
    else
        gameBoard[randRow][randCol] = 2;
}

int zeroCount()
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (gameBoard[i][j] == 0)
                count++;
        }
    }
    return count;
}

void displayMenu()
{
    bool y = true;
    int l;
    srand(static_cast<unsigned int>(time(nullptr)));
    l = rand() % 15;
    SetConsoleTextAttribute(hConsole, l);
    welcome();
    cout << "                                                         Press Any Buttom to start\n";
    getch();
    while (y)
    {
        char userInput;
        SetConsoleTextAttribute(hConsole, l);
        cout << "If you want to Play Game press 1\n"
             << "If want to see our pro players in Leaderboard press 2\n"
             << "If you wanna leave the game press 3\n";
        cin >> userInput;

        switch (userInput)
        {
        case '1':
            playGame(l);
            Player *leaderBoard;
            appendToLeaderboard(leaderBoard);
            writeToFile(leaderBoard);
            delete[] leaderBoard;
            totalPlayers = 0;
            SetConsoleTextAttribute(hConsole, 15);
            score = 0;
            break;
        case '2':
            printFromFile();
            break;
        case '3':
            y = false;
            goodLuck();
            break;
        default:
            break;
        }
    }
}

void playGame(int l)
{
    cout << "                                                            please enter your name\n";
    cin >> name;
    cout << "                                                      please enter the size of board\n";
    cin >> n;
    cout << "                                  if you want to exit the game and go to menu at any time you can press q\n";
    Sleep(1000);
    gameBoard = new int *[n];
    // initializing gameBoard with 0
    for (int i = 0; i < n; i++)
    {
        gameBoard[i] = new int[n];
        for (int j = 0; j < n; j++)
            gameBoard[i][j] = 0;
    }
    numGenerator();
    numGenerator();
    int k = 0;
    while (true)
    {
        displayGameBoard();
        if (gameOver())
        {
            SetConsoleTextAttribute(hConsole, l);
            gameover();
            break;
        }
        if (winner() && k == 0)
        {
            k++;
            int m;
            SetConsoleTextAttribute(hConsole, l);
            win();
            cout << "                                               Look who is the Winner \n"
                 << "                                     Do you want to continue or go back to Menu ?\n"
                 << "                                                  Tap 1 to Continue\n"
                 << "                                                 Tap 2 to go to Menu\n";
            cin >> m;
            if (m == 2)
                break;
        }
        int **gameBoardCopy = new int *[n];
        for (int i = 0; i < n; i++)
        {
            gameBoardCopy[i] = new int[n];
            for (int j = 0; j < n; j++)
                gameBoardCopy[i][j] = gameBoard[i][j];
        }
        char userInput;
        userInput = getch();
        switch (userInput)
        {
        case 'w':
            sumUp(gameBoard, true);
            break;
        case 'd':
            sumRight(gameBoard, true);
            break;
        case 's':
            sumDown(gameBoard, true);
            break;
        case 'a':
            sumLeft(gameBoard, true);
            break;
        default:
            break;
        case 'q':
            break;
        }
        if (userInput == 'q')
            break;
        if (equalCheck(gameBoardCopy) == false)
            numGenerator();
        deleteBoard(gameBoardCopy);
    }
}

void displayGameBoard()
{
    system("cls");
    cout << ">>> score: " << score << " <<<\n";
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            cout << "\u001b[36;1m\u256D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u256E";
        }
        cout << endl;
        for (int k = 0; k < n; k++)
        {
            cout << "\u001b[36;1m\u2503         \u2503";
        }
        cout << endl;
        for (int j = 0; j < n; j++)
        {
            cout << "\u001b[36;1m\u2503\u001b[0m  ";
            cout << "\u001b[1m";
            switch (gameBoard[i][j])
            {
            case 0:
                cout << "     ";
                break;
            case 2:
                cout << "\u001b[32;1m  " << 2 << "  ";
                break;
            case 4:
                cout << "\u001b[30;1m  " << 4 << "  ";
                break;
            case 8:
                cout << "\u001b[36;1m  " << 8 << "  ";
                break;
            case 16:
                cout << "\u001b[34m " << 16 << "  ";
                break;
            case 32:
                cout << "\u001b[33m " << 32 << "  ";
                break;
            case 64:
                cout << "\u001b[32m " << 64 << "  ";
                break;
            case 128:
                cout << "\u001b[35m " << 128 << " ";
                break;
            case 256:
                cout << "\u001b[33;1m " << 256 << " ";
                break;
            case 512:
                cout << "\u001b[31;1m " << 512 << " ";
                break;
            case 1024:
                cout << "\u001b[31m" << 1024 << " ";
                break;
            case 2048:
                cout << "\u001b[37;1m" << 2048 << " ";
                break;
            case 4096:
                cout << "\u001b[35;1m" << 4096 << " ";
                break;
            case 8192:
                cout << "\u001b[34m" << 8192 << " ";
                break;
            case 16384:
                cout << "\u001b[36m" << 16384;
                break;
            case 32768:
                cout << "\u001b[31m" << 32768;
                break;
            case 65536:
                cout << "\u001b[31m" << 65536;
                break;
            default:
                break;
            }
            cout << "\u001b[0m";
            cout << "  \u001b[36;1m\u2503\u001b[0m";
        }
        cout << endl;
        for (int k = 0; k < n; k++)
        {
            cout << "\u001b[36;1m\u2503         \u2503\u001b[0m";
        }
        cout << endl;
        for (int k = 0; k < n; k++)
        {
            cout << "\u001b[36;1m\u2570\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u256F\u001b[0m";
        }
        cout << endl;
    }
}

// false means the copy isn't equal with game board
bool equalCheck(int **gameBoardCopy)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (gameBoardCopy[i][j] != gameBoard[i][j])
                return false;
        }
    }
    return true;
}

// checking if player can do another move when the board is full & false means it can't move in char userInput direction
bool moveCheck(int **gameBoardCopy, char x)
{
    switch (x)
    {
    case 'w':
        sumUp(gameBoardCopy, false);
        return !equalCheck(gameBoardCopy);
    case 'd':
        sumRight(gameBoardCopy, false);
        return !equalCheck(gameBoardCopy);
    case 's':
        sumDown(gameBoardCopy, false);
        return !equalCheck(gameBoardCopy);
    case 'a':
        sumLeft(gameBoardCopy, false);
        return !equalCheck(gameBoardCopy);
    }
    return false;
}

void deleteBoard(int **&board)
{
    for (int i = 0; i < n; i++)
        delete[] board[i];
    delete[] board;
}

//check if player lost the game or not
bool gameOver()
{
    bool isFull = true;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (gameBoard[i][j] == 0)
                isFull = false;
        }
    }
    if (isFull)
    {
        int **gameBoardCopy = new int *[n];
        for (int i = 0; i < n; i++)
        {
            gameBoardCopy[i] = new int[n];
            for (int j = 0; j < n; j++)
                gameBoardCopy[i][j] = gameBoard[i][j];
        }

        if (moveCheck(gameBoardCopy, 'w') == false && moveCheck(gameBoardCopy, 'd') == false && moveCheck(gameBoardCopy, 's') == false && moveCheck(gameBoardCopy, 'a') == false)
        {
            deleteBoard(gameBoard);
            deleteBoard(gameBoardCopy);
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

//if any 2048 apear in board it will find it 
bool winner()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (gameBoard[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

// file processing ___________________________________________________________________________________

void bubbleSort(Player *&leaderBoard, int playerCount)
{
    for (int i = 0; i < playerCount; i++)
    {
        for (int j = 0; j < playerCount - 1; j++)
        {
            if (leaderBoard[j].score < leaderBoard[j + 1].score)
            {
                swap(leaderBoard[j].score, leaderBoard[j + 1].score);
                swap(leaderBoard[j].name, leaderBoard[j + 1].name);
                swap(leaderBoard[j].boardSize, leaderBoard[j + 1].boardSize);
            }
        }
    }
}

void readFromFile(Player *&leaderBoard)
{
    int i = 0;
    string playerName, playerScore, boardSize;
    ifstream file("leaderboard.txt", ios::in);
    if (file.is_open())
    {
        while (file >> playerName >> playerScore >> boardSize)
        {
            leaderBoard[i].name = playerName;
            leaderBoard[i].score = stoi(playerScore);
            leaderBoard[i].boardSize = stoi(boardSize);
            i++;
        }
        file.close();
    }
}

void writeToFile(Player *leaderBoard)
{
    ofstream file("leaderboard.txt", ios::out);
    for (int i = 0; i < totalPlayers; ++i)
    {
        file << leaderBoard[i].name << " " << leaderBoard[i].score << " " << leaderBoard[i].boardSize << endl;
    }
    file.close();
}

// read from file and count the amount of lines(players)
void playerCount()
{
    string playerName, playerScore, boardSize;
    ifstream file("leaderboard.txt", ios::in);
    if (file.is_open())
    {
        while (file >> playerName >> playerScore >> boardSize)
        {
            totalPlayers++;
        }
        file.close();
    }
}

// in this function if any same name with same board size is available , it will give me it's address if not will give me -1
int samePlayerAddress()
{
    if (totalPlayers != 0)
    {
        Player *temp = new Player[totalPlayers];
        readFromFile(temp);
        for (int i = 0; i < totalPlayers; i++)
        {
            if (name == temp[i].name && temp[i].boardSize == n)
                return i;
        }
        return -1;
    }
    return -1;
}

void appendToLeaderboard(Player *&leaderBoard)
{
    playerCount();
    int address = samePlayerAddress();
    Player *temp = new Player[totalPlayers];
    readFromFile(temp);
    if (address >= 0)
    {
        bool isBetter = false;
        if (temp[address].score < score)
        {
            leaderBoard = new Player[totalPlayers];
            readFromFile(leaderBoard);
            leaderBoard[address].score = score;
            isBetter = true;
        }
        if (isBetter)
            bubbleSort(leaderBoard, totalPlayers);
        else
        {
            leaderBoard = new Player[totalPlayers];
            readFromFile(leaderBoard);
        }
    }
    else
    {
        totalPlayers += 1;
        leaderBoard = new Player[totalPlayers];
        readFromFile(leaderBoard);
        leaderBoard[totalPlayers - 1].name = name;
        leaderBoard[totalPlayers - 1].score = score;
        leaderBoard[totalPlayers - 1].boardSize = n;
        bubbleSort(leaderBoard, totalPlayers);
    }
}

void printFromFile()
{
    int i = 1;
    string playerName, playerScore, boardSize;
    ifstream file("leaderboard.txt", ios::in);
    if (file.is_open())
    {
        string size;
        cout << "Please enter the board size that you want to see it's leaderboard: \n";
        cin >> size;
        system("cls");
        for (int i = 0; i < 20; i++)
            cout << "\u2550";
        cout << " board size: " << size << " ";
        for (int i = 0; i < 20; i++)
            cout << "\u2550";
        cout << endl;
        cout << "Ranking "
             << "| name "
             << "| score " << endl;
        while (file >> playerName >> playerScore >> boardSize)
        {
            if (boardSize == size)
            {
                cout << i << "   -    " << playerName << "      "
                     << playerScore << "      " << endl;
                i++;
            }
        }
        for (int i = 0; i < 55; i++)
            cout << "\u2550";
        cout << endl;
        file.close();
    }
}
//______________________________________________________________________________________________________
// cout welcome
void welcome()
{
    cout << "                                                          :                                                               :      \n";
    Sleep(50);
    cout << "                               ,;                  .,    t#,                                 ,;                          t#,     \n";
    Sleep(50);
    cout << "                             f#i            i     ,Wt   ;##W.                              f#i                          ;##W.    \n";
    Sleep(50);
    cout << "               ;           .E#t            LE    i#D.  :#L:WE             ..       :     .E#t               GEEEEEEEL  :#L:WE    \n";
    Sleep(50);
    cout << "             .DL          i#W,            L#E   f#f   .KG  ,#D           ,W,     .Et    i#W,                ,;;L#K;;. .KG  ,#D   \n";
    Sleep(50);
    cout << "     f.     :K#L     LWL L#D.            G#W. .D#i    EE    ;#f         t##,    ,W#t   L#D.                    t#E    EE    ;#f  \n";
    Sleep(50);
    cout << "     EW:   ;W##L   .E#f:K#Wfff;         D#K. :KW,    f#.     t#i       L###,   j###t :K#Wfff;                  t#E   f#.     t#i \n";
    Sleep(50);
    cout << "     E#t  t#KE#L  ,W#; i##WLLLLt       E#K.  t#f     :#G     GK      .E#j##,  G#fE#t i##WLLLLt                 t#E   :#G     GK  \n";
    Sleep(50);
    cout << "     E#t f#D.L#L t#K:   .E#L         .E#E.    ;#G     ;#L   LW.     ;WW; ##,:K#i E#t  .E#L                     t#E    ;#L   LW.  \n";
    Sleep(50);
    cout << "     E#jG#f  L#LL#G       f#E:      .K#E       :KE.    t#f f#:     j#E.  ##f#W,  E#t    f#E:                   t#E     t#f f#:   \n";
    Sleep(50);
    cout << "     E###;   L###j         ,WW;    .K#D         .DW:    f#D#;    .D#L    ###K:   E#t     ,WW;                  t#E      f#D#;    \n";
    Sleep(50);
    cout << "     E#K:    L#W;           .D#;  .W#G            L#,    G#t    :K#t     ##D.    E#t      .D#;                 t#E       G#t     \n";
    Sleep(50);
    cout << "     EG      LE.              tt :W##########Wt    jt     t     ...      #G      ..         tt                  fE        t      \n";
    Sleep(50);
    cout << "     ;       ;@                  :,,,,,,,,,,,,,.                         j                                       :               \n";
    cout << "                                                                                                                                 \n";
    cout << "                                                                                                                                 \n";
    cout << "                                                                                   .                                             \n";
    Sleep(50);
    cout << "                                                    t                             ,W                                             \n";
    Sleep(50);
    cout << "                                                    EE.                          i##     t,                                      \n";
    Sleep(50);
    cout << "                                                    :KW;           :            f###     tW:                                     \n";
    Sleep(50);
    cout << "                                                      G#j         G#j          G####     t#W.                                    \n";
    Sleep(50);
    cout << "                                                       j#D.     .E#G#G       .K#Ki##     tEDE                                    \n";
    Sleep(50);
    cout << "                                                    itttG#K,   ,W#; ;#E.    ,W#D.,##  ...jK:KD                                   \n";
    Sleep(50);
    cout << "                                                    E##DDDDG: i#K:   :WW:  i##E,,i##, E#fDWfff:                                  \n";
    Sleep(50);
    cout << "                                                    E#E       :WW:   f#D. ;DDDDDDE##DGiGEjE                                      \n";
    Sleep(50);
    cout << "                                                    E#E        .E#; G#L          ,##    G#E                                      \n";
    Sleep(50);
    cout << "                                                    E##EEEEEEt   G#K#j           ,##     GE                                      \n";
    Sleep(50);
    cout << "                                                    tffffffffft   j#;            .E#      t                                      \n";
    cout << "                                                                                   t                                             \n\n";
}
// cout winner
void win()
{
    cout << "                                                L.             L.                     ,;           \n";
    Sleep(100);
    cout << "                                            t   EW:        ,ft EW:        ,ft       f#i j.         \n";
    Sleep(100);
    cout << "                                   ;        Ej  E##;       t#E E##;       t#E     .E#t  EW,        \n";
    Sleep(100);
    cout << "                                 .DL        E#, E###t      t#E E###t      t#E    i#W,   E##j       \n";
    Sleep(100);
    cout << "                         f.     :K#L     LWLE#t E#fE#f     t#E E#fE#f     t#E   L#D.    E###D.     \n";
    Sleep(100);
    cout << "                         EW:   ;W##L   .E#f E#t E#t D#G    t#E E#t D#G    t#E :K#Wfff;  E#jG#W;    \n";
    Sleep(100);
    cout << "                         E#t  t#KE#L  ,W#;  E#t E#t  f#E.  t#E E#t  f#E.  t#E i##WLLLLt E#t t##f   \n";
    Sleep(100);
    cout << "                         E#t f#D.L#L t#K:   E#t E#t   t#K: t#E E#t   t#K: t#E  .E#L     E#t  :K#E: \n";
    Sleep(100);
    cout << "                         E#jG#f  L#LL#G     E#t E#t    ;#W,t#E E#t    ;#W,t#E    f#E:   E#KDDDD###i\n";
    Sleep(100);
    cout << "                         E###;   L###j      E#t E#t     :K#D#E E#t     :K#D#E     ,WW;  E#f,t#Wi,,,\n";
    Sleep(100);
    cout << "                         E#K:    L#W;       E#t E#t      .E##E E#t      .E##E      .D#; E#t  ;#W:  \n";
    Sleep(100);
    cout << "                         EG      LE.        E#t ..         G#E ..         G#E        tt DWi   ,KK: \n";
    Sleep(100);
    cout << "                         ;       ;@         ,;.             fE             fE                      \n";
    cout << "                                                             ,              ,                      \n";
}
// cout gameover
void gameover()
{
    cout << "                                                                      :                                   \n";
    Sleep(150);
    cout << "                                                               ,;    t#,                     ,;           \n";
    Sleep(150);
    cout << "                .Gt                                          f#i    ;##W.                  f#i j.         \n";
    Sleep(150);
    cout << "               j#W:            ..           ..       :     .E#t    :#L:WE                .E#t  EW,        \n";
    Sleep(150);
    cout << "             ;K#f             ;W,          ,W,     .Et    i#W,    .KG  ,#D  t      .DD. i#W,   E##j       \n";
    Sleep(150);
    cout << "           .G#D.             j##,         t##,    ,W#t   L#D.     EE    ;#f EK:   ,WK. L#D.    E###D.     \n";
    Sleep(150);
    cout << "          j#K;              G###,        L###,   j###t :K#Wfff;  f#.     t#iE#t  i#D :K#Wfff;  E#jG#W;    \n";
    Sleep(150);
    cout << "        ,K#f   ,GD;       :E####,      .E#j##,  G#fE#t i##WLLLLt :#G     GK E#t j#f  i##WLLLLt E#t t##f   \n";
    Sleep(150);
    cout << "         j#Wi   E#t      ;W#DG##,     ;WW; ##,:K#i E#t  .E#L      ;#L   LW. E#tL#i    .E#L     E#t  :K#E: \n";
    Sleep(150);
    cout << "          .G#D: E#t     j###DW##,    j#E.  ##f#W,  E#t    f#E:     t#f f#:  E#WW,       f#E:   E#KDDDD###i\n";
    Sleep(150);
    cout << "            ,K#fK#t    G##i,,G##,  .D#L    ###K:   E#t     ,WW;     f#D#;   E#K:         ,WW;  E#f,t#Wi,,,\n";
    Sleep(150);
    cout << "              j###t  :K#K:   L##, :K#t     ##D.    E#t      .D#;     G#t    ED.           .D#; E#t  ;#W:  \n";
    Sleep(150);
    cout << "               .G#t ;##D.    L##, ...      #G      ..         tt      t     t               tt DWi   ,KK: \n";
    Sleep(150);
    cout << "                 ;; ,,,      .,,           j                                                              \n";
}
// cout good luck
void goodLuck()
{
    cout << "                                          ;                                                                      \n";
    Sleep(100);
    cout << "                       :           :      ED.                                                                    \n";
    Sleep(100);
    cout << "                      t#,         t#,     E#Wi                               :              .,  G:               \n";
    Sleep(100);
    cout << "               .Gt   ;##W.       ;##W.    E###G.                        i    Ef            ,Wt  E#,    :     ;f. \n";
    Sleep(100);
    cout << "              j#W:  :#L:WE      :#L:WE    E#fD#W;                      LE    E#t          i#D.  E#t  .GE     i##:\n";
    Sleep(100);
    cout << "            ;K#f   .KG  ,#D    .KG  ,#D   E#t t##L                    L#E    E#t         f#f    E#t j#K;     i##:\n";
    Sleep(100);
    cout << "          .G#D.    EE    ;#f   EE    ;#f  E#t  .E#K,                 G#W.    E#t       .D#i     E#GK#f       i##:\n";
    Sleep(100);
    cout << "         j#K;     f#.     t#i f#.     t#i E#t    j##f               D#K.     E#t fi   :KW,      E##D.        i##:\n";
    Sleep(100);
    cout << "       ,K#f   ,GD;:#G     GK  :#G     GK  E#t    :E#K:             E#K.      E#t L#j  t#f       E##Wi        i##:\n";
    Sleep(100);
    cout << "        j#Wi   E#t ;#L   LW.   ;#L   LW.  E#t   t##L             .E#E.       E#t L#L   ;#G      E#jL#D:      i##:\n";
    Sleep(100);
    cout << "         .G#D: E#t  t#f f#:     t#f f#:   E#t .D#W;             .K#E         E#tf#E:    :KE.    E#t ,K#j     i##:\n";
    Sleep(100);
    cout << "           ,K#fK#t   f#D#;       f#D#;    E#tiW#G.             .K#D          E###f       .DW:   E#t   jD     i#W.\n";
    Sleep(100);
    cout << "             j###t    G#t         G#t     E#K##i              .W#G           E#K,          L#,  j#t              \n";
    Sleep(100);
    cout << "              .G#t     t           t      E##D.              :W##########Wt  EL             jt   ,;          :G#:\n";
    Sleep(100);
    cout << "                ;;                        E#t                :,,,,,,,,,,,,, .:                               iKt \n";
    cout << "                                          L:                                                                     \n";
}