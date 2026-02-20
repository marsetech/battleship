#include "field/BattleField.h"
#include "modes/AdvancedField.h"
#include "modes/IntermediateField.h"
#include "modes/TutorialField.h"
#include "utils/GameUtils.h"

CampoDiBattaglia::CampoDiBattaglia(int dimensione)
    : dimensioneGriglia(dimensione), naviRimaste(0), sparoNonSalvato(false) {
  griglia.resize(dimensioneGriglia, std::vector<char>(dimensioneGriglia, Mare));
}

void CampoDiBattaglia::stampaGriglia(bool mostraNavi) const {
  std::cout << std::endl;
  printCentered("C A M P O   D I   B A T T A G L I A");

  for (int i = 0; i < dimensioneGriglia; ++i) {
    std::string riga;
    for (int j = 0; j < dimensioneGriglia; ++j) {
      char simbolo = griglia[i][j];
      // Se non si vogliono mostrare le navi, nascondile
      if (!mostraNavi && simbolo == NaveBattaglia) {
        simbolo = Mare;
      }
      riga += simbolo;
      riga += " ";
    }
    printCentered(riga);
  }
}

void CampoDiBattaglia::gestioneSparo() {
  int  x, y;
  bool coordinateValide = false;

  // Richiede all'utente di inserire le coordinate con controllo validità
  do {
    std::string inputX, inputY;

    std::cout << std::endl;
    printCentered("P R E P A R A T I V I   P E R   L O   S P A R O...");
    printCentered("Mi raccomando, ricorda di inserire lo spazio tra le due coordinate!!");
    std::cout << "\nInserire le coordinate (x y) dello sparo da effettuare: ";
    std::cin >> inputX >> inputY;

    // Verifica singolarmente se tutti i caratteri delle dimensioni inserite
    // sono numeri
    bool isNumberX = !inputX.empty() && std::all_of(inputX.begin(), inputX.end(), ::isdigit);
    bool isNumberY = !inputY.empty() && std::all_of(inputY.begin(), inputY.end(), ::isdigit);

    // Se entrambi gli input sono valori numerici, lo convertono in un intero
    if (isNumberX && isNumberY) {
      x                = std::stoi(inputX);
      y                = std::stoi(inputY);
      coordinateValide = true;
    } else {
      printCentered("*** E R R O R E ***");
      printCentered("Coordinate non valide, riprova assicurandoti di inserire "
                    "numeri interi...");
    }
  } while (!coordinateValide);

  // Verifica il colpo e aggiorna la griglia
  verificaSparo(x, y);
}

bool CampoDiBattaglia::verificaSparo(int x, int y) {
  // Funzione che gestisce gli errori o, in caso contrario, aggiorni la griglia
  // di combattimento
  std::cout << std::endl;
  printCentered("E S I T O   D E L L O   S P A R O");

  // ERRORE: Coordinate dello sparo effettuato fuori dal campo di gioco, quindi
  // avvisa l'utente dell'errore e lo sparo è nullo
  if (x < 0 || y < 0 || x >= dimensioneGriglia || y >= dimensioneGriglia) {
    printCentered("||A T T E N Z I O N E||");
    printCentered("Coordinate dello sparo fuori dalla griglia di gioco! "
                  "Riprovare di nuovo...");
    return false;
  }

  // ERRORE: Coordinate dello sparo effettuato già in precedenza, quindi avvisa
  // l'utente dell'errore e lo sparo è nullo
  if (griglia[x][y] == Colpito || griglia[x][y] == Mancato) {
    printCentered("||A T T E N Z I O N E||");
    printCentered("Hai già sparato in queste coordinate, lo sparo è nullo! "
                  "Riprovare di nuovo...");
    return false;
  }

  // Segnala se è stata affondata una nave oppure è stata mancata. In entrambi i
  // casi, riaggiorna la griglia
  if (griglia[x][y] == NaveBattaglia) {
    std::cout << "\nBersaglio colpito! Ottimo lavoro comandante, continua così!!" << std::endl;

    griglia[x][y] = Colpito; // Assegnazione char di nave colpita
    naviRimaste--;           // Decremento contatore delle navi rimaste
    sparoNonSalvato = true;
    return true;
  } else {
    std::cout << "\nBersaglio mancato! Peccato comandante, potrai rifarti al "
                 "prossimo tentativo!"
              << std::endl;

    griglia[x][y]   = Mancato; // Assegnazione char di nave non colpita
    sparoNonSalvato = true;
  }

  return false;
}

// FUNZIONE ESCLUSIVA DELLA MODALITÀ MULTIPLAYER
bool CampoDiBattaglia::verificaSparoComputer(int x, int y) {
  // Segnala se è stata affondata una nave oppure è stato colpo mancato. In
  // entrambi i casi, riaggiorna il file
  if (griglia[x][y] == NaveBattaglia) {
    griglia[x][y] = Colpito; // Assegno char di nave colpita
    naviRimaste--;           // Decremento contatore delle navi rimaste
    sparoNonSalvato = true;
    return true;
  } else {
    griglia[x][y]   = Mancato; // Assegno char di nave non colpita
    sparoNonSalvato = true;
  }
  return false;
}

bool CampoDiBattaglia::tutteNaviAffondate() const {
  return naviRimaste == 0; // CONDIZIONE VITTORIA: Nessuna nave presente nel campo di battaglia
}

void CampoDiBattaglia::caricamentoFile() {
  std::string nomeFile;

  // Richiesta all'utente di inserire il file del file di salvataggio
  // precedentemente caricati
  std::cout << std::endl;
  printCentered("C A R I C A M E N T O   F I L E   D I   G I O C O");
  std::cout << "Inserisci il nome del file di salvataggio che desideri caricare: ";
  std::cin >> nomeFile;

  //CampoDiBattaglia* campo = new CampoIntermedio(0); // Puntatore temporaneo in quanto sarà aggiornato
                                                    // dal file di salvataggio
  caricaPartita(nomeFile);
}

bool CampoDiBattaglia::caricaPartita(const std::string& nomeFile) {
  std::ifstream file(nomeFile); // Apertura file in modalità lettura

  // Verifica se l'apertura del file è andata a buon fine, in caso contrario
  // stampa errore a schermo
  while (!file) {
    printCentered("*** E R R O R E ***");
    printCentered("Errore durante l'apertura del file di salvataggio, riprovare "
                  "inserendo un nome valido (verifica esista il file inserito)...");

    // Richiede di inserire un nome valido del file
    std::string nuovoNomeFile;
    std::cout << "\nInserisci nuovamente il nome del file di salvataggio "
                 "da caricare: ";
    std::cin >> nuovoNomeFile;

    // Tentativo di lettura del nuovo file
    file = std::ifstream(nuovoNomeFile);
  }

  file >> dimensioneGriglia; // Ottiene dimensione del file
  griglia.resize(dimensioneGriglia,
                 std::vector<char>(dimensioneGriglia)); // Ridimensiona la griglia

  for (int i = 0; i < dimensioneGriglia; ++i) {
    for (int j = 0; j < dimensioneGriglia; ++j) {
      file >> griglia[i][j]; // Lettura campo di battaglia su file

      if (griglia[i][j] == NaveBattaglia) {
        naviRimaste++; // Aumento contatore navi rimaste
      }
    }
  }
  file.close(); // Chiusura del file
  return true;  // Indica che l'apertura del file e il caricamento sono andati a
                // buon fine
}

void CampoDiBattaglia::salvaPartita() const {
  std::ofstream file("salvataggio.txt",
                     std::ios::trunc); // Scrittura su file (trunc serve per
                                       // eliminare contenuto precedente)

  // Verifica se l'apertura del file è andata a buon fine, in caso contrario
  // stampa errore a schermo
  if (!file) {
    printCentered("*** E R R O R E ***");
    printCentered("Errore durante il caricamento del salvataggio della partita...");
    return;
  }

  file << dimensioneGriglia << std::endl;

  for (int i = 0; i < dimensioneGriglia; ++i) {
    for (int j = 0; j < dimensioneGriglia; ++j) {
      file << griglia[i][j] << " ";
    }

    file << std::endl;
  }

  file.close();

  std::cout << std::endl;
  printCentered("S A L V A T A G G I O...");
  printCentered("I progressi della partita son stati salvati con successo!");
}

int CampoDiBattaglia::getDimensioneGriglia() const {
  return dimensioneGriglia;
}

char CampoDiBattaglia::getElementoGriglia(int x, int y) const {
  return griglia[x][y];
}

bool CampoDiBattaglia::getSparoNonSalvato() const {
  return sparoNonSalvato;
}

void CampoDiBattaglia::resetSparoNonSalvato() {
  sparoNonSalvato = false;
}

CampoDiBattaglia* creaCampo(int scelta, int dimensione) {
  // Iterazione switch che varia a seconda della scelta dell'utente
  switch (scelta) {
    // Creazione campo modalità principiante
    case 1:
      std::cout << std::endl;
      printCentered("P R I N C I P I A N T E");
      // Restituzione puntatore che punta al CampoPrincipiante
      return new CampoPrincipiante(dimensione);

    // Creazione campo modalità intermedio
    case 2:
      std::cout << std::endl;
      printCentered("I N T E R M E D I O");
      // Restituisce puntatore che punta al CampoIntermedio
      return new CampoIntermedio(dimensione);

    // Creazione campo modalità avanzato
    case 3:
      std::cout << std::endl;
      printCentered("A V A N Z A T O");
      // Restituisce puntatore che punta al CampoAvanzato
      return new CampoAvanzato(dimensione);

    // Se non si verifica nessuno dei 3 casi precedenti, avvisa all'utente della
    // scelta sbagliata
    default:
      printCentered("*** E R R O R E ***");
      printCentered("La scelta della modalità risulta essere incompatibile con "
                    "quelle presentate! Riprovare...");
      return nullptr;
  }
}

bool salvataggioProgressi(CampoDiBattaglia* campo) {
  char salva;
  bool salvaValido = false; // Variabile booleana che serve a non uscire dal ciclo do-while

  do {
    // Richiede all'utente di scegliere se salvare o meno lo sparo appena
    // effettuato
    std::cout << "\nVuoi salvare i progressi della partita fatta finora? (s/n): ";
    std::cin >> salva;

    salva = std::tolower(salva); // Conversione input utente in minuscolo per
                                 // evitare errori indesiderati

    // Verifica se lo sparo deve essere salvato sul file, se non deve essere
    // salvato o se l'input inserito non è valido
    if (salva == 's') {
      campo->salvaPartita();
      salvaValido = true;
    } else if (salva == 'n') {
      char esci;
      bool esciValido = false;

      do {
        // Richiede all'utente se ha intenzione di uscire dal gioco o continuare
        // (senza salvataggio dell'ultimo sparo effettuato)
        std::cout << "\nVuoi uscire dal gioco senza salvare? (s/n): ";
        std::cin >> esci;

        esci = std::tolower(esci); // Conversione input utente in minuscolo per
                                   // evitare errori indesiderati

        // Verifica se l'utente vuole uscire dal gioco, continuare (ma senza il
        // salvataggio dei progressi) oppure avvisare all'utente di input non
        // valido
        if (esci == 's') {
          std::cout << std::endl;
          printCentered("U S C I T A   I N   C O R S O...");
          delete campo; // Deallocazione di memoria
          return true;  // Ritorna positivo così da uscire dalle iterazioni
                        // do-while
        } else if (esci == 'n') {
          esciValido  = true;
          salvaValido = true;
        } else {
          printCentered("*** E R R O R E ***");
          printCentered("Opzione non valida, Assicurati di selezionare una delle "
                        "opzioni valide elencate precedentemente...");
        }
      } while (!esciValido);
    } else {
      printCentered("*** E R R O R E ***");
      printCentered("Opzione non valida, Assicurati di selezionare una delle "
                    "opzioni valide elencate precedentemente...");
    }
  } while (!salvaValido);

  campo->resetSparoNonSalvato(); // Puntatore punta al metodo di reset dello
                                 // sparo che non è stato salvato
  return false;                  // Indica che il programma può continuare
}

bool gestioneChiusura(CampoDiBattaglia* campo) {
  char termina;
  bool terminaValido = false;

  do {
    // Richiede all'utente se ha intenzione di uscire dal gioco o continuare
    // (senza salvataggio dell'ultimo sparo effettuato)
    std::cout << "\nVuoi uscire dal gioco? (s/n): ";
    std::cin >> termina;

    termina = std::tolower(termina); // Conversione input utente in minuscolo
                                     // per evitare errori indesiderati

    // Verifica se l'utente vuole uscire dal gioco, continuare (ma senza il
    // salvataggio dei progressi) oppure avvisare all'utente di input non valido
    if (termina == 's') {
      std::cout << std::endl;
      printCentered("U S C I T A   I N   C O R S O...");
      remove("salvataggio.txt"); // Rimuove il file di salvataggio poiché ormai
                                 // inutilizzabile
      delete campo;              // Deallocazione di memoria
      return false;              // Utente è intenzionato ad uscire dal programma
    } else if (termina == 'n') {
      return true; // Utente è intenzionato a continuare a giocare
    } else {
      printCentered("*** E R R O R E ***");
      printCentered("Opzione non valida, Assicurati di selezionare una delle "
                    "opzioni valide elencate precedentemente...");
    }
  } while (!terminaValido);

  return true; // Valore default qualora nessuna condizione viene accettata
}
