#include "header_general.h"

DATAS SCANDATA(char* jeu_donnees){
    //      -- FONCTION DE CHARGEMENT DES DONNEES
    //      JEU_DONNEES : Numéro du jeu de données
    //      || RETURN :     Structure de valeurs

    char* temp = (char*) malloc( 20*sizeof(char) );
    DATAS datas; int count;

    strcpy(temp, "fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "exclusion"); strcat(temp, ".txt");
    FILE* fichier = fopen(temp, "rw+");
    count = 0;
    while(!feof(fichier)){
        datas.EXCLUSION = (DATA*) malloc( (count+1)*sizeof(DATA) );
        fscanf(fichier, "%d %d\n", &(datas.EXCLUSION[count].nb), &(datas.EXCLUSION[count].i));
        count++;
    }
    datas.EXCLUSION_TOT = count;

    return datas;
}