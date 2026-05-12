/* 
Paul Carlu - Malo Martin 
Université de Rennes 
Master 1 CSM
Module - Elements finis
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../TP5/solex.h"

extern int Domaine;
extern int nucas;
const float PI = M_PI;

    float A11(float* x){
        return 1;
    }

    float A12(float* x){
        return 0;
    }

    float A22(float* x){
        return 1;
    }

    float A00(float* x){
        float val;
        switch (nucas) {
            case 1 :
            val=0;
            break;
            case 2 :
            val=0;
            break;
            case 3 :
            val=1;
            break;
        default :
            printf("*** A00 : exemple non prevu.\n");
            break;
        }
        return val;
    }

    float BN(float*){
        return 0;
    }
    

    float FN(float* x,int refArete){
        float val = 0.0;
        if (Domaine == 2){
            switch (nucas) {
                case 1 :
                val=0;
                break;
                case 2 :
                val=0;
                break;
                case 3 :
                switch(refArete)
                {
                    case 2:
                        return -PI*sin(PI/3.0)*cos(PI*x[1]);
                        break;
                    case 3:
                        return -PI*sin(PI/3.0)*cos(PI*x[0]);
                        break;
                    default:
                        return 0.0;
                }
                break;
            default :
                printf("*** FN : exemple non prevu.\n");
                break;
            }
        }

        return val;
    }

    float FOMEGA(float* x){
        float val;
        switch (nucas) {
            case 1 :
            val=32*(x[0]*(x[0]-1) - x[1]*(1-x[1]));
            break;
            case 2 :
            val=(2*M_PI*M_PI)*solex(x);
            break;
            case 3 :
            val=(2*M_PI*M_PI + 1)*solex(x);
            break;
        default :
            printf("*** FOMEGA : exemple non prevu.\n");
            break;
        }
        return val;
    }

    float UD(float* x){
        float val;
        switch (nucas) {
            case 1 :
            val=solex(x);
            break;
            case 2 :
            val=solex(x);
            break;
            case 3 :
            val=solex(x);
            break;
        default :
            printf("*** UD : exemple non prevu.\n");
            break;
        }

        return val;
    }

