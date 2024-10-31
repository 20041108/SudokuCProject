#ifndef SUDOKO_H_INCLUDED
#define SUDOKO_H_INCLUDED

//structure d'une cellule (une case) de la grille.
	struct cellule
	{
	   int valeur;
	   int estEditable;
	};
	typedef struct cellule Cell;

//structure d'une grille sudoku 9x9 (81 cases/cellules).
	struct grille
	{
	    Cell cell[9][9];
	};
	typedef struct grille Grid;

    void afficherGrille(Grid * grille);
    int verifierLigne(Grid * grille, int ligne);
    int verifierColonne(Grid * grille, int ligne);
    int verifierRegion(Grid * grille, int ligne, int colonne);
    int verifierGrille(Grid* grille);
    int enregistrerGrille(char * filename, Grid * grille);
    Grid * chargerGrille(char * filename);
    int progressionJeu(Grid * grid);
    int choisirGrille(char * filename, char * niveau);
    void choisirCellule(Grid * grille, int * lin, int * col);
    void remplirCellule(Grid * grille);
    Grid * remplirGrille(Grid * grille, int * progression, int * temps);
    void reglesSudoku();
    int  proposerAide(Grid * grille , int ligne, int colonne);
    void choix(char choix, char * pseudo);
    void menuSudoku();
    void initialisation(char * pseudo);
    int totalGrille(int niveau);

    int verifierCellule(Grid * grille, int num, int lin, int col);
    int resoudreSudoku(Grid * grille);

    void viderTampon();
    void clearBuffer();


#endif // SUDOKO_H_INCLUDED
