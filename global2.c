#include "header_general.h"

void DFS(DATASET dataset, TASK** selection, int nb_selection, TASK* tache, int TEMPS_PREC){
    /*
     *  PROCÉDURE DE PARCOURS DFS RÉCURSIF
     *  GRAPHE    : Variable contenant le graphe
     * MAILLON   : Variable du maillon dans lequel la recherche va être faite
     */

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
}

void ALGO(DATASET dataset){

    int nb_stations = 0;
    STATION* stations = (STATION*) malloc(nb_stations*sizeof(STATION));
    stations->temps_tot = 0;

    // Boucle Principale
    while(!FINTRAITEMENT(dataset)){
        stations = (STATION*) realloc(stations, (nb_stations+1)*sizeof(STATION));

        // Boucle de répétition dans une station
        int comp_selection = 1;
        int nb_selection = 0;
        TASK** selection = (TASK**) malloc(nb_selection*sizeof(TASK*));

        while(comp_selection - nb_selection){
            comp_selection = nb_selection;

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
                if(cond && !dataset.TASKS[i].USED){
                    selection = (TASK**) realloc(selection, (nb_selection+1)*sizeof(TASK*));
                    selection[nb_selection] = &(dataset.TASKS[i]);
                    //printf("%d : (PTOT = %d)\n", dataset.TASKS[i].BASEID, dataset.TASKS[i].P_TOT);
                    nb_selection++;
                }
            }
            for(int i = 0; i < nb_selection; i++){
                selection[i]->USED = 1;
            }

            printf("PRECEDENCE : \n");
            for(int u = 0; u < nb_selection; u++) printf("%d : (PTOT = %d)\n", selection[u]->BASEID, selection[u]->P_TOT);

            printf("TEMPS : \n");
            for(int i = 0; i < nb_selection; i++){
                for(int j = 0; j < nb_selection; j++){
                    selection[j]->TEMOIN = 0;
                }
                for(int j = 0; j < nb_selection; j++){
                    selection[j]->TEMOIN = 0;
                }
                DFS(dataset, selection, nb_selection, selection[i], 0);
            }
            //for(int i = 0; i < nb_selection; i++) printf("\t%d : %d\n", selection[i]->BASEID, selection[i]->TEMPS_TOT);
            for(int i = 0; i < nb_selection; i++){
                if(selection[i]->TEMPS_TOT > dataset.T_CYCLE){
                    selection[i]->USED = 0;
                    for(int l = i; l < nb_selection-1; l++){
                        selection[l] = selection[l+1];
                    }
                    selection = (TASK**) realloc (selection, (nb_selection-1)*sizeof(TASK*));
                    nb_selection--;
                }
            }
            for(int u = 0; u < nb_selection; u++) printf("%d : (TEMPS_TOT = %d < %d)\n", selection[u]->BASEID, selection[u]->TEMPS_TOT, dataset.T_CYCLE);
            printf("\n");


            printf("EXCLUSION : \n");
            for (int i = 0; i < nb_selection; i++){
                for(int j = 0; j < selection[i]->E_TOT; j++){
                    for(int k = i+1; k < nb_selection; k++){
                        //printf("\tTRY : POUR (%d) %d on compare (%d) %d   et   (%d) %d\n", i, selection[i]->BASEID, j, selection[i]->E[j]->BASEID, k, selection[k]->BASEID);
                        if(selection[i]->E[j]->BASEID == selection[k]->BASEID){
                            int indice = (selection[i]->E[j]->S_TOT >= selection[k]->S_TOT) ? k : i;
                            for(int l = 0; l < selection[indice]->S_TOT; l++){
                                //printf("\tPARCOURS (%d) : succ. %d -> USED-%d\n", selection[indice]->BASEID, selection[indice]->S[l]->BASEID, selection[indice]->S[l]->USED);
                                if(selection[indice]->S[l]->USED == 1){
                                    printf("BREAK : ANN. SUPPR. de %d (%d utilise)\n", selection[indice]->BASEID, selection[indice]->S[l]->BASEID);
                                    indice = (selection[i]->E[j]->S_TOT >= selection[k]->S_TOT) ? i : k;
                                    break;
                                }
                            }
                            selection[indice]->USED = 0;
                            for(int l = indice; l < nb_selection-1; l++){
                                selection[l] = selection[l+1];
                            }
                            selection = (TASK**) realloc (selection, (nb_selection-1)*sizeof(TASK*));
                            nb_selection--;
                            for(int u = 0; u < nb_selection; u++) printf("%d : (PTOT = %d)\n", selection[u]->BASEID, selection[u]->P_TOT);
                            printf("\n");
                        }
                    }

                }
            }

            printf("TEMOIN DE FIN (SELECTIONS = %d, OLD_SELECTIONS = %d)\n\n\n", nb_selection, comp_selection);

            //printf("%d : VAL=%d\n", nb_stations, nb_actions);
        }
        stations[nb_stations].selection = selection;
        stations[nb_stations].nb_selections = nb_selection;
        for(int i = 0; i < nb_selection; i++) stations[nb_stations].temps_tot = (stations[nb_stations].temps_tot < selection[i]->TEMPS_TOT) ? selection[i]->TEMPS_TOT : stations[nb_stations].temps_tot;

        nb_stations++;
    }

    for(int i = 0; i < nb_stations; i++){
        printf("STATION %d (Nombre d'actions a executer : %d  |  Temps total : %d ms) :\n", i+1, stations[i].nb_selections, stations[i].temps_tot);
        for(int j = 0; j < stations[i].nb_selections; j++){
            printf("\tACTION %d :\tN. ACTION : %d (Duree : %d ms, Temps : %d)\n", j+1, stations[i].selection[j]->BASEID, stations[i].selection[j]->TEMPS_EXE, stations[i].selection[j]->TEMPS_TOT);
        }
        printf("\n");
    }

    int std = 1;
    //system("cls");
    //printf("\e[1;1H\e[2J");
    //clrscr();
    setbuf(stdout, 0);
    printf("NB. STATIONS : %d\n", nb_stations);
    scanf("%d", &std);

}

int FINTRAITEMENT(DATASET dataset){
    for(int i = 0; i < dataset.TASK_TOT; i++) if(!dataset.TASKS[i].USED) return 0;
    return 1;
}