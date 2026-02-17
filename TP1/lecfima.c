#include <stdlib.h>
#include <stdio.h>
#include "allocmat.h"

void lecfima(char *ficmai, int *p_typel, int *p_nbtng, float ***ppp_coord, int *p_nbtel, 
            int ***ppp_ngnel, int *p_nbneel, int *p_nbaret, int ***ppp_nRefAr) {
    /* Notations :
    - typel : type de l'élément géométrique
    - nbtng : nombre total de noeuds
    - nbtel : nombre total d'éléments
    - nbneel : nombre de noeuds sur un élément
    - nbaret : nombre d'arêtes sur un élément
    */
    FILE* fichierMaillage = fopen(ficmai, "r");
    if (!fichierMaillage) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fscanf(fichierMaillage,"%d",p_nbtng);

    /* Coordonnées */
    float **mat_coord = allocmatFLOAT(*p_nbtng,2);
    for (int i=0; i<*p_nbtng; i++) {
        fscanf(fichierMaillage,"%f %f",&mat_coord[i][0],&mat_coord[i][1]);
    }
    *ppp_coord = mat_coord;

    fscanf(fichierMaillage,"%d %d %d %d",p_nbtel,p_typel,p_nbneel,p_nbaret);

    /* Numéros globaux noeuds éléments + numéros globaux référence arêtes */
    int **mat_ngnel = allocmatINT(*p_nbtel,*p_nbneel);
    int **mat_nRefAr = allocmatINT(*p_nbtel,*p_nbaret);
    if (*p_typel == 1) {   // QUADRANGLE
        for(int i=0; i<*p_nbtel; i++) {
            fscanf(fichierMaillage,"%d %d %d %d %d %d %d %d",&mat_ngnel[i][0],&mat_ngnel[i][1],&mat_ngnel[i][2],&mat_ngnel[i][3],
                                                            &mat_nRefAr[i][0],&mat_nRefAr[i][1],&mat_nRefAr[i][2],&mat_nRefAr[i][3]);
        }
    } else if (*p_typel == 2) {   // TRIANGLE
        for(int i=0; i<*p_nbtel; i++) {
            fscanf(fichierMaillage,"%d %d %d %d %d %d",&mat_ngnel[i][0],&mat_ngnel[i][1],&mat_ngnel[i][2],
                                                       &mat_nRefAr[i][0],&mat_nRefAr[i][1],&mat_nRefAr[i][2]);
        }
    }
    *ppp_ngnel = mat_ngnel;
    *ppp_nRefAr = mat_nRefAr;

    fclose(fichierMaillage);
    }