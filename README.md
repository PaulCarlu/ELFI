**CARLU Paul** - **MARTIN Malo**  
Université de Rennes  
Master 1 Mathématiques et Applications — parcours *Calcul scientifique et modélisation*

Ce travail a été réalisé dans le cadre du module **Éléments finis** du master.

---

## Compilation

La compilation se fait dans le dossier `TP5` à l'aide du fichier : `script.sh`

Avant cela, il est nécessaire de compiler les fichiers Fortran présents dans le dossier `tp5_prof` afin d'obtenir les fichiers `.o` nécessaires.

---

## Exécution du programme

Lors de l'exécution du programme, plusieurs choix sont demandés :
- **domaine** : `1` ou `2`
- **cas** : `1`, `2` ou `3`
- **maillage** (quadrangle / triangle) : `1` ou `2`
- **IMPFCH** : entier permettant d'imprimer les erreurs dans `fort.IMPFCH`

> Attention : les valeurs `5` et `6` renvoient une erreur provenant de `affsol_`.

---

## Exemple d'exécution

Entrée :
```text
1 | 2 | 2 | 8
```
La procédure sera lancée pour les fichiers :
```text
d1t1_2
d1t1_4
d1t1_8
d1t1_16
d1t1_32
d1t1_64
```
- Cas utilisé : `2`
- Les erreurs seront imprimées dans le fichier :
```text
fort.8
```
