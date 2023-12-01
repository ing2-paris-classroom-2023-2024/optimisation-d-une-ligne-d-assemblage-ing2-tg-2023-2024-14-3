#ifndef ECELECAR_HEADER_GENERAL_H
#define ECELECAR_HEADER_GENERAL_H

// Espace des Bibliothèques :
#include <stdio.h> // Gestion de la console et des entrées utilisateurs
#include <stdlib.h> // Gestions des fonctions de base du C
#include <string.h> // Gestion des chaines de caractères
#include <stdbool.h> // Gestion du type booléen
#include <limits.h> // Gestions des limites et bordures de fichiers et de valeurs

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

typedef struct TASK TASK; // Alias pour la structure TASK déclarée plus bas

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
     * MARQUEUR (entier | int) : Témoigne du niveau d'importance de la tâche au sein de la station.
     *
     * TEMOIN (entier | int) : Argument de colorisation dans le parcours DFS utilisé.
     */

    int BASEID;
    int TEMPS_EXE;
    bool USED;

    // Section précédences
    struct TASK** P;
    int P_TOT;
    // Section successeurs
    struct TASK** S;
    int S_TOT;
    // Section exclusions
    struct TASK** E;
    int E_TOT;

    int MARQUEUR;
    int TEMPS_TOT;
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

void DFS(DATASET dataset, TASK** selection, int nb_selection, TASK* tache, int MARQUEUR_PREC);
// Procédure de parcours en DFS pour la séléction des tâches à effectuer.

void ALGO(DATASET dataset); // Procédure générale du projet qui instancie et affiche les différentes stations.

bool FINTRAITEMENT(DATASET dataset); // Fonction de libération mémoire des stations et de DATASET

// Protos de Chargement de Données

DATAS SCANDATAS(char* jeu_donnees); // Fonction lisant les données

int** FILLDATAS(char* fname, int* tot, int cond); // Fonction remplissant les différents tableaux utiles pour DATA

void DISPDATAS(DATAS datas); // Procédure temporaire d'affichage des éléments remplis

void FREEDATAS(DATAS datas); // Procédure de libération de l'espace mémoire d'une instance de type DATA

// Protos de l'Ordonnancement des Données

DATASET DATASORT(DATAS datas); // Remplissage De l'instance de DATASET à partir des informations de DATA
void DISPDATASET(DATASET dataset); // Fonction d'affichage des infos présentes dans la structure DATASET
void FREEDATASET(DATASET dataset); // Procédure de libération de l'espace mémoire d'une instance de type DATASET

// Version alternative des codes :

void DFS2(DATASET dataset, TASK** SELECTION, int nb_SELECTION, TASK* tache, int TEMPS_PREC);
// Procédure de recherche par DFS alternative servant pour une autre interprétation du code.

void ALGO2(DATASET dataset); // Procédure de fonctionnement alternatif du projet.

bool FINTRAITEMENT2(DATASET dataset);
// Fonction de léibération de mémoire pour le fonctionnement alternatif du programme.

#endif