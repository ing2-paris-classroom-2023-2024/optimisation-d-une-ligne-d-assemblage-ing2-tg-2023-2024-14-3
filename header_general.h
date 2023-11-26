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
    /*
     * Structure DATAS qui va lire les fichiers du jeu de donnée choisi et remplir une instance de structure DATASET.
     *
     * Le jeu de donnés doit être renseigné dans un dossier numéroté et se situer dans le répertoire
     *      "fichiers_ressources".
     *
     * Cette structure est détruite lorsque l'instance de la structure DATASET est remplie.
     */
    int TCYCLE;          // Temps de Cycle

    int** EXCLUSIONS;    // Données d'exclusion
    int EXCLUSIONS_TOT;  // Nombre total d'exclusion

    int** PRECEDENCES;   // Données de précédence
    int PRECEDENCES_TOT; // Nombre total de precedence

    int** OPERATIONS ;   // Données d'opération
    int OPERATIONS_TOT;  // Nombre total d'opérations
} DATAS;

typedef struct TASK TASK;

typedef struct DATASET {
    /*
     * Structure qui répertorie toutes les informations nécessaires au code à partir d'un jeu de donnés.
     *
     * T_CYCLE (entier | int) : Temps de cycle que doivent respecter les stations.
     *
     * TASK_TOT (entier | int) : Nombre de tâches à effectuer lors de ce programme.
     *
     * TASKS (tableau de structures TASK | TASK*) : Tableau contenant les instances de structure TASK
     */
    int T_CYCLE;
    int TASK_TOT;
    TASK* TASKS;

} DATASET;

struct TASK {
    /*
     * Structure TASK contenant les informations pour chaque tâche à effectuer.
     *
     * */

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

    int TEMPS_TOT;
    int TEMOIN;
};

typedef struct STATION{
    int id;
    int temps_tot;
    int nb_selections;
    struct TASK** selection;
}STATION;




// **********  PROTOS   **********

// Fonctions globales
void QuickSortRecursive(int* data, int left, int right); // Tri Rapide
void DFS(DATASET dataset, TASK** selection, int nb_selection, TASK* tache, int TEMPS_PREC);  // Parcours DFS d'un element de station

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