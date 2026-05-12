CARLU Paul - MARTIN Malo
Université de Rennes
Master 1 Mathématiques et Applications parcours Calcul scientifique et modélisation

Ce travail a été réalisé dans le cadre du module 'Elements finis' du master.

La compilation se fait dans le dossier 'TP5' à l'aide du fichier 'script.sh'.
Pour ce faire, il faut au préalable avoir compilé les fichiers fortran à l'intérieure du dossier 'tp5_prof' pour obtenir les '.o' nécessaire.

Lors de l'éxécution du programme, il vous sera demander des choix à faire :
    - domaine : 1 ou 2
    - cas : 1, 2 ou 3
    - maillage (quadrangle/triangle) : 1 ou 2
    - IMPFCH : entier pour imprimer dans fort.IMPFCH les erreurs
      (attention : pour 5 et 6 renvoie une erreur qui provient de affsol_)

Après avoir fait ces choix, la procédure se lance pour l'ensemble des fichiers possible.
    Exemple : 
    choix --> 1 | 2 | 2 | 8
    lance la procédure pour les fichiers --> d1t1_2 | d1t1_4 | d1t1_8 | d1t1_16 | d1t1_32 | d1t1_64
    sur le cas --> 2
    les erreurs seront imprimées dans le fichier --> fort.8
