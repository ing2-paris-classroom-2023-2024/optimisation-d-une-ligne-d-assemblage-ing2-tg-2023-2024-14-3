#include "header_general.h"

DATAS SCANDATAS(char* jeu_donnees){
    //      -- FONCTION DE CHARGEMENT DES DONNEES
    //      JEU_DONNEES : Numéro du jeu de données
    //      || RETURN :     Structure de valeurs

    char* temp = (char*) malloc( 50*sizeof(char) );
    DATAS datas;

    printf("SCAN1\n");
    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "exclusions"); strcat(temp, ".txt");
    datas.EXCLUSIONS = FILLDATAS(temp, &(datas.EXCLUSIONS_TOT), 0);

    printf("SCAN2\n");
    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "precedences"); strcat(temp, ".txt");
    datas.PRECEDENCES = FILLDATAS(temp, &(datas.PRECEDENCES_TOT), 0);

    printf("SCAN3\n");
    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "operations"); strcat(temp, ".txt");
    datas.OPERATIONS = FILLDATAS(temp, &(datas.OPERATIONS_TOT), 1);

    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "temps_cycle"); strcat(temp, ".txt");
    FILE* fichier = fopen(temp, "rw+");
    if(!feof(fichier)) fscanf(fichier, "%d\n", &(datas.TCYCLE));
    datas.TCYCLE *= 1000;
    fclose(fichier);

    return datas;
}

int** FILLDATAS(char* fname, int* tot, int cond){
    FILE* fichier = fopen(fname, "rw+");
    *tot = 0;
    int** tab = (int**) malloc( sizeof(int*) );
    while(!feof(fichier)){
        tab = (int**) realloc( tab, (*tot+1)*sizeof(int*) );
        tab[*tot] = (int*) malloc( 2*sizeof(int) );
        if(cond) {
            double temp = 0.001;
            fscanf(fichier, "%d %lf\n", &(tab[*tot][0]), &(temp));
            tab[*tot][1] = (int) (temp * 1000);
        }
        else{
            fscanf(fichier, "%d %d\n", &(tab[*tot][0]), &(tab[*tot][1]));
        }
        //printf("VAL :\t%d\t%d\n", tab[*tot][0], tab[*tot][1]);
        (*tot)++;
    }
    fclose(fichier);
    printf("\n");
    return tab;
}

