#include<math.h>
#include<stdio.h>

/*
--------------------------------------------------------------------------------
    Evaluation de la solution exacte
--------------------------------------------------------------------------------
*/
extern int nucas;

float solex(float *coor) {
  const float PI = M_PI;
  float val = 0.;

  switch (nucas) {
    case 1 :
	val=16.*coor[0]*coor[1]*(coor[0]-1)*(1-coor[1]);
	break;
    case 2 :
	val=sin(PI*coor[0])*sin(PI*coor[1]);
	break;
    case 3 :
	val=cos(PI*coor[0])*cos(PI*coor[1]);
	break;
    default :
	printf("*** SOLEX : exemple non prevu.\n");
	break;
  }
  return(val);
}
