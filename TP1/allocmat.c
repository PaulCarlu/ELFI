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

void freematFLOAT(float **mat) {
    free(mat[0]);
    free(mat);
}

void freematINT(int **mat) {
    free(mat[0]);
    free(mat);
}