#ifndef _SCENE_H_
#define _SCENE_H_

#include "mat.h"

typedef struct v_s {// Vertex
    vect3 position;
    float w;
} v;
/* (DOCUMENTATION .obj)
v x y z w

    Polygonal and free-form geometry statement.

    Specifies a geometric vertex and its x y z coordinates. Rational
    curves and surfaces require a fourth homogeneous coordinate, also
    called the weight.

    x y z are the x, y, and z coordinates for the vertex. These are
    floating point numbers that define the position of the vertex in
    three dimensions.

    w is the weight required for rational curves and surfaces. It is
    not required for non-rational curves and surfaces. If you do not
    specify a value for w, the default is 1.0.

    NOTE: A positive weight value is recommended. Using zero or
    negative values may result in an undefined point in a curve or
    surface.
*/

typedef vect3 vn; //Normal vector
/* (DOCUMENTATION .obj)
vn x y z

    Polygonal and free-form geometry statement.

    Specifies a normal vector with components x, y, and z.

    Vertex normals affect the smooth-shading and rendering of geometry.
    For polygons, vertex normals are used in place of the actual facet
    normals.  For surfaces, vertex normals are interpolated over the
    entire surface and replace the actual analytic surface normal.

    When vertex normals are present, they supersede smoothing groups.

    x y z are the x, y, and z coordinates for the vertex normal. They
    are floating point numbers.
*/

typedef struct vt_s {//Coordonnées de texture
    float u, v, w;
} vt;
/* (DOCUMENTATION .obj)
vt u v w

    Vertex statement for both polygonal and free-form geometry.

    Specifies a texture vertex and its coordinates. A 1D texture
    requires only u texture coordinates, a 2D texture requires both u
    and v texture coordinates, and a 3D texture requires all three
    coordinates.

    u is the value for the horizontal direction of the texture.

    v is an optional argument.

    v is the value for the vertical direction of the texture. The
    default is 0.

    w is an optional argument.

    w is a value for the depth of the texture. The default is 0.
*/

typedef struct face_part_s {//Partie de face
    int v, vt, vn;
} face_part;

typedef struct face_s {// Face
    face_part sommet[3];
} face;
/* (DOCUMENTATION .obj)

f v/vt/vn v/vt/vn v/vt/vn ...

    Polygonal geometry statement.

    Specifies a face with vertices, texture coordinates, and vertex
    normals. The face is defined by a list of vertices, each of which
    can have an associated texture coordinate and vertex normal.

    v is the vertex index. It is a positive integer that refers to a
    vertex defined by the v statement.

    vt is the texture coordinate index. It is an optional positive
    integer that refers to a texture coordinate defined by the vt
    statement.

    vn is the vertex normal index. It is an optional positive integer
    that refers to a vertex normal defined by the vn statement.
*/

typedef struct vp_s {//Vertex properties
    float u, v, w;
} vp;
/* (DOCUMENTATION .obj)
vp u v w
    
    Free-form geometry statement.

    Specifies a point in the parameter space of a curve or surface.

    The usage determines how many coordinates are required. Special
    points for curves require a 1D control point (u only) in the
    parameter space of the curve. Special points for surfaces require a
    2D point (u and v) in the parameter space of the surface. Control
    points for non-rational trimming curves require u and v
    coordinates. Control points for rational trimming curves require u,
    v, and w (weight) coordinates.

    u is the point in the parameter space of a curve or the first
    coordinate in the parameter space of a surface.

    v is the second coordinate in the parameter space of a surface.

    w is the weight required for rational trimming curves. If you do
    not specify a value for w, it defaults to 1.0.

    NOTE: For additional information on parameter vertices, see the
    curv2 and sp statements
*/

typedef struct item_s {
    v* tab_sommets;
    vn* tab_normales;
    vt* tab_text;
    face* tab_faces;
    vp* tab_props;
    signed long long int taille_tab_sommets;
    signed long long int taille_tab_normales;
    signed long long int taille_tab_text;
    signed long long int taille_tab_faces;
    signed long long int taille_tab_props;
    signed long long int cpt_sommets;
    signed long long int cpt_normales;
    signed long long int cpt_text;
    signed long long int cpt_faces;
    signed long long int cpt_props;
    vect3 u1; //Vecteur de base servant de référence pour les sommets
    vect3 u2; //Vecteur de base servant de référence pour les sommets
    vect3 u3; //Vecteur de base servant de référence pour les sommets
    vect3 origine;
} item;

typedef struct camera_s {
    vect3 position; //Position de la caméra selon le repère monde
    vect3 u1; //Vecteur de base pour référence
    vect3 u2; //Vecteur de base pour référence
    vect3 u3; //Vecteur de base pour référence
} camera;

typedef struct scene_s {
    item* items; //Tableau d'items
    camera cam; //Caméra de la scène
    int cpt_items; //Compteur d'items dans la scène
    int taille_tab_items; //Taille du tableau d'items
} scene;

void ajouter_sommet(item*, v);
void ajouter_normale(item*, vn);
void ajouter_texture(item*, vt);
void ajouter_prop(item*, vp);
void ajouter_face(item*, face);
//Fonction de rajout d'élément dans un item, complexité amortie pour les tableaux dynamiques (O(1), doublage de la taille des tableaux si besoin).

item deserialize_item(const char*); //Fonction de désérialisation d'un item à partir d'un fichier .obj simple (composé uniquement de v, vn, vt, f).
void free_item(item*); //Libère la mémoire allouée pour un item

void rotate_item(item*, float, vect3); //Applique une rotation à l'item autour d'un axe donné
void translate_item(item*, vect3); //Applique une translation à l'item

void rotate_camera(scene*, float, vect3); //Applique une rotation à la caméra de la scène
void translate_camera(scene*, vect3); //Applique une translation à la caméra de la scène

void ajouter_item(scene*, item); //Ajoute un item à la scène

void change_ref_item_scene(scene*); //Change la référence des items de la scène pour qu'ils soient dans le repère de la caméra 
//Permet de préparer le terrain pour l'affichage en 3D

void free_scene(scene*); //Libère la mémoire allouée pour une scène
// /!\ Attention, cette fonction libère la memoire allouée pour les items de la scene

#endif