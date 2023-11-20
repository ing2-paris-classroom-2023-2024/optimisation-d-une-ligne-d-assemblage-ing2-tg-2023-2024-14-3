#include "header_general.h"

int main() {
    setbuf(stdout, 0);
    char* jeu_donnees = "01";
    DATAS datas = SCANDATA(jeu_donnees);
    printf("EXCLUSIONS :\n");
    for(int i = 0; i < datas.EXCLUSION_TOT; i++){
        printf("%d :\t%d\t%d\n", i, datas.EXCLUSION[i].nb, datas.EXCLUSION[i].i);
    }
    printf("\nPRECEDENCES :\n");
    for(int i = 0; i < datas.PRECEDENCE_TOT; i++){
        printf("%d :\t%d\t%d\n", i, datas.PRECEDENCE[i].nb, datas.PRECEDENCE[i].i);
    }
    printf("\nOPERATIONS :\n");
    for(int i = 0; i < datas.OPERATION_TOT; i++){
        printf("%d :\t%d\t%.2f\n", i, datas.OPERATION[i].nb, datas.OPERATION[i].f);
    }
    printf("\nTCYCLE : \n");
    printf("%d\n", datas.TCYCLE);
    return 0;
}
