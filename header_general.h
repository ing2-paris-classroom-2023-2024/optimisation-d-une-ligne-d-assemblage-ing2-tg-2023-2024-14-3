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
     * BASEID (entier | int) : Numéro réel de la tâche.
     *
     * TEMPS_EXE (entier | int) : Temps de réalisation de la tâche en ms
     *
     * USED (booléen | bool) : Indique si la tâche est assignée ou non.
     *
     * P (Tableau de pointeurs sur TASK | TASK**) : Tableau d'adresse des tâches précédentes la tâche actuelle.
     *
     * P_TOT (entier | int) : Nombre de prédécesseurs de la tâche actuelle.
     *
     * S (Tableau de pointeurs sur TASK | TASK**) : Tableau d'adresse des tâches succédant à la tâche actuelle.
     *
     * S_TOT (entier | int) : Nombre de successeurs de la tâche actuelle.
     *
     * E (Tableau de pointeurs sur TASK | TASK**) : Tableau d'adresse des tâches ayant une relation d'exclusion avec
     *      la tâche actuelle.
     *
     * E_TOT (entier | int) : Nombre de relations d'exclusions avec cette tâche
     *
     * TEMOIN (entier | int) : Argument de colorisation dans le parcours DFS utilisé.
     */

    int BASEID;
    int TEMPS_EXE;
    bool USED;
    struct TASK** P;    // Tableau des Précédents
    int P_TOT;
    struct TASK** S;    // Tableau des Successeurs
    int S_TOT;
    struct TASK** E;    // Tableau des Exclusions
    int E_TOT;
    int TEMPS_TOT;
    int MARQUEUR;
    int TEMOIN;
};

typedef struct STATION{
    /*
     * Structure qui définie chaque station et les répertorie les tâches faites à cette dernière.
     *
     * TEMPS_TOT (entier | int) : Durée totale en ms des actions au sein de la station.
     *
     * NB_SELECTIONS (entier | int) : Nombre de tâches présentes dans la station.
     *
     * SELECTION (Tableau de pointeurs sur TASK | TASK**) : Tableau d'adresse des tâches effectuées par la station.
     */

    int TEMPS_TOT;
    int NB_SELECTIONS;
    struct TASK** SELECTION;

}STATION;

// **********  PROTOS   **********

// Fonctions globales
//void DFS(DATASET dataset, TASK** selection, int nb_selection, TASK* tache, int TEMPS_PREC);  // Parcours DFS d'un element de station
void DFS(DATASET dataset, TASK** selection, int nb_selection, TASK* tache, int MARQUEUR_PREC);

// Protos de Chargement de Données
DATAS SCANDATAS(char* jeu_donnees);
int** FILLDATAS(char* fname, int* tot, int cond);
void DISPDATAS(DATAS datas);
void FREEDATAS(DATAS datas);

// Protos de l'Ordonnancement des Données
DATASET DATASORT(DATAS datas);
void DISPDATASET(DATASET dataset);
void FREEDATASET(DATASET dataset);

// Algorithme
void ALGO(DATASET dataset);
int FINTRAITEMENT(DATASET dataset);

#endif