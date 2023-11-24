#include "header_general.h"

int main() {
    setbuf(stdout, 0);
    char* jeu_donnees = "01";
    DATAS datas = SCANDATAS(jeu_donnees);
    //DISPDATAS(datas);
    DATASET dataset = DATASORT(datas);
    DISPDATASET(dataset);

    ALGO(dataset);

    FREEDATASET(dataset);
    return 0;
}


void ALGO(DATASET dataset){

    int nb_stations = 0;
    STATION* stations = (STATION*) malloc(nb_stations*sizeof(STATION));

    // Boucle Principale
    while(!FINTRAITEMENT(dataset)){
        stations = (STATION*) realloc(stations, (nb_stations+1)*sizeof(STATION));

        // Boucle de répétition dans une station
        int nb_actions = 1;
        while(nb_actions){
            nb_actions = 0;

            // Détecteur de sommet valide en fonction des PRECEDENCES
            int nb_selection = 0;
            TASK** selection = (TASK**) malloc(nb_selection*sizeof(TASK*));
            for(int i = 0; i < dataset.TASK_TOT; i++){
                // Si tous les prédécesseurs sont valides alors valider la tache
                bool cond = 1;
                for(int j = 0; j < dataset.TASKS[i].P_TOT; j++){
                    if(dataset.TASKS[i].P[j]->USED == 0){
                        cond = 0;
                        break;
                    }
                }
                if(cond){
                    selection = (TASK**) realloc(selection, (nb_selection+1)*sizeof(TASK*));
                    selection[nb_selection] = &(dataset.TASKS[i]);
                    printf("%d : (PTOT = %d)\n", dataset.TASKS[i].BASEID, dataset.TASKS[i].P_TOT);
                    nb_selection++;
                }
            }
            printf("LIMITE");

            for (int i = 0; i < nb_selection; i++){
                for(int j = 0; j < selection[i]->E_TOT; j++){
                    for(int k = 0; k < nb_selection; k++){
                        if(selection[i]->E[j]->BASEID == selection[k]->BASEID){
                            if(selection[i]->E[j]->S_TOT >= selection[k]->S_TOT){
                                for(int l )
                            }
                        }
                    }

                }
            }
            while(1) {
                for (int i = 0; i < nb_selection; i++) {
                    printf("%d : (PTOT = %d)\n", selection[i]->BASEID, selection[i]->P_TOT);
                }
                *selection = *selection + 1;
                nb_selection--;
            }

            printf("%d : VAL=%d\n", nb_stations, nb_actions);
        }

        nb_stations++;
    }


}

int FINTRAITEMENT(DATASET dataset){
    for(int i = 0; i < dataset.TASK_TOT; i++) if(!dataset.TASKS[i].USED) return 0;
    return 1;
}

int FINSTATION(DATASET dataset){
    for(int i = 0; i < dataset.TASK_TOT; i++){
        if(dataset.TASKS[i].USED ) return 0;
    }
    return 1;
}