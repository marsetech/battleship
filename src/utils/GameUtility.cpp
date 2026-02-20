#include "field/BattleField.h"
#include "modes/AdvancedField.h"
#include "modes/IntermediateField.h"
#include "utils/GameUtils.h"

void benvenuto() {
    std::cout << std::endl << std::endl;
    printCentered("B A T T A G L I A   N A V A L E");
    printCentered("Benvenuto al famoso gioco di Battaglia Navale");
    printCentered("T I P S: Prima di iniziare, leggi attentamente il regolamento\n");
}

void regolamento() {
    // Funzione (con fine esclusivamente estetico) che spiega le regole da seguire
    // durante il gioco
    std::cout << std::endl << std::endl;
    printCentered("R E G O L A M E N T O   D E L   G I O C O");
    std::cout << "1. Il campo di battaglia sarà il tuo capitano, dagli fiducia o "
                 "rischierai di sprofondare!"
              << std::endl;
    std::cout << "2. Il file di salvataggio NON deve essere aperto! Non barare, "
                 "ti vedo!!!"
              << std::endl;
    std::cout << "3. Una volta posizionate le mani, non potranno essere "
                 "modificate le loro posizioni. Decidi saggiamente!"
              << std::endl;
    std::cout << "4. I progressi non salvati potrebbero andare persi, sii cauto "
                 "con le tue scelte."
              << std::endl;
    std::cout << std::endl;
    printCentered("B U O N   D I V E R T I M E N T O");
    printCentered("----------------------------------------------------------");
}

int selezioneDifficolta() {
    std::string input;
    int         sceltaDifficolta;
    bool        difficoltaValida;

    // Richiede all'utente di inserire la difficoltà tramite input valido
    do {
        std::cout << std::endl;
        printCentered("D I F F I C O L T À");
        std::cout << "\nSelezionare una delle seguenti opzioni (La selezione della "
                     "difficoltà influenza sulla modalità di gioco): "
                  << std::endl;
        std::cout << "(1) Principiante: Deciderai tu dove le navi sono posizionate. "
                     "Troppo facile, vero?"
                  << std::endl;
        std::cout << "(2) Intermedio: Le navi saranno disposte in posizioni random lungo "
                     "il campo da gioco. Sii cauto e distruggi la flotta, capitano."
                  << std::endl;
        std::cout << "(3) Avanzato: Le navi rimanenti si muoveranno ogni volta che "
                     "ne affonderai una. Fai attenzione!"
                  << std::endl;
        std::cout << "(4) O P Z I O N A L E: Caricare il risultato dal salvataggio "
                     "della partita precedente."
                  << std::endl;
        std::cout << "(5) Multiplayer (Giocatore vs AI)." << std::endl;
        std::cout << "\nDifficoltà selezionata dall'utente: ";
        std::cin >> input;

        // Verifica se l'input è composto solo da cifre numeriche o sono presenti
        // caratteri (input non valido)
        bool isNumber = !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);

        // Verifica se input è un numero e lo converte in un intero
        if (isNumber) {
            sceltaDifficolta = std::stoi(input);
            difficoltaValida = (sceltaDifficolta >= 1 && sceltaDifficolta <= 5);
        } else {
            difficoltaValida = false; // Qualora la difficoltà inserita non è valida, avvisa
                                      // all'utente dell'input inserito non valido
            printCentered("*** E R R O R E ***");
            printCentered("Opzione non valida, Assicurati di selezionare una delle "
                          "opzioni valide elencate precedentemente...");
        }
    } while (!difficoltaValida);

    return sceltaDifficolta;
}

int inserimentoDimensioni() {
    std::string input;
    int         dimensione;
    bool        dimensioneValida;

    do {
        std::cout << std::endl;
        // Programma chiede all'utente di inserire una dimensione adatta
        printCentered("D I M E N S I O N E   D E L   C A M P O");
        std::cout << "\nInserisci la dimensione del campo di combattimento: ";
        std::cin >> input;

        // Verifica singolarmente se tutti i caratteri delle dimensioni inserite
        // sono numeri
        bool isNumber = !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);

        // Se l'input è numerico, lo converte in un intero altrimenti rileva input
        // non valido
        if (isNumber) {
            dimensione       = std::stoi(input); // Conversione carattere input in un intero
            dimensioneValida = dimensione >= 2;  // Verifica che sia dimensione
                                                 // corretta
        } else {
            dimensioneValida = false;
        }

        // Verifica se la difficoltà non è valida e avvisa l'utente con errore a
        // schermo
        if (!dimensioneValida) {
            printCentered("*** E R R O R E ***");
            printCentered("Opzione non valida, selezionare dimensione del campo "
                          "adeguata (dimensione necessariamente maggiore o uguale di 2");
        }
    } while (!dimensioneValida);

    return dimensione;
}

void Partita() {
    bool continuaGioco = true; // Variabile booleana per controllare se l'utente
                               // vuole continuare a giocare

    do {
        // Funzione che richiede all'utente di inserire la difficoltà tramite input
        // valido
        int sceltaDifficolta = selezioneDifficolta();

        CampoDiBattaglia* campo = nullptr; // Definizione puntatore che non punta a niente per evita che
                                           // punti a segmenti di memoria inutilizzati
        int dimensione = 0;                // Inizializzione la dimensione della griglia di gioco

        // Iterazioni che variano in base alla scelta dell'utente
        if (sceltaDifficolta == 4) {
            campo = new CampoIntermedio(dimensione);    // Crea dimensione del campo (PRIMA: 0)
            campo->caricamentoFile();                   // Puntatore che carica i salvataggi sul file
            dimensione = campo->getDimensioneGriglia(); // Riaggiorna dimensione del file
                                                        // (DOPO: dimensione scelta da utente)
        } else if (sceltaDifficolta == 5) {
            PartitaMultiplayer(); // Richiama la funzione riservata al multiplayer
            continuaGioco = false;
            // continue; // Usa continue per saltare il resto del ciclo e riprendere
            // la prossima iterazione
        } else {
            dimensione = inserimentoDimensioni(); // Richiama funzione per
            campo      = creaCampo(sceltaDifficolta,
                                   dimensione); // Puntatore assegnato al metodo di creazione del campo
        }

        // Verifica che la creazione del campo è avvenuta correttamente, in caso
        // contrario avvisa all'utente con errore a schermo
        if (!campo) {
            printCentered("*** E R R O R E ***");
            printCentered("Errore durante la creazione del campo di battaglia! Riprovare...");
            return;
        }

        campo->posizionaNavi();      // Puntatore richiama metodo di posizionare navi
                                     // (varia in base alla scelta fatta)
        campo->stampaGriglia(false); // Puntatore richiama metodo di stampare campo
                                     // senza mostrare navi

        // Verifica che si assicura ALMENO una nave è presente per far sì che non
        // finisca la partita
        while (!campo->tutteNaviAffondate()) {
            campo->gestioneSparo(); // Puntatore richiama metodo di gestione (CON
                                    // VERIFICA) del colpo
            campo->stampaGriglia(); // Puntatore richiama metodo di stampare la
                                    // griglia (aggiornata dopo lo sparo)

            // Verifica se SIMULTANEAMENTE è stata scelta difficoltà 3 e l'ultimo
            // sparo non è stato ancora salvato
            if (sceltaDifficolta == 3 && campo->getSparoNonSalvato()) {
                CampoAvanzato* campoAvanzato =
                    dynamic_cast<CampoAvanzato*>(campo); // Trasformazione puntatore CampoDiBattaglia a CampoAvanzato
                                                         // dinamicamente

                // Verifica se campo è diventato oggetto di CampoAvanzato
                if (campoAvanzato) {
                    campoAvanzato->muoviNavi(); // Puntatore richiama metodo di spostamento navi
                                                // (ESCLUSIVA modalità avanzata)
                    std::cout << "Le navi avversarie si sono mosse!" << std::endl;
                }
            }

            // Verifica se lo sparo non è salvato affinché l'utente decida se salvarlo
            // o meno
            if (campo->getSparoNonSalvato()) {
                // Verifica il valore di ritorno del metodo di gestione del salvataggio
                // del colpo
                if (salvataggioProgressi(campo)) {
                    return; // Se la funzione per salvare i progressi ritorna true,
                            // termina il programma
                }
            }

            // Verifica che tutte le navi sono state affondate mandando a schermo il
            // messaggio di vittoria all'utente in caso affermativo
            if (campo->tutteNaviAffondate()) {
                std::cout << std::endl << std::endl;
                printCentered("C O N G R A T U L A Z I O N I");
                printCentered("Hai vinto il gioco della Battaglia Navale!");

                continuaGioco = gestioneChiusura(campo); // Richiama funzione necessaria a

                // Verifica la chiamata della funzione (Se return false, elimina
                // puntatore ed esce dal gioco)
                if (!continuaGioco) {
                    delete campo; // Deallocazione della memoria
                    return;
                }
            }
        }
    } while (continuaGioco);
}

void PartitaMultiplayer() {
    bool rigioca = false; // Variabile booleana per controllare se l'utente vuole rigiocare

    do {
        int dimensione = inserimentoDimensioni();

        // Creazione campo di battaglia per utente ed AI (con difficoltà intermedia
        // per sfruttare posizionamento casuale delle navi)
        CampoDiBattaglia* campoUtente = creaCampo(2, dimensione);
        CampoDiBattaglia* campoIA     = creaCampo(2, dimensione);

        // Verifica se la creazione del campo è avvenuta correttamente stampando a
        // schermo, in caso contrario, messaggio di errore per avvisare utente
        if (!campoUtente || !campoIA) {
            printCentered("*** E R R O R E ***");
            printCentered("Errore durante la creazione del campo di battaglia "
                          "multigiocatore! Riprovare...");
            return;
        }

        campoUtente->posizionaNavi(); // Puntatore Utente che richiama metodo di
                                      // posizionamento navi
        campoIA->posizionaNavi();     // Puntatore AI che richiama metodo di
                                      // posizionamento navi

        campoUtente->stampaGriglia(false); // Puntatore Utente che richiama metodo stampa la griglia (senza
                                           // mostrare posizione navi)
        campoIA->stampaGriglia(false);     // Puntatore AI che richiama metodo stampa la
                                           // griglia (senza mostrare posizione navi)

        bool turnoUtente = true;  // Variabile booleana per indicare il turno dell'utente
        bool gameOver    = false; // Variabile booleana per indicare la fine del gioco

        do {
            if (turnoUtente) {
                int  x, y;
                bool coordinateValide = false; // Variabile booleana per controllare le
                                               // coodinate dello sparo

                do {
                    std::string inputX, inputY;

                    // Richiesta inserimento coordinate con il controllo della validità
                    std::cout << std::endl;
                    printCentered("P R E P A R A T I V I   P E R   L O   S P A R O   I "
                                  "N   C O R S O...");
                    printCentered("Mi raccomando! Ricorda di inserire lo spazio tra le "
                                  "due coordinate");
                    std::cout << "Inserire le coordinate (x y) dello sparo da effettuare: ";
                    std::cin >> inputX >> inputY;

                    // Verifica se l'input per coordinate X,Y è composto solo da cifre
                    // numeriche o sono presenti caratteri (input non valido)
                    bool isNumberX = !inputX.empty() && std::all_of(inputX.begin(), inputX.end(), ::isdigit);
                    bool isNumberY = !inputY.empty() && std::all_of(inputY.begin(), inputY.end(), ::isdigit);

                    // Se l'input sono valori numerici, input convertito in variabile
                    // intera altrimenti avvisa all'utente di input non valido
                    if (isNumberX && isNumberY) {
                        x                = std::stoi(inputX);
                        y                = std::stoi(inputY);
                        coordinateValide = true;
                    } else {
                        printCentered("*** E R R O R E ***");
                        printCentered("Coordinate non valide, assicurati di inserire due "
                                      "numeri interi...");
                    }
                } while (!coordinateValide);

                campoIA->verificaSparo(x, y); // Puntatore richiama metodo di verifica
                                              // che il colpo sia andato a buon fine
                campoIA->stampaGriglia();     // Puntatore richiama metodo di stampa della
                                              // griglia di gioco dell'IA

                // Verifica che il campo di gioco dell'AI sia vuoto di navi mandando a
                // schermo vittoria dell'utente in caso affermativo
                if (campoIA->tutteNaviAffondate()) {
                    std::cout << std::endl;
                    printCentered("C O N G R A T U L A Z I O N I");
                    printCentered("Hai vinto il gioco della Battaglia Navale!");

                    char risposta;
                    // Richiede all'utente se vuole ricominciare la partita o uscire
                    std::cout << "\nVuoi giocare di nuovo? (s/n): ";
                    std::cin >> risposta;

                    risposta = std::tolower(risposta);

                    if (risposta == 's') {
                        rigioca  = true; // Riavvia il ciclo esterno per rigiocare
                        gameOver = true; // Termina la partita attuale
                    } else {
                        rigioca  = false;
                        gameOver = true; // Termina il gioco completamente
                    }
                } else {
                    turnoUtente = false; // Passa il turno all'IAs
                }
            } else {
                int xAI, yAI;

                // Genera coordinate casuali per lo sparo dell'AI, verificando che tale
                // numero sia compreso nella griglia
                xAI = rand() % dimensione; // CoordinataX: valore [0,dimensioneCampo-1]
                yAI = rand() % dimensione; // CoordinataY: valore [0,dimensioneCampo-1]

                campoUtente->verificaSparoComputer(xAI, yAI); // Puntatore richiama metodo per verificare che il colpo
                                                              // sia andato a segno

                std::cout << "\nIl computer ha sparato nelle coordinate: ( " << xAI << ", " << yAI << " )" << std::endl;
                campoUtente->stampaGriglia(); // Stampa la griglia dell'utente
                                              // aggiornata dopo lo sparo dell'AI

                // Verifica che il campo di gioco dell'utente sia vuoto di navi mandando
                // a schermo vittoria dell'AI in caso affermativo
                if (campoUtente->tutteNaviAffondate()) {
                    std::cout << std::endl;
                    printCentered("H A I   P E R S O!");
                    printCentered("L'AI ha vinto!, Peccato, potrai rifarti la prossima volta...");
                    gameOver = true; // Termina il gioco completamente
                    rigioca  = false;
                } else {
                    turnoUtente = true; // Passaggio del turno all'utente
                }
            }
        } while (!gameOver);

        // Deallocazione di memoria dei puntatori creati in precedenza
        delete campoUtente;
        delete campoIA;

    } while (rigioca);
}

int parseTerminalSize(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return 80;
    }
    return cols;
}

int getTerminal() {
    int cols = 80; // fallback sicuro

    if (isatty(fileno(stdin))) {
        int   rows;
        FILE* term = popen("stty size", "r");
        if (term) {
            if (fscanf(term, "%d %d", &rows, &cols) != 2) {
                cols = 80; // fallback se fscanf fallisce
            }
            pclose(term);
        }
    }

    if (cols <= 0) cols = 80; // fallback
    return cols;
}

void printCentered(const std::string& text) {
    int lunghezza = getTerminal();
    // Calcola spazi vuoti prima del testo e lo centra con fratto 2
    int spazi = (lunghezza - text.size()) / 2;

    // Se lo spazio è positivo, stampa testo con spazio a destra e sinistra
    if (spazi > 0) {
        // Centra il testo nello spazio che ha a disposizione nel terminale
        std::cout << std::setw(spazi + text.size()) << text << std::endl;
    } else {
        // Stampa direttamente il testo nel caso di testo>larghezza terminale
        std::cout << text << std::endl;
    }
}
