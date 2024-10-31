#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include "sudoku.h"

int chercherGrille(char * filename, int * type);
int numeroGrille(int niveau);
void nombreGrilles(int niveau);
Grid * creerGrille();
Grid * importerGrille();
Grid * genererGrilleRemplie();
Grid * modifierGrille(Grid * grille);
void choixMenuAdmin(char choix);
int validerFichier(char * filename);

void menuAdmin();
void clearBuffer();
#endif 
