#include "header_general.h"

// Chargement de Données


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

void DISPDATAS(DATAS datas){
    printf("EXCLUSIONS :\n");
    for(int i = 0; i < datas.EXCLUSIONS_TOT; i++){
        printf("%d :\t%d\t%d\n", i, datas.EXCLUSIONS[i][0], datas.EXCLUSIONS[i][1]);
    }
    printf("\nPRECEDENCES :\n");
    for(int i = 0; i < datas.PRECEDENCES_TOT; i++){
        printf("%d :\t%d\t%d\n", i, datas.PRECEDENCES[i][0], datas.PRECEDENCES[i][1]);
    }
    printf("\nOPERATIONS :\n");
    for(int i = 0; i < datas.OPERATIONS_TOT; i++){
        printf("%d :\t%d\t%d\n", i, datas.OPERATIONS[i][0], datas.OPERATIONS[i][1]);
    }
    printf("\nTCYCLE : \n");
    printf("%d\n", datas.TCYCLE);
}



// Ordonnancement des Données


DATASET DATASORT(DATAS datas){
    DATASET dataset;

    // Remplissage du jeu de données initial
    dataset.TASK_TOT = 0;
    dataset.TASKS = (TASK*) malloc( dataset.TASK_TOT*sizeof(TASK) );
    for(int i = 0; i < datas.OPERATIONS_TOT; i++){
        dataset.TASKS = (TASK*) realloc(dataset.TASKS, (dataset.TASK_TOT+1)*sizeof(TASK) );
        dataset.TASKS[dataset.TASK_TOT].BASEID = datas.OPERATIONS[i][0];
        dataset.TASKS[dataset.TASK_TOT].POIDS = datas.OPERATIONS[i][1];
        dataset.TASKS[dataset.TASK_TOT].P_TOT = 0;
        dataset.TASKS[dataset.TASK_TOT].P = (TASK**) malloc( dataset.TASKS[dataset.TASK_TOT].P_TOT*sizeof(TASK*) );
        dataset.TASKS[dataset.TASK_TOT].E_TOT = 0;
        dataset.TASKS[dataset.TASK_TOT].E = (TASK**) malloc( dataset.TASKS[dataset.TASK_TOT].E_TOT*sizeof(TASK*) );
        dataset.TASK_TOT++;
    }
    dataset.T_CYCLE = datas.TCYCLE;

    // Ajout des précédents
    for(int i = 0; i < datas.PRECEDENCES_TOT; i++){
        TASK* LIGNE[2];
        for(int j = 0; j < dataset.TASK_TOT; j++){
            if(datas.PRECEDENCES[i][0] == dataset.TASKS[j].BASEID){
                LIGNE[0] = &(dataset.TASKS[j]);
            }
        }
        for(int j = 0; j < dataset.TASK_TOT; j++){
            if(datas.PRECEDENCES[i][1] == dataset.TASKS[j].BASEID){
                LIGNE[1] = &(dataset.TASKS[j]);
            }
        }

        LIGNE[0]->P = (TASK**) realloc(LIGNE[0]->P, (LIGNE[0]->P_TOT+1)*sizeof(TASK*));
        LIGNE[0]->P[LIGNE[0]->P_TOT] = LIGNE[1];
        LIGNE[0]->P_TOT++;
        //printf("TACHE %d :\tAntecedent -> %d \t(PTOT %d)\n", LIGNE[0]->BASEID, LIGNE[0]->P[LIGNE[0]->P_TOT-1]->BASEID, LIGNE[0]->P_TOT);
    }

    //Ajout des exclusions
    for(int i = 0; i < datas.EXCLUSIONS_TOT; i++){
        TASK* LIGNE[2];
        for(int j = 0; j < dataset.TASK_TOT; j++){
            if(datas.EXCLUSIONS[i][0] == dataset.TASKS[j].BASEID){
                LIGNE[0] = &(dataset.TASKS[j]);
            }
        }
        for(int j = 0; j < dataset.TASK_TOT; j++){
            if(datas.EXCLUSIONS[i][1] == dataset.TASKS[j].BASEID){
                LIGNE[1] = &(dataset.TASKS[j]);
            }
        }
        LIGNE[0]->E = (TASK**) realloc(LIGNE[0]->E, (LIGNE[0]->E_TOT+1)*sizeof(TASK*));
        LIGNE[0]->E[LIGNE[0]->E_TOT] = LIGNE[1];
        LIGNE[0]->E_TOT++;
        //printf("TACHE %d :\tExclut -> %d \t(ETOT %d)\n", LIGNE[0]->BASEID, LIGNE[0]->E[LIGNE[0]->E_TOT-1]->BASEID, LIGNE[0]->E_TOT);
        LIGNE[1]->E = (TASK**) realloc(LIGNE[1]->E, (LIGNE[1]->E_TOT+1)*sizeof(TASK*));
        LIGNE[1]->E[LIGNE[1]->E_TOT] = LIGNE[0];
        LIGNE[1]->E_TOT++;
        //printf("TACHE %d :\tExclut -> %d \t(ETOT %d)\n", LIGNE[1]->BASEID, LIGNE[1]->E[LIGNE[1]->E_TOT-1]->BASEID, LIGNE[1]->E_TOT);
    }

    return dataset;
}

void DISPDATASET(DATASET dataset){
    printf("Tâches (TTOT : %d) :\n", dataset.TASK_TOT);
    for(int i = 0; i < dataset.TASK_TOT; i++){
        printf("\tTache n°%d :\n");
        printf("\t\tPrécédents (PTOT : %d) : ", dataset.TASKS[i].P_TOT);
        for(int j = 0; j < dataset.TASKS[i].P_TOT; j++){
            printf("%d, ", dataset.TASKS[i].P[j]->BASEID);
        }
        printf("\n");
        printf("\t\tExclusions (ETOT : %d) : ", dataset.TASKS[i].E_TOT);
        for(int j = 0; j < dataset.TASKS[i].E_TOT; j++){
            printf("%d, ", dataset.TASKS[i].E[j]->BASEID);
        }
        printf("\n");
    }
}



