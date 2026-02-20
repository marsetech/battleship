#ifndef ESTETICA_H
#define ESTETICA_H

#include "GameCore.h"

void benvenuto();
void regolamento();
int selezioneDifficolta();
int inserimentoDimensioni();
void Partita();
void PartitaMultiplayer();

int parseTerminalSize(int rows, int cols);
int getTerminal();
void printCentered(const std::string &text);

#endif
