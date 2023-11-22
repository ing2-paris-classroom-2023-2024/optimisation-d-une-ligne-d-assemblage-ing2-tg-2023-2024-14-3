#ifndef ECELECAR_HEADER_GENERAL_H
#define ECELECAR_HEADER_GENERAL_H

// Espace des Bibliothèques :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// **********  MACROS   **********




// ********** STRUCTURE **********


typedef struct DATAS {
    int TCYCLE;         // Temps de Cycle
    int** EXCLUSIONS;    // Données d'exclusion
    int EXCLUSIONS_TOT;  // Nombre total d'exclusion
    int** PRECEDENCES;   // Données de précédence
    int PRECEDENCES_TOT; // Nombre total de precedence
    int** OPERATIONS ;   // Données d'opération
    int OPERATIONS_TOT;  // Nombre total d'operation
} DATAS;


typedef struct DATASET {
    int T_CYCLE;
    int TASK_TOT;
    struct TASK* TASKS;
} DATASET;
typedef struct TASK;
typedef struct TASK {
    int BASEID;
    int POIDS;
    struct TASK** P;
    int P_TOT;
    struct TASK** E;
    int E_TOT;
} TASK;




// **********  PROTOS   **********

// Protos de Chargement de Données
DATAS SCANDATAS(char* jeu_donnees);
int** FILLDATAS(char* fname, int* tot, int cond);
void DISPDATAS(DATAS datas);

// Protos de l'Ordonnancement des Données
DATASET DATASORT(DATAS datas);
void DISPDATASET(DATASET dataset);




#endif