#ifndef _MAT_H_
#define _MAT_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

typedef struct vect3_s vect3;
typedef struct vect4_s vect4;

typedef struct mat3_s mat3;
typedef struct mat4_s mat4;


mat3 add_3(mat3, mat3); //Additionne 2 matrice 3*3
mat4 add_4(mat4, mat4); //Additionne 2 matrice 4*4

mat3 sous_3(mat3, mat3); //Soustrait la 2e matrice a la 1ere (3*3)
mat4 sous_4(mat4, mat4); //Soustrait la 2e matrice a la 1ere (4*4)

void affiche_3(mat3); //Affiche matrice 3*3
void affiche_4(mat4); //Affiche matrice 4*4

float dot_product(vect3, vect3); //Produit scalaire de 2 vecteurs 3D
vect3 vector_cross_product(vect3, vect3); //Produit vectoriel de 2 vecteurs 3D

float norm(vect3); //Renvoie la norme d'un vecteur 3D
vect3 normalize(vect3); //Renvoie le vecteur normalisé d'un vecteur 3D

mat3 product(mat3, mat3); //Produit de 2 matrices 3*3
vect3 product_mat_vect3(mat3, vect3); //Produit d'une matrice 3*3 et d'un vecteur 3D
mat3 rotation_mat(float angle, vect3 axis); //Renvoie une matrice de rotation selon un angle et un axe

float det(float a, float b, float c, float d); //Calcul du déterminant d'une matrice 2x2
float determinant(mat3); //Calcul du déterminant d'une matrice 3x3

mat3 mat_cofactrice(mat3); //Renvoie la matrice cofactrice d'une matrice 3*3
mat3 transpose(mat3); //Transpose une matrice 3*3

mat3 inverse(mat3); //Inverse une matrice 3*3 si celle-ci est inversible, renvoie une erreur sinon
vect3 change_ref(vect3 v, mat3 base_ref, mat3 new_ref); //Change la référence d'un vecteur v de base_ref à new_ref

#endif 