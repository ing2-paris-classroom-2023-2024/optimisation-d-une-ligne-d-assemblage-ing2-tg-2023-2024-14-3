#include "header_general.h"

DATAS SCANDATAS(char* jeu_donnees){
    //      -- FONCTION DE CHARGEMENT DES DONNEES
    //      JEU_DONNEES : Numéro du jeu de données
    //      || RETURN :     Structure de valeurs

    char* temp = (char*) malloc( 50*sizeof(char) );
    DATAS datas; int count; FILE* fichier;

    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "exclusions"); strcat(temp, ".txt");
    fichier = fopen(temp, "rw+");
    datas.EXCLUSIONS_TOT = 0;
    datas.EXCLUSIONS = (int**) malloc( sizeof(int*) );
    while(!feof(fichier)){
        datas.EXCLUSIONS = (int**) realloc( datas.EXCLUSIONS, (datas.EXCLUSIONS_TOT+1)*sizeof(int*) );
        datas.EXCLUSIONS[datas.EXCLUSIONS_TOT] = (int*) malloc( 2*sizeof(int) );
        fscanf(fichier, "%d %d\n", &(datas.EXCLUSIONS[datas.EXCLUSIONS_TOT][0]), &(datas.EXCLUSIONS[datas.EXCLUSIONS_TOT][1]));
        datas.EXCLUSIONS_TOT++;
    }
    fclose(fichier);

    fichier = fopen(temp, "rw+");
    datas.PRECEDENCES_TOT = 0;
    datas.PRECEDENCES = (int**) malloc( sizeof(int*) );
    while(!feof(fichier)){
        datas.PRECEDENCES = (int**) realloc( datas.PRECEDENCES, (datas.PRECEDENCES_TOT+1)*sizeof(int*) );
        datas.PRECEDENCES[datas.PRECEDENCES_TOT] = (int*) malloc( 2*sizeof(int) );
        fscanf(fichier, "%d %d\n", &(datas.PRECEDENCES[datas.PRECEDENCES_TOT][0]), &(datas.PRECEDENCES[datas.PRECEDENCES_TOT][1]));
        printf("TEST : %d %d\n", datas.PRECEDENCES[datas.PRECEDENCES_TOT][0], datas.PRECEDENCES[datas.PRECEDENCES_TOT][1]);
        datas.PRECEDENCES_TOT++;
    }
    fclose(fichier);

    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "operations"); strcat(temp, ".txt");
    datas.OPERATIONS_TOT = 0;
    datas.OPERATIONS = (int**) malloc( sizeof(int*) );
    while(!feof(fichier)){
        datas.OPERATIONS = (int**) realloc( datas.OPERATIONS, (datas.OPERATIONS_TOT+1)*sizeof(int*) );
        datas.OPERATIONS[datas.OPERATIONS_TOT] = (int*) malloc( 2*sizeof(int) );
        float temp = 0.0;
        fscanf(fichier, "%d %f\n", &(datas.OPERATIONS[datas.OPERATIONS_TOT][0]), &(temp));
        datas.OPERATIONS[datas.OPERATIONS_TOT][1] = (int)(temp*1000);
        datas.OPERATIONS_TOT++;
    }
    fclose(fichier);

    strcpy(temp, "../fichiers_ressources/"); strcat(temp, jeu_donnees); strcat(temp, "/"); strcat(temp, "temps_cycle"); strcat(temp, ".txt");
    fichier = fopen(temp, "rw+");
    fscanf(fichier, "%d", &(datas.TCYCLE));
    datas.TCYCLE = (int)(datas.TCYCLE*1000);
    fclose(fichier);

    return datas;
}

int** FILLINDATAS(char* fname, int* tot, int cond){

}

