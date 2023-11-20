#include "header_general.h"

DATAS SCANDATA(char* jeu_donnees){
    //      -- FONCTION DE CHARGEMENT DES DONNEES
    //      JEU_DONNEES : Numéro du jeu de données
    //      || RETURN :     Structure de valeurs

    char* temp = (char*) malloc( 50*sizeof(char) );
    DATAS datas; int count; FILE* fichier;

    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "exclusions"); strcat(temp, ".txt");
    fichier = fopen(temp, "rw+");
    count = 0;
    datas.EXCLUSION = (DATA*) malloc( sizeof(DATA) );
    while(!feof(fichier)){
        datas.EXCLUSION = (DATA*) realloc( datas.EXCLUSION, (count+1)*sizeof(DATA) );
        fscanf(fichier, "%d %d\n", &(datas.EXCLUSION[count].nb), &(datas.EXCLUSION[count].i));
        count++;
    }
    datas.EXCLUSION_TOT = count;
    fclose(fichier);

    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "precedences"); strcat(temp, ".txt");
    fichier = fopen(temp, "rw+");
    count = 0;
    datas.PRECEDENCE = (DATA*) malloc( sizeof(DATA) );
    while(!feof(fichier)){
        datas.PRECEDENCE = (DATA*) realloc( datas.PRECEDENCE, (count+1)*sizeof(DATA) );
        fscanf(fichier, "%d %d\n", &(datas.PRECEDENCE[count].nb), &(datas.PRECEDENCE[count].i));
        count++;
    }
    datas.PRECEDENCE_TOT = count;
    fclose(fichier);

    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "operations"); strcat(temp, ".txt");
    fichier = fopen(temp, "rw+");
    count = 0;
    datas.OPERATION = (DATA*) malloc( sizeof(DATA) );
    while(!feof(fichier)){
        datas.OPERATION = (DATA*) realloc( datas.OPERATION, (count+1)*sizeof(DATA) );
        fscanf(fichier, "%d %f\n", &(datas.OPERATION[count].nb), &(datas.OPERATION[count].f));
        count++;
    }
    datas.OPERATION_TOT = count;
    fclose(fichier);

    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "temps_cycle"); strcat(temp, ".txt");
    fichier = fopen(temp, "rw+");
    fscanf(fichier, "%d", &(datas.TCYCLE));
    fclose(fichier);

    return datas;
}