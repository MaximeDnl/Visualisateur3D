# 🌀 Visualisateur3D  
🎯 **Projet personnel en C : moteur de rendu 3D from scratch**
 
L'objectif : construire un visualisateur 3D (ou un mini moteur de rendu), étape par étape dans le langage de programmation C, en comprenant chaque brique.  
Ci-dessous est décrit les différentes étapes du projet, et si j'y arrive, les références avec les fichiers correspondants (:

---

## 🔹 PHASE 1 — **Géométrie & mathématiques 3D**

> Premier objectif : poser les bases mathématiques et les outils de transformation pour manipuler des objets dans l’espace.

### 1 Structures fondamentales
- `Vec3` : vecteurs 3D pour représenter points ou directions.
- `Mat3` : matrices 3×3 pour les rotations.
- `Mat4` : matrices 4×4 pour les transformations affines (rotation + translation).

### 2 Opérations vectorielles
- Addition, soustraction
- Produit scalaire et vectoriel
- Normalisation, calcul de norme

### 3 Transformations
- Rotations autour des axes X, Y, Z
- Passage entre repères (changement de base)
- Inversion de matrice de rotation (transposition si orthonormée)

---

## 🔹 PHASE 2 — **Représentation de la scène**

> On passe de la théorie à la modélisation d’objets 3D et de leur place dans une scène globale.

### 4 Objet 3D
- Liste de sommets (coordonnées locales)
- Liste d’arêtes (paires d’indices de sommets)

### 5 Repères
- **Local** : chaque objet possède son propre repère
- **Monde** : tous les objets sont convertis dans un repère global

### 6 Caméra
- Définie par un repère propre (position + base orthonormée)
- Permet d'observer la scène depuis un point de vue donné

---

## 🔹 PHASE 3 — **Pipeline de rendu**

> Transformation complète d’un objet local jusqu’à sa projection sur un écran.

### 7 Étapes du pipeline
1. Objet (repère local) → repère monde  
2. Monde → repère caméra (vue)  
3. Caméra → plan image (projection perspective ou ortho)  
4. Plan image → écran (2D)

### 8 Projection
- Projection perspective (option : orthographique)
- Division par la profondeur (x/z, y/z)
- Application d'une *viewport* (fenêtre d'affichage)

---

## 🔹 PHASE 4 — **Affichage**

> Enfin, on trace les formes à l’écran. 

### 9 Rendu wireframe
- Transformation des sommets jusqu’à l’écran
- Tracé des arêtes entre les points projetés

### 10 Rasterisation simple
- Console : rendu ASCII, repère Y inversé
- SDL2 ou autre lib graphique : lignes 2D dans une fenêtre

---

## 🔹 PHASE 5 — **Interaction**

> On donne vie à la scène : zoom, rotation, déplacement…

### 11 Contrôles utilisateur
- Rotation de la caméra autour de l’objet
- Zoom / dézoom
- Translation latérale (*pan*)

### 12 Navigation & animation
- Mise à jour du repère caméra selon les entrées
- Rafraîchissement continu de l’affichage

---

## 🎉 Objectif final

Créer un visualisateur 3D **interactif** et **fluide**, qui permette de tourner autour d’un objet (genre une théière 🫖 ou autre), en mode *fil de fer*.

---

> ✨ Si j’arrive au bout : **je fais un post LinkedIn.**
















    
