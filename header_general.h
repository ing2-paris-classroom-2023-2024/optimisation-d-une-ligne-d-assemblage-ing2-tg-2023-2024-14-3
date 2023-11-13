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


// Structures de Chargement de Données
typedef struct DATA {
    int type;         // Type de donnée (0 : INT, 1 : FLOAT)
    int nb;           //
    int i;            // Données de type INT (0)
    float f;          // Données de type FLOAT (1)
} DATA;
typedef struct DATAS {
    int TCYCLE;         // Temps de Cycle
    DATA* EXCLUSION;    // Données d'exclusion
    int EXCLUSION_TOT;  // Nombre total d'exclusion
    DATA* PRECEDENCE;   // Données de précédence
    int PRECEDENCE_TOT; // Nombre total de precedence
    DATA* OPERATION ;   // Données d'opération
    int OPERATION_TOT;  // Nombre total d'operation
} DATAS;



// **********  PROTOS   **********

// Protos de Chargement de Données
DATAS SCANDATA(char* jeu_donnees);



#endif