#include "header_general.h"

void DFS(DATASET dataset, TASK** selection, int nb_selection, TASK* tache, int MARQUEUR_PREC){
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
    tache->MARQUEUR = (tache->MARQUEUR < MARQUEUR_PREC + 1) ? MARQUEUR_PREC + 1 : tache->MARQUEUR;

    for(int i = 0; i < tache->S_TOT; i++){
        bool cond = 0;
        for(int j = 0; j < nb_selection; j++){
            if(selection[j]->BASEID == tache->S[i]->BASEID) cond = 1;
        }
        if(cond){
            DFS(dataset, selection, nb_selection, tache->S[i], tache->MARQUEUR);
        }
    }
    tache->TEMOIN = 2;
}

void ALGO(DATASET dataset){
    /*
     * Procédure principale de ce projet
     * Gère et affiche les stations et les tâches associées
     * DATASET dataset : Structure du jeu de données triées et organisées
     */

    // Création du tableau de STATIONS et initialisation des paramètres
    int nb_stations = 0;
    STATION* stations = (STATION*) malloc(nb_stations*sizeof(STATION));
    stations->TEMPS_TOT = 0;

    // Boucle Principale
    while(!FINTRAITEMENT(dataset)){
        stations = (STATION*) realloc(stations, (nb_stations+1)*sizeof(STATION));

        // Boucle de répétition dans une station
        int comp_selection = 1;
        int nb_selection = 0;

        // Création du tableau des tâches de la station
        TASK** selection = (TASK**) malloc(nb_selection*sizeof(TASK*));

        //Boucle de parcours du dataset
        while(comp_selection - nb_selection){
            comp_selection = nb_selection;

            // Détecteur de sommet valide en fonction des PRECEDENCES
            for(int i = 0; i < dataset.TASK_TOT; i++){
                bool cond = 1;
                // Si tous les prédécesseurs sont valides alors valider la tache
                for(int j = 0; j < dataset.TASKS[i].P_TOT; j++){
                    if(dataset.TASKS[i].P[j]->USED == 0){
                        cond = 0;
                        break;
                    }
                }
                // Si une tâche a été choisie, on l'ajoute au tableau de la station
                if(cond && !dataset.TASKS[i].USED){
                    selection = (TASK**) realloc(selection, (nb_selection+1)*sizeof(TASK*));
                    selection[nb_selection] = &(dataset.TASKS[i]);
                    //printf("%d : (PTOT = %d)\n", dataset.TASKS[i].BASEID, dataset.TASKS[i].P_TOT);
                    nb_selection++;
                }
            }
            // Boucle de désactivation du choix des tâches présentes dans la station
            for(int i = 0; i < nb_selection; i++){
                selection[i]->USED = 1;
            }
            // Boucle d'affichage des précédences
            printf("PRECEDENCE : \n");
            for(int u = 0; u < nb_selection; u++) printf("%d : (PTOT = %d)\n", selection[u]->BASEID, selection[u]->P_TOT);

            // Boucle d'affichage et de vérification des exclusions
            printf("EXCLUSION : \n");
            // On parcourt le tableau dataset et celui de la station pour trouver les correspondances
            for (int i = 0; i < nb_selection; i++){
                for(int j = 0; j < selection[i]->E_TOT; j++){
                    for(int k = i+1; k < nb_selection; k++){
                        //printf("\tTRY : POUR (%d) %d on compare (%d) %d   et   (%d) %d\n", i, selection[i]->BASEID, j, selection[i]->E[j]->BASEID, k, selection[k]->BASEID);

                        // Si les tâches correspondent
                        if(selection[i]->E[j]->BASEID == selection[k]->BASEID){
                            int indice = (selection[i]->E[j]->S_TOT >= selection[k]->S_TOT) ? k : i;

                            // Boucle de vérification des exclusions de la tâche
                            for(int l = 0; l < selection[indice]->S_TOT; l++){
                                //printf("\tPARCOURS (%d) : succ. %d -> USED-%d\n", selection[indice]->BASEID, selection[indice]->S[l]->BASEID, selection[indice]->S[l]->USED);
                                if(selection[indice]->S[l]->USED == 1){
                                    printf("BREAK : ANN. SUPPR. de %d (%d utilise)\n", selection[indice]->BASEID, selection[indice]->S[l]->BASEID);
                                    indice = (selection[i]->E[j]->S_TOT >= selection[k]->S_TOT) ? i : k;
                                    break;
                                }
                            }
                            selection[indice]->USED = 0;
                            // Boucle de déplacement des valeurs au sein du tableau
                            for(int l = indice; l < nb_selection-1; l++){
                                selection[l] = selection[l+1];
                            }
                            // Suppression de la tâche qui venait d'être ajoutée
                            selection = (TASK**) realloc (selection, (nb_selection-1)*sizeof(TASK*));
                            nb_selection--;
                            for(int u = 0; u < nb_selection; u++) printf("%d : (PTOT = %d)\n", selection[u]->BASEID, selection[u]->P_TOT);
                            printf("\n");
                        }
                    }
                }
            }
            // Gestion du temps en rapport avec le temps de cycle
            printf("TEMPS : \n");
            for(int i = 0; i < nb_selection; i++){
                selection[i]->MARQUEUR = 0;
            }
            for(int i = 0; i < nb_selection; i++){
                for(int j = 0; j < nb_selection; j++){
                    selection[j]->TEMOIN = 0;
                }
                // Appel de la fonction DFS pour
                DFS(dataset, selection, nb_selection, selection[i], 0);
            }
            //for(int i = 0; i < nb_selection; i++) printf("\t%d : %d\n", selection[i]->BASEID, selection[i]->TEMPS_TOT);
            do{
                for(int u = 0; u < nb_selection; u++) printf("%d : (MARQUEUR = %d, S_TOT =  %d)\n", selection[u]->BASEID, selection[u]->MARQUEUR, selection[u]->S_TOT);
                stations[nb_stations].TEMPS_TOT = 0;

                // Addition des temps des actions de la liste de tâches
                for(int i = 0; i < nb_selection; i++){
                    stations[nb_stations].TEMPS_TOT += selection[i]->TEMPS_EXE;
                }
                // Si la somme est plus importante que le temps de cycle
                if(stations[nb_stations].TEMPS_TOT > dataset.T_CYCLE){
                    int indice = 0;

                    // Boucle de recherche de l'indice de la tâche à enlever
                    for(int i = 0; i < nb_selection; i++){
                        if(selection[indice]->MARQUEUR == selection[i]->MARQUEUR) {
                            indice = (selection[indice]->S_TOT < selection[i]->S_TOT) ? indice : i;
                        }
                        else if(selection[indice]->MARQUEUR < selection[i]->MARQUEUR) {
                            indice = i;
                        }
                    }
                    selection[indice]->USED = 0;

                    // Décalage des informations
                    for(int l = indice; l < nb_selection-1; l++){
                        selection[l] = selection[l+1];
                    }
                    // Réduction du tableau
                    selection = (TASK**) realloc (selection, (nb_selection-1)*sizeof(TASK*));
                    nb_selection--;
                }
            }while(stations[nb_stations].TEMPS_TOT > dataset.T_CYCLE);
            printf("\n");
            //Fin de la recherche des incompatibilitées
            printf("TEMOIN DE FIN (SELECTIONS = %d, OLD_SELECTIONS = %d)\n\n\n", nb_selection, comp_selection);

            //printf("%d : VAL=%d\n", nb_stations, nb_selection);
        }
        //Assignation de la sélection de tâche et MAJ du nombre de tâches dans la station
        stations[nb_stations].SELECTION = selection;
        stations[nb_stations].NB_SELECTIONS = nb_selection;

        nb_stations++;// Incrémentation du nombre de stations
    }

    for(int i = 0; i < nb_stations; i++){
        printf("STATION %d (Nombre d'actions a executer : %d  |  Temps total : %d ms) :\n", i+1, stations[i].NB_SELECTIONS, stations[i].TEMPS_TOT);
        for(int j = 0; j < stations[i].NB_SELECTIONS; j++){
            printf("\tACTION %d :\tN. ACTION : %d (Duree : %d ms, Marqueur : %d)\n", j+1, stations[i].SELECTION[j]->BASEID, stations[i].SELECTION[j]->TEMPS_EXE, stations[i].SELECTION[j]->MARQUEUR);
        }
        printf("\n");
    }

    int std = 1;
    //system("cls");
    //printf("\e[1;1H\e[2J");
    //clrscr();
    setbuf(stdout, 0);
    printf("NB. STATIONS : %d\n", nb_stations);
    //scanf("%d", &std);

}

bool FINTRAITEMENT(DATASET dataset){
    for(int i = 0; i < dataset.TASK_TOT; i++) if(!dataset.TASKS[i].USED) return false;
    return true;
}