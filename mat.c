#include "mat.h"

struct vect3_s{
    float x, y, z;
};

struct vect4_s{
    float w, x, y, z;
};

struct mat3_s{
    vect3 cols[3];
};

struct mat4_s{
    vect4 cols[4];
};

mat3 add_3(mat3 m1, mat3 m2){
    mat3 new_m;
    for(int i = 0 ; i < 3 ; i++){
        new_m.cols[i].x = m1.cols[i].x  + m2.cols[i].x;
        new_m.cols[i].y = m1.cols[i].y  + m2.cols[i].y;
        new_m.cols[i].z = m1.cols[i].z  + m2.cols[i].z;
    }
    return new_m;
}

mat4 add_4(mat4 m1, mat4 m2){
    mat4 new_m;
    for(int i = 0 ; i < 4 ; i++){
        new_m.cols[i].x = m1.cols[i].x  + m2.cols[i].x;
        new_m.cols[i].y = m1.cols[i].y  + m2.cols[i].y;
        new_m.cols[i].z = m1.cols[i].z  + m2.cols[i].z;
        new_m.cols[i].w = m1.cols[i].w  + m2.cols[i].w;
    }
    return new_m;
}

mat3 sous_3(mat3 m1, mat3 m2){
    mat3 new_m;
    for(int i = 0 ; i < 3 ; i++){
        new_m.cols[i].x = m1.cols[i].x  - m2.cols[i].x;
        new_m.cols[i].y = m1.cols[i].y  - m2.cols[i].y;
        new_m.cols[i].z = m1.cols[i].z  - m2.cols[i].z;
    }
    return new_m;
}

mat4 sous_4(mat4 m1, mat4 m2){
    mat4 new_m;
    for(int i = 0 ; i < 4 ; i++){
        new_m.cols[i].w = m1.cols[i].w  - m2.cols[i].w;
        new_m.cols[i].x = m1.cols[i].x  - m2.cols[i].x;
        new_m.cols[i].y = m1.cols[i].y  - m2.cols[i].y;
        new_m.cols[i].z = m1.cols[i].z  - m2.cols[i].z;
    }
    return new_m;
}

void affiche_3(mat3 m){
    printf("%f %f %f\n", m.cols[0].x, m.cols[1].x, m.cols[2].x);
    printf("%f %f %f\n", m.cols[0].y, m.cols[1].y, m.cols[2].y);
    printf("%f %f %f\n", m.cols[0].z, m.cols[1].z, m.cols[2].z);
    printf("\n");
}

void affiche_4(mat4 m){
    printf("%f %f %f %f\n", m.cols[0].w, m.cols[1].w, m.cols[2].w, m.cols[3].w);
    printf("%f %f %f %f\n", m.cols[0].x, m.cols[1].x, m.cols[2].x, m.cols[3].x);
    printf("%f %f %f %f\n", m.cols[0].y, m.cols[1].y, m.cols[2].y, m.cols[3].y);
    printf("%f %f %f %f\n", m.cols[0].z, m.cols[1].z, m.cols[2].z, m.cols[3].z);
    printf("\n");
}

float dot_product(vect3 v1, vect3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vect3 vector_cross_product(vect3 v1, vect3 v2) {
    vect3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

float norm(vect3 v){
    return sqrt(dot_product(v, v));
}

vect3 normalize(vect3 v){
    float n = norm(v);
    vect3 result;
    if (n != 0) {
        result.x = v.x / n;
        result.y = v.y / n;
        result.z = v.z / n;
    } else {
        result.x = 0;
        result.y = 0;
        result.z = 0;
    }
    return result;
}

mat3 product(mat3 m1, mat3 m2){
    mat3 result;
    for (int i = 0; i < 3; i++) {
            result.cols[i].x = m1.cols[0].x * m2.cols[i].x + m1.cols[1].x * m2.cols[i].y + m1.cols[2].x * m2.cols[i].z;
            result.cols[i].y = m1.cols[0].y * m2.cols[i].x + m1.cols[1].y * m2.cols[i].y + m1.cols[2].y * m2.cols[i].z;
            result.cols[i].z = m1.cols[0].z * m2.cols[i].x + m1.cols[1].z * m2.cols[i].y + m1.cols[2].z * m2.cols[i].z;
    }
    return result;
}

vect3 product_mat_vect3(mat3 m, vect3 v) {
    vect3 result;
    result.x = m.cols[0].x * v.x + m.cols[1].x * v.y + m.cols[2].x * v.z;
    result.y = m.cols[0].y * v.x + m.cols[1].y * v.y + m.cols[2].y * v.z;
    result.z = m.cols[0].z * v.x + m.cols[1].z * v.y + m.cols[2].z * v.z;
    return result;
}

mat3 rotation_mat(float angle, vect3 axis) {
    mat3 result;
    float c = cos(angle);
    float s = sin(angle);
    float t = 1 - c;

    result.cols[0].x = t * axis.x * axis.x + c;
    result.cols[0].y = t * axis.x * axis.y - s * axis.z;
    result.cols[0].z = t * axis.x * axis.z + s * axis.y;

    result.cols[1].x = t * axis.x * axis.y + s * axis.z;
    result.cols[1].y = t * axis.y * axis.y + c;
    result.cols[1].z = t * axis.y * axis.z - s * axis.x;

    result.cols[2].x = t * axis.x * axis.z - s * axis.y;
    result.cols[2].y = t * axis.y * axis.z + s * axis.x;
    result.cols[2].z = t * axis.z * axis.z + c;

    return result;
}
// Matrice de rotation autour de l'axe x et d'angle a : rotation_mat(a, (vect3){1, 0, 0});
// Matrice de rotation autour de l'axe y et d'angle a : rotation_mat(a, (vect3){0, 1, 0});
// Matrice de rotation autour de l'axe z et d'angle a : rotation_mat(a, (vect3){0, 0, 1});

float det2(float a, float b, float c, float d) {//Calcul du déterminant d'une matrice 2x2 utilisée pour le calcul de l'inverse d'une matrice 3x3
    return a * d - b * c;
}

float determinant(mat3 m) {
    return m.cols[0].x * (m.cols[1].y * m.cols[2].z - m.cols[1].z * m.cols[2].y) -
           m.cols[0].y * (m.cols[1].x * m.cols[2].z - m.cols[1].z * m.cols[2].x) +
           m.cols[0].z * (m.cols[1].x * m.cols[2].y - m.cols[1].y * m.cols[2].x);
}

mat3 mat_cofactrice(mat3 m) {
    mat3 result;

    result.cols[0].x = det2(m.cols[1].y, m.cols[2].y, m.cols[1].z, m.cols[2].z);
    result.cols[0].y = -det2(m.cols[1].x, m.cols[2].x, m.cols[1].z, m.cols[2].z);
    result.cols[0].z = det2(m.cols[1].x, m.cols[2].x, m.cols[1].y, m.cols[2].y);

    result.cols[1].x = -det2(m.cols[0].y, m.cols[2].y, m.cols[0].z, m.cols[2].z);
    result.cols[1].y = det2(m.cols[0].x, m.cols[2].x, m.cols[0].z, m.cols[2].z);
    result.cols[1].z = -det2(m.cols[0].x, m.cols[2].x, m.cols[0].y, m.cols[2].y);

    result.cols[2].x = det2(m.cols[0].y, m.cols[1].y, m.cols[0].z, m.cols[1].z);
    result.cols[2].y = -det2(m.cols[0].x, m.cols[1].x, m.cols[0].z, m.cols[1].z);
    result.cols[2].z = det2(m.cols[0].x, m.cols[1].x, m.cols[0].y, m.cols[1].y);

    return result;
}

mat3 transpose(mat3 m){
    mat3 result;

    result.cols[0].x = m.cols[0].x;
    result.cols[0].y = m.cols[1].x;
    result.cols[0].z = m.cols[2].x;
    result.cols[1].x = m.cols[0].y;
    result.cols[1].y = m.cols[1].y;
    result.cols[1].z = m.cols[2].y;
    result.cols[2].x = m.cols[0].z;
    result.cols[2].y = m.cols[1].z;
    result.cols[2].z = m.cols[2].z;

    return result;
}

mat3 inverse(mat3 m) {
    float det = determinant(m);
    if (det == 0) {
        fprintf(stderr, "Error: Matrix is not invertible (determinant is zero).\n");
        exit(EXIT_FAILURE);
    }

    mat3 cof = mat_cofactrice(m);
    mat3 adj = transpose(cof);

    mat3 result;
    for (int i = 0; i < 3; i++) {
        result.cols[i].x = adj.cols[i].x / det;
        result.cols[i].y = adj.cols[i].y / det;
        result.cols[i].z = adj.cols[i].z / det;
    }

    return result;
}

vect3 change_ref(vect3 v, mat3 base_ref, mat3 new_ref){
    mat3 inv_new_ref = inverse(new_ref);
    return product_mat_vect3(product(inv_new_ref, base_ref), v);
}

int main(){
    mat3 m;
    m.cols[0].x = 3.;
    m.cols[0].y = 0.;
    m.cols[0].z = 1.;
    m.cols[1].x = 2.;
    m.cols[1].y = 5.;
    m.cols[1].z = 2.;
    m.cols[2].x = 89.;
    m.cols[2].y = 6.;
    m.cols[2].z = 3.;

    affiche_3(inverse(m));
    /*
    mat3 m2 = add_3(m, m);
    affiche_3(m2);

    mat3 m3 = product(m, m2);
    affiche_3(m3);

    affiche_3(rotation_mat(M_PI / 4, (vect3){0, 0, 1})); */

    return 0;
}