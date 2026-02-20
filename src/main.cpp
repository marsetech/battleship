#include "utils/GameUtils.h"

int main() {
  benvenuto();

  char choise;
  bool valid_choise = false;

  do {
    std::cout << "\nSelezionare cortesemente una delle seguenti opzioni sottoelencate proposte dal programma:"
              << std::endl;
    std::cout << "(R): Visualizzare il regolamento di gioco. [Raccomandato]" << std::endl;
    std::cout << "(N): Passare direttamente all'inizio del gioco." << std::endl;
    std::cout << "\nDecisione: ";
    std::cin >> choise;

    choise = tolower(choise); // Convert character (avoid mistakes)

    if (choise == 'r') {
      regolamento();
      valid_choise = true;
    } else if (choise == 'n') {
      valid_choise = true;
    } else {
      printCentered("*** E R R O R ***");
      printCentered("::SYSTEM: Invalid option, please make sure to select the currect option...");
    }
  } while (!valid_choise);

  Partita(); // Main Game

  return 0;
}
