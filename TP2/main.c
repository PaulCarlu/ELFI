// Carlu Paul - Martin Malo
//
#include <stdio.h>
#include <stdlib.h>
#include "cal1Elem.h"
#include "fonctionsUtilitaires.h"
#include "../TP1/lecfima.h"
#include "../TP1/allocmat.h"

// Depuis le dossier TP2 :
// gcc main.c cal1Elem.c fonctionsUtilitaires.c processCalcElementaires.c integralesElementaires.c fonctionsDef.c ../TP1/lecfima.c ../TP1/allocmat.c -lm
//

int main() {
    // Utilisation de lecfima pour charger le fichier de maillage
    /* Notations :
    - typEl : type de l'élément géométrique
    - nbtng : nombre total de noeuds
    - nbtel : nombre total d'éléments
    - nbneel : nombre de noeuds sur un élément
    - nbaret : nombre d'arêtes sur un élément
    - coord : matrice de toutes les coordonnées
    - ngnel : matrice des numéros globaux des éléments
    - nRefAr : matrice des numéros de référence associés aux arrêtes
    */
    char *ficmai = "maillage.txt";
    int typEl, nbtng, nbtel, nbneel, nbaret;
    float **coord; 
    int **ngnel, **nRefAr;
    
    lecfima(ficmai,&typEl,&nbtng,&coord,&nbtel,&ngnel,&nbneel,&nbaret,&nRefAr);

    // Initialisation des variables
    /* Notations :
    - nRefDom : numéro de référence des arêtes internes du domaine
    - nbRefD0, nbRefD1, nbRefF1 : nombre de valeurs contenues dans les différents vecteurs numRefD0, numRefD1 et numRefF1
    - numRefD0, numRefD1, numRefF1 : vecteurs des numéros de référence de chaque type
    ---> numRefD0 : Dirichlet homogène ; numRefD1 : Dirichlet non homogène ; numRefF1 : Fourier/Neumann
    - coorEl : coordonnées de l'élement sélectionné
    - nRefArEl : matrice des numéros de référence associés aux arrêtes de l'élement sélectionné
    - MatElem : matrice élémentaire
    - SMbrElem : vecteur du second membre élémentaire
    - NuDElem : vecteur des noeuds porteurs d'une condition de Dirichlet
    - uDElem : vecteurs des valeurs portées par ces noeuds avec une condition de Dirichlet
    */
    float **MatElem = allocmatFLOAT(nbneel,nbneel);
    float **coorEl = allocmatFLOAT(nbneel,2);
    float SMbrElem[nbneel], uDElem[nbneel];
    int NuDElem[nbneel], nRefArEl[nbneel];
    int *numRefD0, *numRefD1, *numRefF1;
    int nRefDom, nbRefD0, nbRefD1, nbRefF1;

    for (int K=0; K < nbtel; K++) {
        // Assignation des valeurs pour la fonction cal1Elem
        for (int i=0; i<nbneel; i++) {
            for (int j=0; j<nbneel; j++) {
                MatElem[i][j] = 0;
            }
            SMbrElem[i] = 0;
        }
        selectPts(nbneel,ngnel[K],coord,coorEl);

        // Appel de cal1Elem
        cal1Elem(nbneel,nRefDom,nbRefD0,numRefD0,nbRefD1,numRefD1,nbRefF1,numRefF1,typEl,coorEl,nbaret,nRefArEl,MatElem,SMbrElem,NuDElem,uDElem);
        
        // Appel de impCalEl pour vérifier les calculs
        impCalEl(K+1,typEl,nbneel,MatElem,SMbrElem,NuDElem,uDElem);
    }

    freematFLOAT(MatElem);
    freematFLOAT(coord);
    freematINT(ngnel);
    freematINT(nRefAr);
    return 0;
}