#include <stdio.h>
#include <stdlib.h>


#include <string.h>
#include "partie.h"

void afficherSudoku(){
    printf( "\n\n\t\t\t  ||    /******  /**   /** /*******   /******  /**   /** /**   /** || \n");
    printf( "\t\t\t  ||   /**__  **| **  | **| **__  ** /**__  **| **  /**/| **  | ** ||  \n");
    printf("\t\t\t  ||  | **  \\__/| **  | **| **  \\ **| **  \\ **| ** /**/ | **  | ** ||  \n");
    printf("\t\t\t  ||  |  ****** | **  | **| **  | **| **  | **| *****/  | **  | ** ||  \n");
    printf("\t\t\t  ||   \\____  **| **  | **| **  | **| **  | **| **  **  | **  | ** ||   \n");
    printf("\t\t\t  ||   /**  \\ **| **  | **| **  | **| **  | **| **\\  ** | **  | ** ||  \n");
    printf("\t\t\t  ||  |  ******/|  ******/| *******/|  ******/| ** \\  **|  ******/ ||  \n");
    printf("\t\t\t  ||   \\______/  \\______/ |_______/  \\______/ |__/  \\__/ \\______/  ||   \n\n" );
}

int verifierPseudo(char * pseudo){
    size_t i;
    if(strlen(pseudo) < 3) return 0;
    if(strlen(pseudo) > 15) return 0;
    for(i = 0; i < strlen(pseudo); i++) {
        if(pseudo[i] == ' ') return 0;
    }
    return 1;
}

int ajouterStatistique(Partie * partie, char * filename){
    FILE * fich = fopen(filename, "a");
    if(fich == NULL) return 0;
    fprintf(fich, "%d %s %s %d %d\n", partie->id, partie->joeur, partie->niveau, partie->temps, partie->progression);
    fclose(fich);
    return 1;
}

int modifierStatistique(Partie * partie){
    Partie part;
    FILE * fich = fopen("statistiques", "r");
    int cmpt = 0, ligne;
    if(fich == NULL) return 0;

    ligne = chercherJoueur(partie->joeur);
    if(ligne == 0) return 0;

    while(!feof(fich)){
       cmpt++;
       fscanf(fich, "%d %s %s %d %d\n", &part.id, part.joeur, part.niveau, &part.temps, &part.progression);
       if(strcmp(part.joeur, partie->joeur) == 0 && cmpt == ligne) {
            strcpy(partie->niveau, part.niveau);
            partie->temps += part.temps;
            partie->id = part.id;
            ajouterStatistique(partie, "copieStatistiques");
       } else {
            ajouterStatistique(&part, "copieStatistiques");
       }
    }
    fclose(fich);
    remove("statistiques");
    rename("copieStatistiques", "statistiques");
    return 1;
}

void afficherStatistiques(){
    Partie partie;
    FILE * fich = fopen("statistiques", "r");
    int secondes = 0, minutes = 0, heures = 0;
    char temps[20], progression[10];
    afficherSudoku();
    if(fich == NULL){
        printf("\n\t\t\t Alerte : aucune statistique n'a ete enregistree jusqu'au present !\n");
        return;
    }
    printf("\n\t|----------------------|----------------------|----------------------|----------------------|\n");
    printf("\t| %-20s | %-20s | %-20s | %-20s |\n", "Joueur", "Niveau", "Temps", "Progression");
    printf("\t|----------------------|----------------------|----------------------|----------------------|\n");
    while(!feof(fich)){
       fscanf(fich, "%d %s %s %d %d\n", &partie.id, partie.joeur, partie.niveau, &partie.temps, &partie.progression);
       formatTemps((int)partie.temps, &heures, &minutes, &secondes);
       sprintf(temps, "%d h %d min %d s", heures, minutes, secondes);
       sprintf(progression, "%d/81", partie.progression);
       printf("\t| %-20s | %-20s | %-20s | %-20s |\n", partie.joeur, partie.niveau, temps, progression);
    }
    printf("\n\t|----------------------|----------------------|----------------------|----------------------|\n");
    fclose(fich);
}

int chercherStatistique(char * pseudo){
    Partie partie;
    int boolean = 0, secondes = 0, minutes = 0, heures = 0;
    FILE * fich = fopen("statistiques", "r");
    char temps[20], progression[10];
    afficherSudoku();
    if(fich == NULL){
        printf("\n\n\t\t\t Alerte : aucune statistique n'a ete etablie pour vous !\n");
        return 0;
    }
    printf("\n\t|----------------------|----------------------|----------------------|----------------------|\n");
    printf("\t| %-20s | %-20s | %-20s | %-20s |\n", "Joueur", "Niveau", "Temps", "Progression");
    printf("\t|----------------------|----------------------|----------------------|----------------------|\n");
    while(!feof(fich)){
       fscanf(fich, "%d %s %s %d %d\n", &partie.id, partie.joeur, partie.niveau, &partie.temps, &partie.progression);
       if(strcmp(partie.joeur, pseudo) == 0){
           formatTemps((int)partie.temps, &heures, &minutes, &secondes);
           sprintf(temps, "%d h %d min %d s", heures, minutes, secondes);
           sprintf(progression, "%d/81", partie.progression);
           printf("\t| %-20s | %-20s | %-20s | %-20s |\n", partie.joeur, partie.niveau, temps, progression);
           boolean = 1;
       }
    }
    printf("\n\t|----------------------|----------------------|----------------------|\n");
    if(boolean != 1){
       system("cls");
       afficherSudoku();
       printf("\n\n\t\t\t --------- Aucune statistique n'a ete enregistre pour vous ! --------- \n");
    }
    fclose(fich);
    return 1;
}

int chercherJoueur(char * pseudo){
    Partie part;
    FILE * fich = fopen("statistiques", "r");
    int i = 0, j = 0;
    if(fich == NULL) return 0;
    while(!feof(fich)){
       fscanf(fich, "%d %s %s %d %d\n", &part.id, part.joeur, part.niveau, &part.temps, &part.progression);
       j++;
       if(strcmp(part.joeur, pseudo) == 0){
            i += j;   
            j = 0;
       }
    }
    fclose(fich);
    return i;
}

void formatTemps(int duree, int * heures, int * minutes, int * secondes){
    *heures = duree / 3600; // 1 heure = 3600 secondes
    *minutes = (duree % 3600) / 60; // 1 minute = 60 secondes
    *secondes = duree % 60;
}

int totalParties(char * pseudo){
    Partie part;
    FILE * fich = fopen("statistiques", "r");
    int i = 0;
    if(fich == NULL) return 0;
    while(!feof(fich)){
       fscanf(fich, "%d %s %s %d %d\n", &part.id, part.joeur, part.niveau, &part.temps, &part.progression);
       if(strcmp(part.joeur, pseudo) == 0){
            i += 1;
       }
    }
    fclose(fich);
    return i;
}

int choisirPartie(char * filename, char * pseudo){
    FILE * fich = NULL;
    Partie partie;
    int i = 0, MAX = totalParties(pseudo);
    if(MAX == 0) return 0;
    int TAB[MAX];
    char id[10];
    do{
        system("cls");
        fich = fopen("statistiques", "r");
        printf("\n\t|----------------------|----------------------|----------------------|\n");
        printf("\t| %-20s | %-20s | %-20s |\n", "numero", "Joueur", "Niveau");
        printf("\t|----------------------|----------------------|----------------------|\n");
        while(!feof(fich)){
           fscanf(fich, "%d %s %s %d %d\n", &partie.id, partie.joeur, partie.niveau, &partie.temps, &partie.progression);
           if(strcmp(partie.joeur, pseudo) == 0){
               printf("\t| %-20d | %-20s | %-20s |\n", partie.id, partie.joeur, partie.niveau);
               TAB[i++] = partie.id;
           }
        }
        fclose(fich);
        printf("\n\t|----------------------|----------------------|----------------------|\n");
        printf("\n\t Entrez .0. pour retourner au menu principal \n");
        printf("\n\t Entrez le numero correspondant au partie que vous voulez continuer > ");
        fflush(stdin);
        scanf("%s", id);
    } while(!verifierIdPartie(TAB, MAX, id));
    if(strcmp(id, "0") == 0){
        return 2;
    }
    sprintf(filename, "%s %s", pseudo, id);
    return 1;
}

int verifierIdPartie(int * tab, int taille, char * saisie){
    size_t i;
    if(strlen(saisie) == 1 && saisie[0] == '0') return 1;  // condition for exit
    for(i = 0; i < strlen(saisie); i++){
        if(saisie[i] > '9' || saisie[i] < '0') return 0;
    }
    int j;
    for(j = 0;  j < taille; j++){
        if(tab[j] == atoi(saisie))  return 1;
    }
    return 0;
}

