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

    while(!FINTRAITEMENT(dataset)){
        stations = (STATION*) realloc(stations, (nb_stations+1)*sizeof(STATION));

        int nb_actions = 1;
        while(nb_actions){
            nb_actions = 0;
            scanf("%d", &nb_actions);
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