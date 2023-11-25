#include "header_general.h"

void DFS(DATASET dataset, TASK** selection, int nb_selection, TASK* tache, int TEMPS_PREC){
    //      -- FONCTION DE PARCOURS DFS RECURSIF
    //      GRAPHE    : Variable contenant le graphe
    //      MAILLON   : Variable du maillon dans lequel la recherche va être faite
    //      || RETURN :     N/A

    // Vérification de la couleur pour la suite du parcours
    if(tache->TEMOIN){return;}
    tache->TEMOIN = 1;

    // Affichage du chemin
    //printf("%d, ", tache->BASEID);

    // Calcul temps
    tache->TEMPS_TOT = (tache->TEMPS_TOT < TEMPS_PREC + tache->TEMPS_EXE) ? TEMPS_PREC + tache->TEMPS_EXE : tache->TEMPS_TOT;

    for(int i = 0; i < tache->S_TOT; i++){
        bool cond = 0;
        for(int j = 0; j < nb_selection; j++){
            if(selection[j]->BASEID == tache->S[i]->BASEID) cond = 1;
        }
        if(cond){
            DFS(dataset, selection, nb_selection, tache->S[i], tache->TEMPS_TOT);
        }
    }

    tache->TEMOIN = 2;
    return;
}