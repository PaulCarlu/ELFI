#include <stdio.h>
#include <stdlib.h>

float **allocmatFLOAT(int nrow, int ncol) {
    float **mat = malloc(nrow*sizeof(float*));
    if(mat != NULL) {
        float *tmp_mat = malloc(nrow*ncol*sizeof(float));
        if(tmp_mat != NULL) {
            for(int i=0; i<nrow; i++) {
                mat[i] = tmp_mat;
                tmp_mat += ncol;
            }
        } else {
            free(mat);
            mat = NULL;
        }
    }
    return mat;
}

int **allocmatINT(int nrow, int ncol) {
    int **mat = malloc(nrow*sizeof(int*));
    if(mat != NULL) {
        int *tmp_mat = malloc(nrow*ncol*sizeof(int));
        if(tmp_mat != NULL) {
            for(int i=0; i<nrow; i++) {
                mat[i] = tmp_mat;
                tmp_mat += ncol;
            }
        } else {
            free(mat);
            mat = NULL;
        }
    }
    return mat;
}

void printmatFloat (float** ppA , int nrow ,int ncol ){
    for( int i =0; i < nrow ;i ++) {
        for (int j =0; j < ncol ;j ++) printf (" %f ", ppA [i ][ j ]) ;
        printf ("\n");
    }
}

void printmatInt (int** ppA , int nrow ,int ncol ){
    for( int i =0; i < nrow ;i ++) {
        for (int j =0; j < ncol ;j ++) printf (" %d ", ppA [i ][ j ]) ;
        printf ("\n");
    }
}

void freematFLOAT(float **mat) {
    free(mat[0]);
    free(mat);
}

void freematINT(int **mat) {
    free(mat[0]);
    free(mat);
}