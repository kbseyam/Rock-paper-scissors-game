#include <iostream>
using namespace std;

enum enChoice { rock = 1, paper = 2, scissors = 3 };
enum enWinner { player, computer, draw };
enum enColor { green, yellow, red };

int randomNumber(int from, int to) { return rand() % (to - from + 1) + from; }

int readNumber(string message, int from, int to) {
  int number = 0;
  do {
    cout << message;
    cin >> number;
  } while (number > to || number < from);

  return number;
}

string getTabs(int numOfTabs) {
  string tabs = "";
  for (int i = 0; i < numOfTabs; i++) tabs += '\t';

  return tabs;
}

enChoice getChoice(int choice) {
  if (choice == 1)
    return enChoice::rock;
  else if (choice == 2)
    return enChoice::paper;
  else
    return enChoice::scissors;
}

string getChoiceText(enChoice choice) {
  if (choice == enChoice::rock)
    return "Rock";
  else if (choice == enChoice::paper)
    return "Paper";
  else
    return "Scissors";
}

enWinner whoWonTheRound(enChoice playerChoice, enChoice computerChoice) {
  if (playerChoice == computerChoice) return enWinner::draw;

  switch (playerChoice) {
    case enChoice::rock:
      if (computerChoice == enChoice::paper) return enWinner::computer;
      break;
    case enChoice::paper:
      if (computerChoice == enChoice::rock) return enWinner::player;
      break;
    default:
      if (computerChoice == enChoice::rock) return enWinner::computer;
      break;
  }

  return enWinner::player;
}

string getWinnerText(enWinner winner) {
  if (winner == enWinner::player)
    return "Player";
  else if (winner == enWinner::computer)
    return "Computer";
  else
    return "No Winner";
}

enWinner whoWinTheGame(short playerWinsCounter, short computerWinsCounter) {
  if (playerWinsCounter > computerWinsCounter)
    return enWinner::player;
  else if (playerWinsCounter < computerWinsCounter)
    return enWinner::computer;
  else
    return enWinner::draw;
}

void resetScreen() {
  system("Color 0F");
  system("cls");
}

void changebackgroundColor(enColor color) {
  if (color == enColor::green)
    system("Color 2F");
  else if (color == enColor::red)
    system("Color 4F");
  else
    system("Color 6F");
}

void printRoundResult(enChoice playerChoice, enChoice computerChoice,
                      enWinner winner, short numOfRound) {
  cout << "\n____________________Round [" << numOfRound
       << "]____________________\n";
  cout << "\nPlayer   Choice: " << getChoiceText(playerChoice);
  cout << "\nComputer Choice: " << getChoiceText(computerChoice);
  cout << "\nRound  Winner  : " << getWinnerText(winner);
  cout << "\n_________________________________________________" << endl;

  if (winner == enWinner::player) {
    changebackgroundColor(enColor::green);
  } else if (winner == enWinner::computer) {
    changebackgroundColor(enColor::red);
    cout << '\a';
  } else {
    changebackgroundColor(enColor::yellow);
  }
}

void updateWinnersStatus(enWinner winner, short &playerWins,
                         short &computerWins, short &draws) {
  switch (winner) {
    case enWinner::player:
      playerWins++;
      break;
    case enWinner::computer:
      computerWins++;
      break;
    default:
      draws++;
      break;
  }
}

// Start round and return winner
enWinner startRound(short roundNum) {
  cout << "\nRound [" << roundNum << "] begains:\n";
  enChoice playerChoice = getChoice(
      readNumber("Your choice: [1]:Rock, [2]:Paper, [3]:Scissors ? ", 1, 3));
  enChoice computerChoice = getChoice(randomNumber(1, 3));
  enWinner winner = whoWonTheRound(playerChoice, computerChoice);
  printRoundResult(playerChoice, computerChoice, winner, roundNum);

  return winner;
}

void printGameResult(short numOfRounds, short playerWinsCounter,
                     short computerWinsCounter, short drawsCounter,
                     string winner) {
  cout << endl
       << getTabs(4)
       << "__________________________________________________________________"
          "\n\n";
  cout << getTabs(4) << "                   +++ G a m e  O v e r +++\n\n";
  cout << getTabs(4)
       << "__________________________________________________________________"
          "\n\n";
  cout << getTabs(4)
       << "_________________________ [Game Results] "
          "_________________________\n\n";
  cout << getTabs(4) << "Game Rounds        : " << numOfRounds << '\n';
  cout << getTabs(4) << "Player won times   : " << playerWinsCounter << '\n';
  cout << getTabs(4) << "Computer won times : " << computerWinsCounter << '\n';
  cout << getTabs(4) << "Draw times         : " << drawsCounter << '\n';
  cout << getTabs(4) << "Final winner       : " << winner << '\n';
  cout << getTabs(4)
       << "__________________________________________________________________"
          "\n"
       << endl;
}

bool checkPlayAgain(string message) {
  char check;
  cout << message;
  cin >> check;

  if (check == 'y' || check == 'Y') return true;

  return false;
}

void startGame() {
  short playerWinsCounter = 0, computerWinsCounter = 0, drawsCounter = 0;
  short numOfRounds = readNumber("How Many Rounds 1 to 10: ", 1, 10);

  for (int i = 1; i <= numOfRounds; i++) {
    // Start round and return winner
    enWinner winnerInRound = startRound(i);
    updateWinnersStatus(winnerInRound, playerWinsCounter, computerWinsCounter,
                        drawsCounter);
  }
  enWinner winnerInGame = whoWinTheGame(playerWinsCounter, computerWinsCounter);
  printGameResult(numOfRounds, playerWinsCounter, computerWinsCounter,
                  drawsCounter, getWinnerText(winnerInGame));

  if (checkPlayAgain(getTabs(4) + "Do you want to play again? Y/N? ")) {
    resetScreen();
    startGame();
  }
}

int main() {
  srand((unsigned)time(NULL));

  startGame();

  return 0;
}
