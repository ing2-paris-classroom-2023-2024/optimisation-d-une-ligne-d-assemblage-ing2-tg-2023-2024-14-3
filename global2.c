#include "header_general.h"

void DFS2(DATASET dataset, TASK** SELECTION, int nb_SELECTION, TASK* tache, int TEMPS_PREC){
    /*
     *  PROCÉDURE DE PARCOURS DFS RÉCURSIF
     *  GRAPHE    : Variable contenant le graphe
     * MAILLON   : Variable du maillon dans lequel la recherche va être faite
     * Version alternative de la procédure utilisée par le programme principal*/

    // Vérification de la couleur pour la suite du parcours
    if(tache->TEMOIN){return;}
    tache->TEMOIN = 1;

    // Affichage du chemin
    //printf("%d, ", tache->BASEID);

    // Calcul temps
    tache->TEMPS_TOT = (tache->TEMPS_TOT < TEMPS_PREC + tache->TEMPS_EXE) ? TEMPS_PREC + tache->TEMPS_EXE : tache->TEMPS_TOT;

    for(int i = 0; i < tache->S_TOT; i++){
        bool cond = 0;
        for(int j = 0; j < nb_SELECTION; j++){
            if(SELECTION[j]->BASEID == tache->S[i]->BASEID) cond = 1;
        }
        if(cond){
            DFS2(dataset, SELECTION, nb_SELECTION, tache->S[i], tache->TEMPS_TOT);
        }
    }
    tache->TEMOIN = 2;
}

void ALGO2(DATASET dataset){
    /*
    * Procédure principale de ce projet
    * Gère et affiche les stations et les tâches associées
    * DATASET dataset : Structure du jeu de données triées et organisées
    * version alternative du sous-programme principal du projet
    */

    // Création du tableau de STATIONS et initialisation des paramètres
    int nb_stations = 0;
    STATION* stations = (STATION*) malloc(nb_stations*sizeof(STATION));
    stations->TEMPS_TOT = 0;

    // Boucle Principale
    while(!FINTRAITEMENT2(dataset)){
        stations = (STATION*) realloc(stations, (nb_stations+1)*sizeof(STATION));

        // Boucle de répétition dans une station
        int comp_SELECTION = 1;
        int nb_SELECTION = 0;
        TASK** SELECTION = (TASK**) malloc(nb_SELECTION*sizeof(TASK*));

        while(comp_SELECTION - nb_SELECTION){
            comp_SELECTION = nb_SELECTION;

            // Détecteur de sommet valide en fonction des PRECEDENCES
            for(int i = 0; i < dataset.TASK_TOT; i++){
                // Si tous les prédécesseurs sont valides alors valider la tache
                bool cond = 1;
                for(int j = 0; j < dataset.TASKS[i].P_TOT; j++){
                    if(dataset.TASKS[i].P[j]->USED == 0){
                        cond = 0;
                        break;
                    }
                }
                // Si une tâche a été choisie, on l'ajoute au tableau de la station
                if(cond && !dataset.TASKS[i].USED){
                    SELECTION = (TASK**) realloc(SELECTION, (nb_SELECTION+1)*sizeof(TASK*));
                    SELECTION[nb_SELECTION] = &(dataset.TASKS[i]);
                    //printf("%d : (PTOT = %d)\n", dataset.TASKS[i].BASEID, dataset.TASKS[i].P_TOT);
                    nb_SELECTION++;
                }
            }
            // Boucle de désactivation du choix des tâches présentes dans la station
            for(int i = 0; i < nb_SELECTION; i++){
                SELECTION[i]->USED = 1;
            }
            // Boucle d'affichage des précédences
            printf("PRECEDENCE : \n");
            for(int u = 0; u < nb_SELECTION; u++) printf("%d : (PTOT = %d)\n", SELECTION[u]->BASEID, SELECTION[u]->P_TOT);

            // Boucle d'affichage du temps au sein de la station
            printf("TEMPS : \n");
            for(int i = 0; i < nb_SELECTION; i++){
                for(int j = 0; j < nb_SELECTION; j++){
                    SELECTION[j]->TEMOIN = 0;
                }
                // Le parcours en DFS sert ici à connaitre le temps des actions qui en découleront
                DFS2(dataset, SELECTION, nb_SELECTION, SELECTION[i], 0);
            }
            //for(int i = 0; i < nb_SELECTION; i++) printf("\t%d : %d\n", SELECTION[i]->BASEID, SELECTION[i]->TEMPS_TOT);
            // La séléction des tâches se fait pas rapport au temps

            // Si une action a déjà été réalisée la retirer de la liste des tâches
            for(int i = 0; i < nb_SELECTION; i++){
                if(SELECTION[i]->TEMPS_TOT > dataset.T_CYCLE){
                    SELECTION[i]->USED = 0;
                    for(int l = i; l < nb_SELECTION-1; l++){
                        SELECTION[l] = SELECTION[l+1];
                    }
                    SELECTION = (TASK**) realloc (SELECTION, (nb_SELECTION-1)*sizeof(TASK*));
                    nb_SELECTION--;
                }
            }
            for(int u = 0; u < nb_SELECTION; u++) printf("%d : (TEMPS_TOT = %d < %d)\n", SELECTION[u]->BASEID, SELECTION[u]->TEMPS_TOT, dataset.T_CYCLE);
            printf("\n");


            printf("EXCLUSION : \n");
            for (int i = 0; i < nb_SELECTION; i++){
                for(int j = 0; j < SELECTION[i]->E_TOT; j++){
                    for(int k = i+1; k < nb_SELECTION; k++){
                        //printf("\tTRY : POUR (%d) %d on compare (%d) %d   et   (%d) %d\n", i, SELECTION[i]->BASEID, j, SELECTION[i]->E[j]->BASEID, k, SELECTION[k]->BASEID);
                        if(SELECTION[i]->E[j]->BASEID == SELECTION[k]->BASEID){
                            int indice = (SELECTION[i]->E[j]->S_TOT >= SELECTION[k]->S_TOT) ? k : i;
                            for(int l = 0; l < SELECTION[indice]->S_TOT; l++){
                                //printf("\tPARCOURS (%d) : succ. %d -> USED-%d\n", SELECTION[indice]->BASEID, SELECTION[indice]->S[l]->BASEID, SELECTION[indice]->S[l]->USED);
                                if(SELECTION[indice]->S[l]->USED == 1){
                                    printf("BREAK : ANN. SUPPR. de %d (%d utilise)\n", SELECTION[indice]->BASEID, SELECTION[indice]->S[l]->BASEID);
                                    indice = (SELECTION[i]->E[j]->S_TOT >= SELECTION[k]->S_TOT) ? i : k;
                                    break;
                                }
                            }
                            SELECTION[indice]->USED = 0;
                            for(int l = indice; l < nb_SELECTION-1; l++){
                                SELECTION[l] = SELECTION[l+1];
                            }
                            SELECTION = (TASK**) realloc (SELECTION, (nb_SELECTION-1)*sizeof(TASK*));
                            nb_SELECTION--;
                            for(int u = 0; u < nb_SELECTION; u++) printf("%d : (PTOT = %d)\n", SELECTION[u]->BASEID, SELECTION[u]->P_TOT);
                            printf("\n");
                        }
                    }

                }
            }

            printf("TEMOIN DE FIN (SELECTIONS = %d, OLD_SELECTIONS = %d)\n\n\n", nb_SELECTION, comp_SELECTION);

            //printf("%d : VAL=%d\n", nb_stations, nb_actions);
        }
        stations[nb_stations].SELECTION = SELECTION;
        stations[nb_stations].NB_SELECTIONS = nb_SELECTION;
        for(int i = 0; i < nb_SELECTION; i++) stations[nb_stations].TEMPS_TOT = (stations[nb_stations].TEMPS_TOT < SELECTION[i]->TEMPS_TOT) ? SELECTION[i]->TEMPS_TOT : stations[nb_stations].TEMPS_TOT;

        nb_stations++;
    }
    AFFICHE_STAT(stations,nb_stations);

    int std = 1;
    //system("cls");
    //printf("\e[1;1H\e[2J");
    //clrscr();
    setbuf(stdout, 0);
    printf("NB. STATIONS : %d\n", nb_stations);
    //scanf("%d", &std);

}

bool FINTRAITEMENT2(DATASET dataset){
    for(int i = 0; i < dataset.TASK_TOT; i++) if(!dataset.TASKS[i].USED) return false;
    return true;
}