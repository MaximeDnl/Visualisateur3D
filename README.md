# Visualisateur3D  
**Projet personnel en C : moteur de rendu 3D from scratch**
 
L'objectif : construire un visualisateur 3D, étape par étape dans le langage de programmation C, en comprenant chaque brique.  
Ci-dessous est décrit les différentes étapes du projet.

---

## 🔹 PHASE 1 — **Géométrie & mathématiques 3D** (Finie et testée)

> Premier objectif : poser les bases mathématiques et les outils de transformation pour manipuler des objets dans l’espace.

### 1 Structures fondamentales (Complété)
- `Vec3` : vecteurs 3D pour représenter points ou directions. ✅
- `Mat3` : matrices 3×3 pour les rotations. ✅
- `Mat4` : matrices 4×4 pour les transformations affines (rotation + translation). ✅

### 2 Opérations vectorielles (Complété)
- Addition, soustraction ✅
- Produit scalaire et vectoriel ✅
- Normalisation, calcul de norme ✅

### 3 Transformations (Complété)
- Rotations autour d'un axe quelconque ✅
- Inversion de matrice 3*3 ✅
- Passage entre repères (changement de base) ✅

---

## 🔹 PHASE 2 — **Représentation de la scène** (Finie et testée)

> On passe de la théorie à la modélisation d’objets 3D et de leur place dans une scène globale.

### 4 Objet 3D (Complété)
- Liste de sommets, textures, normales, faces (coordonnées locales) ✅
- Désérialisation fichier simple .obj (composé uniquement de v, vn, vt, f) ✅

### 5 Repères (Complété)
- **Local** : chaque objet possède son propre repère ✅
- **Caméra** : repère propre (position + base orthonormée) afin d'observer la scène depuis un point de vue donné ✅
- **Monde** : tous les objets sont convertis dans un repère global, celui de la caméra ✅

---

## 🔹 PHASE 3 — **Affichage en "fil de fer"** (Finie et testée)

> Transformation complète d’un objet local jusqu’à sa projection sur un écran.

### 6 Uniformisation des bases (Complété)
1. Objet (repère local) → repère monde   ✅
2. Monde → repère caméra (vue) ✅

### 7 Projection (Complété)
- Caméra → plan image (projection perspective) ✅
- Division par la profondeur (x/z, y/z) ✅
- Application d'une *viewport* (fenêtre d'affichage) ✅
 
### 8 Rendu wireframe (points & segments)
- Transformation des sommets jusqu’à l’écran ✅
- Tracé des arêtes entre les points projetés (Algo de Bresenham) ✅

---

## 🔹 Phase 4 — **Affichage avec faces pleines**

### 9 2e Rendu wireframe (faces)
- Affichage des faces
- Système de priorité d'affichage (afin d'afficher que le visible)
- Nuance de lumière avec méthode de Lambert

---

## 🔹 PHASE 5 — **Interaction**

> On donne vie à la scène : zoom, rotation, déplacement…

### 10 Contrôles utilisateur
- Rotation de la caméra autour de l’objet
- Zoom / dézoom
- Translation latérale

### 11 Navigation & animation
- Mise à jour du repère caméra selon les entrées
- Rafraîchissement continu de l’affichage

---

## Résultats :
 
<img src="images/teapot360.gif" alt="Aperçu d'une téhière" width="1000"/>

<img src="images/cow.gif" alt="Aperçu d'une vache" width="1000"/>

---

## Sources :
https://fr.wikipedia.org/wiki/Objet_3D_(format_de_fichier)<br>
https://fr.wikipedia.org/wiki/Projection_centrale<br>
https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_segment_de_Bresenham<br>
https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm<br>
https://fr.wikipedia.org/wiki/Loi_de_Lambert


> Commande pour compiler : gcc -Wextra -Werror -pedantic -fsanitize=address -o main proj.c scene.c mat.c -lm -ljpeg

---

Ce projet est distribué sous licence Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0).
Voir le fichier LICENSE pour plus de détails.














    
