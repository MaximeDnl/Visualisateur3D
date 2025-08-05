# Visualisateur3D  
**Projet personnel en C : moteur de rendu 3D from scratch**
 
L'objectif : construire un visualisateur 3D (ou un mini moteur de rendu), étape par étape dans le langage de programmation C, en comprenant chaque brique.  
Ci-dessous est décrit les différentes étapes du projet, et si j'y arrive, les références avec les fichiers correspondants (:

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

## 🔹 PHASE 2 — **Représentation de la scène** (Finie, 4 testée, 5 non testée)

> On passe de la théorie à la modélisation d’objets 3D et de leur place dans une scène globale.

### 4 Objet 3D (Complété)
- Liste de sommets, textures, normales, faces (coordonnées locales) ✅
- Désérialisation fichier simple .obj (composé uniquement de v, vn, vt, f) ✅

### 5 Repères (Complété)
- **Local** : chaque objet possède son propre repère ✅
- **Caméra** : repère propre (position + base orthonormée) afin d'observer la scène depuis un point de vue donné ✅
- **Monde** : tous les objets sont convertis dans un repère global, celui de la caméra ✅

---

## 🔹 PHASE 3 — **Pipeline de rendu** (En cours)

> Transformation complète d’un objet local jusqu’à sa projection sur un écran.

### 6 Étapes du pipeline (En cours)
1. Objet (repère local) → repère monde   ✅
2. Monde → repère caméra (vue) ✅
3. Caméra → plan image (projection perspective ou ortho)  
4. Plan image → écran (2D)

### 7 Projection
- Projection perspective (option : orthographique)
- Division par la profondeur (x/z, y/z)
- Application d'une *viewport* (fenêtre d'affichage)

---

## 🔹 PHASE 4 — **Affichage**

> Enfin, on trace les formes à l’écran. 

### 8 Rendu wireframe
- Transformation des sommets jusqu’à l’écran
- Tracé des arêtes entre les points projetés
- Nuance de lumière avec méthode de Lambert

### 9 Rasterisation simple
- Console : rendu ASCII, repère Y inversé
- SDL2 ou autre lib graphique : lignes 2D dans une fenêtre

---

## 🔹 PHASE 5 — **Interaction**

> On donne vie à la scène : zoom, rotation, déplacement…

### 10 Contrôles utilisateur
- Rotation de la caméra autour de l’objet
- Zoom / dézoom
- Translation latérale (*pan*)

### 11 Navigation & animation
- Mise à jour du repère caméra selon les entrées
- Rafraîchissement continu de l’affichage

---

## 🎉 Objectif final

Créer un visualisateur 3D **interactif** et **fluide**, qui permette de tourner autour d’un objet (genre une théière 🫖 ou autre), en mode *fil de fer*.

---

> ✨ Si j’arrive au bout : **je fais un post LinkedIn.**

## Sources :
https://fr.wikipedia.org/wiki/Objet_3D_(format_de_fichier)
https://fr.wikipedia.org/wiki/Projection_centrale
















    
