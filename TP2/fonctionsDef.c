// Carlu Paul - Martin Malo
//
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
            printf("*** SOLEX : exemple non prevu.\n");
            break;
        }
        return val;
    }

    float BN(float*){
        return 0;
    }
    

    float FN(float* x){
        float val;
        if (Domaine == 1){
            val = 0;
        }

        else if (Domaine == 2){
            switch (nucas) {
                case 1 :
                val=0;
                break;
                case 2 :
                val=0;
                break;
                case 3 :
                if((fabs(x[0]-1/3)<1e-7) && (0<x[1])){
                    val=-PI*sin(PI/3)*cos(PI*x[1]);
                }
                else if((fabs(x[1]-1/3)<1e-7) && (0<x[0])){
                    val=-PI*sin(PI/3)*cos(PI*x[0]);
                }
                break;
            default :
                printf("*** SOLEX : exemple non prevu.\n");
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
            val=2*pow(PI,2)*solex(x);
            break;
            case 3 :
            val=(2*pow(PI,2)+1)*solex(x);
            break;
        default :
            printf("*** SOLEX : exemple non prevu.\n");
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
            printf("*** SOLEX : exemple non prevu.\n");
            break;
        }

        return val;
    }

