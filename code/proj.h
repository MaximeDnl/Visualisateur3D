#ifndef _PROJ_H_
#define _PROJ_H_

#include "scene.h"
#include "mat.h"
#include <jpeglib.h>
#include <unistd.h>

typedef struct plan_s {
    int longueur; // Longueur du plan
    int largeur; // Largeur du plan
    float* positions_x; // Tableau de positions des projections des sommets dans plan (axe x)
    float* positions_y; // Tableau de positions des projections des sommets dans plan (axe y)
    int taille_positions; // Taille du tableau de positions
    int cpt_positions; // Compteur de positions dans le plan
} plan;
// Plan de projection pour la scene, ayant pour normale le vecteur z de la caméra, et à une distance z = 1

plan* init_plan(int longueur, int largeur); // Initialise un plan de projection
void free_plan(plan* p); // Libère la mémoire allouée pour un plan

void projeter_sommet(plan* p, vect3 sommet); // Projette un sommet dans le plan
plan* projet_scene(scene* sc); // Projette une scène dans un plan

void dessiner_boule(JSAMPLE* buffer, int largeur, int longueur, int cx, int cy, int r, JSAMPLE r_color, JSAMPLE g_color, JSAMPLE b_color); // Dessine une boule dans le buffer d'image
void dessiner_segment(JSAMPLE* buffer, int largeur, int longueur, int x1, int y1, int x2, int y2, JSAMPLE r_color, JSAMPLE g_color, JSAMPLE b_color); // Dessine un segment dans le buffer d'image
void affichage_plan(plan* p, scene* sc, char* fichier); // Affiche le plan dans un fichier JPEG

#endif