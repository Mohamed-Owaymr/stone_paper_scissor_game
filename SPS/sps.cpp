/*
  **Project: Rock - Paper - Scissors Game in C++ (Functional Programming)**
[1].Project Overview
This project is an interactive application for the classic "Rock - Paper - Scissors" game, where the user
competes against the computer in multiple rounds, the number of which is predefined. The program is based on
Functional Programming and provides a complete gaming experience with performance enhancements, input management,
and user interaction.


[2].Technologies Used
1.Programming Language: C++
2.Programming Style: Functional Programming


[3]. Project Features
✅ Fully Functional Programming: No use of classes, with the code divided into small specialized functions for each task, making the code clearer and easier to maintain.

✅ Enhanced User Experience:
1.Error handling and re-prompting for invalid input.
2.Using colors in outputs to highlight the winner in each round.
3.Adding time delays between rounds to improve interaction.

✅ Professional Input Management:
1.Validating user input when selecting the number of rounds.
2.Supporting both number and letter-based input dynamically.

✅ Using Enumerations (Enums):
1.Defining possible values for player choices (Stone, Paper, Scissor) Using Magic Enum.
2.Defining winner states (UserWin, ComputerWin, Draw).
3.Reducing errors and improving code clarity.

✅ Clean and Optimized Code:
1.Breaking operations into independent functions.
2.Using Switch Case instead of repeated If-Else.
3.Adopting performance optimization standards.


[4]. How the Program Works
1.The user is prompted to enter the number of rounds.
2.Each round begins, and the user chooses an option from the menu (Rock - Paper - Scissors).
3.The computer randomly selects an option.
4.The winner of each round is determined and results are displayed.
5.After all rounds are finished, the final winner is announced based on the number of victories.
6.The user is given the option to play again or exit the game.


[5]. How is the Winner Determined?
**The winner is determined using the classic game logic:
    -🪨 Rock beats Scissors ✂️
    -📄 Paper beats Rock 🪨
    -✂️ Scissors beats Paper 📄
    -In case of a draw, "No Winner" is declared.


[6]. Future Enhancements
🔹 Add support for multiplayer modes: such as playing against another player instead of the computer.
🔹 Implement a scoring system to save scores across sessions.
🔹 Include a graphical user interface (GUI) instead of command-line interaction.
🔹 Use artificial intelligence to make the computer smarter in its choices.
*/



#include <iostream>
#include <limits>         // For numeric_limits              => check User Input.
#include <cstdlib>        // For rand()                      => Get Randoum Choise From Computer.
#include <ctime>          // For time()                      => Get Randoum Choise From Computer.
#include <chrono>         // For seconds()                   => Handling Precise Time Calculations.
#include <thread>         // For sleep_for()                 => To Pause The Program Execution Efficiently.
#include "magic_enum.hpp" // For magic_enum::enum_count<>()  => To Get The Number Of Enum Members


using namespace std;

bool isNegative(int value)
{
    return value < 0;
}
void cleanCin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void printInvalidValueErrorMessage()
{
    cout << "Error! You Entered Invalid Value\n";
}
int readPositiveNumber(const string& msg)
{
    int number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail() || isNegative(number) || number == 0)
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
bool isUpper(char value)
{
    return value >= 65 && value <= 90;
}
bool isLower(char value)
{
    return value >= 97 && value <= 122;
}
bool isLetter(char value)
{
    return isUpper(value) || isLower(value);
}
char readLetterFromUser(const string& msg)
{
    char input;
    cout << msg <<": ";
    cin >> input;
    while(cin.fail() || !isLetter(input))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> input;
    }
    return input;
}
bool readBoolAsLetter(const string& msg)
{
    char ch = readLetterFromUser(msg);
    if(ch == 'n' || ch == 'N')
    {
        return false;
    }
    else
    {
        return true;
    }
}
int readNegativeNumber(const string& msg)
{
    int number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail() || !isNegative(number) || number == 0)
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
int readNaturalNumber(const string& msg)
{
    int number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail())
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
bool inRange(int number , int from , int to)
{
    return number >= from && number <= to;
}
int readNumberInRange(const string& msg , int from , int to)
{
    int number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail() || !inRange(number , from , to))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
enum enNumberInputTypes{NaturalNum = 1 , PositiveNum = 2 , NegativeNum = 3};
int readNumberFromUser(const string& msg , enNumberInputTypes inputType)
{
    int inputNumber = 0;
    switch (inputType)
    {
    case enNumberInputTypes::NaturalNum:
        inputNumber = readNaturalNumber(msg);
        break;
    case enNumberInputTypes::PositiveNum:
        inputNumber = readPositiveNumber(msg);
        break;
    case enNumberInputTypes::NegativeNum:
        inputNumber = readNegativeNumber(msg);
        break;

    
    default:
        inputNumber = readPositiveNumber(msg);
        break;
    }
    return inputNumber;
}
enum enPlayerOptions{Stone = 1 , Paper = 2 , Scissor = 3};
template <typename EnumType>
size_t getEnumSizeUsingMagicEnumCount()
{
    static_assert(is_enum<EnumType>::value , "Error: The parameter must be an enum!");

    size_t enumSize = magic_enum::enum_count<EnumType>();

    return enumSize;

}
bool gameIsOver(int roundsCount , int currentRound)
{
    return roundsCount < currentRound;
}
string getRoundNumberInFormat(int roundNumber)
{
    return "Round [" + to_string(roundNumber) + "]";
}
void displayUserOptionsList(const string options)
{
    cout << "\n****************************\n";
    cout << "Your Options: \n";
    cout << options << endl;
    cout << "****************************\n";
}
template<typename EnumType>
bool isValidOptionNumber(short opNumber)
{
    size_t enumSize = getEnumSizeUsingMagicEnumCount<EnumType>();
    return opNumber <= enumSize;
}
short defaultOptionNumber()
{
    return 1;
}
template<typename EnumType>
EnumType readOptionNumber(const string& msg , const string& optionsList)
{
    short optionNumber;
    displayUserOptionsList(optionsList);
    optionNumber = readNumberFromUser(msg , PositiveNum);
    while(!isValidOptionNumber<EnumType>(optionNumber))
    {
        printInvalidValueErrorMessage();
        optionNumber = readNumberFromUser(msg , PositiveNum);
    }
    return (EnumType)optionNumber;
}
int getRandomNumberInRange(int from , int to)
{
    int randomNumber = rand() % (to - from + 1);
    randomNumber += from; 
    return randomNumber;
}
enum enGameWinner{UserWin = 1 , ComputerWin = 2 , Draw = 3};
enGameWinner getRoundWinner(enPlayerOptions userOption , enPlayerOptions computerOption)
{
    if(userOption == computerOption)
        return enGameWinner::Draw;

    switch (userOption) {
        case Stone:
            return (computerOption == Scissor) ? enGameWinner::UserWin : enGameWinner::ComputerWin;
        case Paper:
            return (computerOption == Stone) ? enGameWinner::UserWin : enGameWinner::ComputerWin;
        case Scissor:
            return (computerOption == Paper) ? enGameWinner::UserWin : enGameWinner::ComputerWin;
        default:
            return enGameWinner::Draw;
    }
        
}
string getOptionName(enPlayerOptions option)
{
    switch (option)
    {
    case enPlayerOptions::Stone:   return "Stone";
    case enPlayerOptions::Paper:   return "Paper";
    case enPlayerOptions::Scissor: return "Scissor";
    
    default: return "Stone";
    }
}
string getWinnerName(enGameWinner winner)
{
    switch (winner)
    {
    case enGameWinner::UserWin:     return "Player";
    case enGameWinner::ComputerWin: return "Computer";
    case enGameWinner::Draw:        return "[No Winner]";

    default: return "Player";
    }
}
struct stRoundResults
{
    short roudNumber = 0;
    enPlayerOptions userOption;
    enPlayerOptions computerOption;
    enGameWinner roundWinner;
};
string redColorEscapeCode()
{
    return "\033[31m";
}
string greenColorEscapeCode()
{
    return "\033[32m";
}
string yellowColorEscapeCode()
{
    return "\033[33m";
}
string defultColorEscapeCode()
{
    return "\033[37m";
}
void changeTheColorThemAccordingWinner(enGameWinner winner)
{
    switch (winner)
    {
    case enGameWinner::UserWin:     cout << greenColorEscapeCode(); break; 
    case enGameWinner::ComputerWin: cout << redColorEscapeCode(); break; 
    case enGameWinner::Draw:        cout << yellowColorEscapeCode(); break; 
    
    default: cout << greenColorEscapeCode(); break;
        break;
    }
}
void restartTextColor()
{
    cout << defultColorEscapeCode();
}
void printRoundResultWithChangeColor(const stRoundResults& roundResults)
{
    changeTheColorThemAccordingWinner(roundResults.roundWinner);
    cout << "\n_____________" << getRoundNumberInFormat(roundResults.roudNumber) << "_____________\n\n";
    cout << "Player    Choice : " << getOptionName(roundResults.userOption)     << endl;
    cout << "Coumputer Choice : " << getOptionName(roundResults.computerOption) << endl;
    cout << "Round Winner     : " << getWinnerName(roundResults.roundWinner) << endl;
    cout << "__________________________________\n\n";
    restartTextColor();
}
void fillRoundResultsDetails(stRoundResults& roundResults , short roudNumber)
{
    roundResults.userOption     = readOptionNumber<enPlayerOptions>("Your Choice" , "[1].Stone\n[2].Paper\n[3].Scissor\n");
    roundResults.computerOption = (enPlayerOptions)getRandomNumberInRange(1 , 3);
    roundResults.roundWinner    = getRoundWinner(roundResults.userOption , roundResults.computerOption);
    roundResults.roudNumber     = roudNumber;
}
stRoundResults runGameRound(short roudNumber)
{
    stRoundResults roundResults;
    cout << "\n" << getRoundNumberInFormat(roudNumber) << " Begins: \n";
    fillRoundResultsDetails(roundResults , roudNumber);
    printRoundResultWithChangeColor(roundResults);
    return roundResults;
}
struct stGameResults
{
    short gameRounds     = 0;
    short userWins       = 0;
    short computterWins  = 0;
    short draws          = 0;
};
void updateGameResultAfterRound(stRoundResults roundResults , stGameResults& gameResults)
{
    ++gameResults.gameRounds;
    switch (roundResults.roundWinner)
    {
    case enGameWinner::UserWin: ++gameResults.userWins;break;
    case enGameWinner::ComputerWin: ++gameResults.computterWins;break;
    case enGameWinner::Draw: ++gameResults.draws;break;
    
    default: ++gameResults.userWins;
        break;
    }
}
enGameWinner getTheFinalWinner(const stGameResults& gameResults)
{
    if(gameResults.userWins > gameResults.computterWins)
    {
        return enGameWinner::UserWin;
    }
    else if(gameResults.userWins < gameResults.computterWins)
    {
        return enGameWinner::ComputerWin;
    }
    else
    {
        return enGameWinner::Draw;
    }
}
void dispalyGameOverHeader()
{
    cout << "\n\t\t_______________________________________________________\n";
    cout << "\n\t\t______________+++ [G A M E   O V E R] +++______________\n";
    cout << "\n\t\t_______________________________________________________\n";
}
void displayFinalGameResults(const stGameResults& gameResults)
{
    changeTheColorThemAccordingWinner(getTheFinalWinner(gameResults));
    dispalyGameOverHeader();
    cout << "\n\t\t__________________ [ Game Results ] ___________________\n\n";
    cout << "\t\tGame Rounds    : " << gameResults.gameRounds                        << "\n";
    cout << "\t\tUser Wins      : " << gameResults.userWins                          << "\n";
    cout << "\t\tCoumputer Wins : " << gameResults.computterWins                     << "\n";
    cout << "\t\tDraw Times     : " << gameResults.draws                             << "\n";
    cout << "\t\tFinal Winner   : " << getWinnerName(getTheFinalWinner(gameResults)) << "\n";
    cout << "\t\t_______________________________________________________\n";
    restartTextColor();
}
void runTheGameInRounds(short roundsCount)
{
    short roudNumber = 1;
    stGameResults gameResults;
    stRoundResults roundResults;
    while(!gameIsOver(roundsCount , roudNumber))
    {
        roundResults = runGameRound(roudNumber);
        updateGameResultAfterRound(roundResults , gameResults);
        this_thread::sleep_for(std::chrono::seconds(2));
        ++roudNumber;
    }
    displayFinalGameResults(gameResults);
}

void startGame()
{
    short roundsCount = 0;
    bool continueGame = true;
    do
    {
        roundsCount = readNumberInRange("Please Enter How Many Rounds Do You Want To Play from 1 to 10" , 1 , 10);
        runTheGameInRounds(roundsCount);
        continueGame = readBoolAsLetter("\t\tDo You Want To Play Again?? N/Y");
    } while (continueGame);
}

int main()
{
    unsigned int seed = (unsigned)time(0);
    srand(seed);

    startGame();
    
    return 0;
}


