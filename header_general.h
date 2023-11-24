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
    int TCYCLE;          // Temps de Cycle
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
    int TEMPS_EXE;
    bool USED;
    struct TASK** P;    // Tableau des Précédents
    int P_TOT;
    struct TASK** S;    // Tableau des Successeurs
    int S_TOT;
    struct TASK** E;    // Tableau des Exclusions
    int E_TOT;
} TASK;

typedef struct STATION{
    int id;
    int temps_tot;
    int ind_tab;
    struct TASK** actions;
}STATION;




// **********  PROTOS   **********

// Protos de Chargement de Données
DATAS SCANDATAS(char* jeu_donnees);
int** FILLDATAS(char* fname, int* tot, int cond);
void DISPDATAS(DATAS datas);
void FREEDATAS(DATAS datas);

// Protos de l'Ordonnancement des Données
DATASET DATASORT(DATAS datas);
void DISPDATASET(DATASET dataset);
void FREEDATASET(DATASET dataset);

// Protos de la création de station
void ajout_task(STATION* instance,TASK* tache); // à déjà séléctionné quelle tache ajouter.
// ne fait vraiment que l'ajout

// Algorithme
void ALGO(DATASET dataset);
int FINTRAITEMENT(DATASET dataset);



#endif