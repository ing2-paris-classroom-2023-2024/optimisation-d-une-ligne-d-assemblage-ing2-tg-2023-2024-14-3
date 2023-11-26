## Pseudo code pour la version alternative du projet :

```c
void ALGO2(DATASET dataset){
    nb_stations<-0
    Allocation dynamique d un tableau de STATION
    while FINTRAITEMENT2(dataset) {
        
        Modification de la taille du tableau de STATION
        Allocation dynamique d un tableau contenant les tâches 
        while Un problème de précédences/exclusion/temps{
            
            Vérification des précédences
            Ajout de la tâche dans le tableau
            Parcours DFS pour l actualisation du temps au sein de la station
            
            if le temps additionné est supérieur au temps de cycle{
                Supprimer la tâche actuelle
            }
            
            Vérification des exclusions
            for éléments dans le tableau des tâches{
                for élément présent dans le tableau d exclusion unique{
                   if Un élément est en commun entre ces tableaux {
                       
                       Suppression de l élément le moins important (moins de précédence ou d impact)
                       Diminution du tableau de tâches
                   }
                }
            }
        }
        Témoin de fin de boucle interne
        Affichage des tâches choisies
        Ajout dans l instance station du tableau de tâche et du temps total
        nb_stations +=1
    }
    Affichage des différents éléments des stations
}
```

## Pseudo code pour la version définitive du projet :
```c
void ALGO(DATASET dataset){
    
    nb_stations<-0
    Allocation dynamique d un tableau de STATION
    while FINTRAITEMENT2(dataset) {
        
        Modification de la taille du tableau de STATION
        Allocation dynamique d un tableau contenant les tâches
        while Un problème de précédences/exclusion/temps{
            
            Vérification des précédences
            if une des conditions n est pas remplie{
                Changement de tâche pour les comparaisons
            }
            Ajout de la tâche dans le tableau des tâches
            Vérification des exclusions
            for éléments dans le tableau des tâches{
                for éléments dans le tableau d exclusion de la tâche{
                    if Un élément est en commun entre ces tableaux{
                        
                        Suppression de l élément le moins important (moins de précédence ou d impact)
                        Diminution du tableau de tâches
                        Affichage des tâches choisies
                    }
                }
            }
            Parcours DFS pour le calcul du temps
            do{
                Remise à zéro du temps total
                Addition du temps de chaque tâche
                if le temps total est supérieur au temps de cycle{
                    Choisir la tâche avec la plus grande importance et la garder
                    Supprimer l autre tâche
                }
            }while le temps total est suppérieur au temps de cycle
            Témoin de fin de parcours interne
        }
        Affectation des différents éléments au sein de l instance de station
        nb_stations +=1
    }
    Affichage des informations des différentes stations
}
```

## Pseudo code de la fonction de remplissage de structure DATASET :
```c
DATASET DATASORT(DATAS datas){
    Instantiation d un élément de type DATASET : dataset
    Initialisation de dataset
    
    for chaque éléments du tableau de tâches{
        Initialisation des éléments des différentes structures TASK
    }
    
    Rempli_prece =
    for chaque élément dans le tableau des précédences{
        for chaque éléments de la première colonne{
            if l ID est le même{
                Ajout dans le tableau de précédence de la tâche
            }
        }
        for chaque élément dans la seconde colonne{
           if l ID est le même{
                Ajout dans le tableau de précédence de la tâche
            } 
        }
        Augmentation de la taille du tableau de précédence de la tâche
        Incrémentation de la variable de taille du tableau
    }
    
    Rempli_succ
    Rempli_exclu
}
```