#include "modes/TutorialField.h"
#include "utils/GameUtils.h"

CampoPrincipiante::CampoPrincipiante(int dimensione)
    : CampoDiBattaglia(dimensione) {}

void CampoPrincipiante::posizionaNavi() {
  char scelta;
  bool sceltaValida = false;

  do {
    // Chiede all'utente se vuole caricare un file con posizione delle navi già
    // preimpostate o caricarne delle nuove
    std::cout << "\nSeleziona una delle seguenti opzioni sottoelencate"
              << std::endl;
    std::cout << "(E): Carica un file già esistente" << std::endl;
    std::cout << "(N): Creare un nuovo file" << std::endl;
    std::cin >> scelta;

    scelta = tolower(scelta); // Evita errori indesiderati da parte dell'utente

    // Iterazioni che richiamano le funzioni in base alla scelta dell'utente
    if (scelta == 'e') {
      caricaNaviDaFile();
      sceltaValida = true;
    } else if (scelta == 'n') {
      creaNaviInFile();
      sceltaValida = true;
    } else {
      printCentered("||A T T E N Z I O N E||");
      printCentered("Opzione non valida, Assicurati di selezionare una delle "
                    "opzioni valide elencate precedentemente...");
    }
  } while (!sceltaValida);
}

void CampoPrincipiante::caricaNaviDaFile() {
  std::ifstream file("navi.txt"); // Apertura file in modalità lettura

  // Verifica se l'apertura del file è andata a buon fine, in caso contrario
  // stampa errore a schermo
  if (!file) {
    printCentered("*** E R R O R E ***");
    printCentered(
        "Errore durante il caricamento del file delle navi, riprovare...");
    return;
  }

  int x, y; // Dichiarazione delle coordinate delle posizioni delle navi

  // Finché non raggiunge quelle coordinate, continua l'iterazione
  while (file >> x >> y) {
    // Verifica se le coordinate rientrano con la dimensione del campo di gioco
    // scelta
    if (x >= 0 && x < dimensioneGriglia && y >= 0 && y < dimensioneGriglia) {
      griglia[x][y] =
          NaveBattaglia; // Assegnazione char della nave in quella posizione
      naviRimaste++; // Aumento del contatore delle navi rimaste sul campo di
                     // gioco
    }
  }
  file.close(); // Chiusura del file
}

void CampoPrincipiante::creaNaviInFile() {
  int numNavi;

  std::cout << std::endl;
  // Chiede all'utente quante navi vuole posizionare nel campo di gioco
  printCentered("P O S I Z I O N A M E N T O   N A V I");
  std::cout << "\nInserisci il numero di navi da posizionare in battaglia: ";
  std::cin >> numNavi;

  std::ofstream file("navi.txt"); // Apertura file in modalità scrittura

  // Verifica se l'apertura del file è andata a buon fine, in caso contrario
  // stampa errore a schermo
  if (!file) {
    printCentered("*** E R R O R E ***");
    printCentered(
        "Errore durante la creazione del file delle navi, riprovare...");
    return;
  }

  // Chiede all'utente dove posizionare le navi (peculiarità della modalità
  // principiante)
  std::cout << std::endl;
  printCentered("P R E P A R A T I V I   AL L A   B A T T A G L I A!");
  std::cout << "\nInserisci le coordinate (x y) delle posizioni delle navi: "
            << std::endl;

  int x, y; // Dichiarazione variabili delle coordinate delle navi da
            // posizionare

  // Iterazione che controlla quante volte dover inserire le coordinate (in base
  // al numero di navi scelto in precedenza)
  for (int i = 0; i < numNavi; ++i) {
    std::cin >> x >> y;

    // Se coordinate rientrano nella griglia di gioco, posiziona le navi in
    // quella posizione altrimenti manda a schermo errore
    if (x >= 0 && x < dimensioneGriglia && y >= 0 && y < dimensioneGriglia) {
      griglia[x][y] = NaveBattaglia;
      naviRimaste++; // Aumento del conteggio delle navi presenti nel campo di
                     // gioco
      file << x << " " << y << std::endl; // Scrittura su file
    } else {
      printCentered("*** E R R O R E ***");
      printCentered(
          "Coordinate delle navi fuori dalla griglia, riprovare nuovamente!"
          "\nRicordati di selezionare valori compresi nella dimensione della "
          "griglia di gioco");
      --i; // Posizione già occupata, dunque decrementa di 1
    }
  }
  file.close(); // chiusura del file
}
