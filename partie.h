#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

struct partie{
    int id;
    char joeur[62];
    char niveau[32];
    int temps;
    int progression;
};
typedef struct partie Partie;

void afficherSudoku();
int verifierPseudo(char * pseudo);
int ajouterStatistique(Partie * partie , char * filename);
int modifierStatistique(Partie * partie);
void afficherStatistiques();
int chercherStatistique(char * pseudo);
int chercherJoueur(char * pseudo);
void formatTemps(int duree, int * heures, int * minutes, int * secondes);

//new version
    int totalParties(char * pseudo);
    int choisirPartie(char * filename, char * pseudo);
    int verifierIdPartie(int * tab, int taille, char * saisie);

#endif // PARTIE_H_INCLUDED
