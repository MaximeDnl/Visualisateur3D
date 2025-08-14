#include "scene.h"

void ajouter_sommet(item* it, v sommet) {
    if (it->taille_tab_sommets == it->cpt_sommets){
        if(it->taille_tab_sommets == 0){
            it->taille_tab_sommets = 1;
        } else {
            it->taille_tab_sommets *= 2;
        }
        it->tab_sommets = realloc(it->tab_sommets, sizeof(v) * it->taille_tab_sommets);
    }
    it->tab_sommets[it->cpt_sommets] = sommet;
    it->cpt_sommets++;
}

void ajouter_normale(item* it, vn normale) {
    if (it->taille_tab_normales == it->cpt_normales){
        if(it->taille_tab_normales == 0){
            it->taille_tab_normales = 1;
        } else {
            it->taille_tab_normales *= 2;
        }
        it->tab_normales = realloc(it->tab_normales, sizeof(vn) * it->taille_tab_normales);
    }
    it->tab_normales[it->cpt_normales] = normale;
    it->cpt_normales++;
}

void ajouter_texture(item* it, vt tex) {
    if (it->taille_tab_text == it->cpt_text){
        if(it->taille_tab_text == 0){
            it->taille_tab_text = 1;
        } else {
            it->taille_tab_text *= 2;
        }
        it->tab_text = realloc(it->tab_text, sizeof(vt) * it->taille_tab_text);
    }
    it->tab_text[it->cpt_text] = tex;
    it->cpt_text++;
}

void ajouter_prop(item* it, vp prop) {
    if (it->taille_tab_props == it->cpt_props){
        if(it->taille_tab_props == 0){
            it->taille_tab_props = 1;
        } else {
            it->taille_tab_props *= 2;
        }
        it->tab_props = realloc(it->tab_props, sizeof(vp) * it->taille_tab_props);
    }
    it->tab_props[it->cpt_props] = prop;
    it->cpt_props++;
}

void ajouter_face(item* it, face f) {
    if (it->taille_tab_faces == it->cpt_faces){
        if(it->taille_tab_faces == 0){
            it->taille_tab_faces = 1;
        } else {
            it->taille_tab_faces *= 2;
        }
        it->tab_faces = realloc(it->tab_faces, sizeof(face) * it->taille_tab_faces);
    }
    it->tab_faces[it->cpt_faces] = f;
    it->cpt_faces++;
}

item deserialize_item(const char* line) {
    item it;
    it.tab_sommets = NULL;
    it.tab_normales = NULL;
    it.tab_text = NULL;
    it.tab_faces = NULL;
    it.tab_props = NULL;
    it.cpt_sommets = 0;
    it.cpt_normales = 0;
    it.cpt_text = 0;
    it.cpt_faces = 0;
    it.cpt_props = 0;
    it.taille_tab_sommets = 0; 
    it.taille_tab_normales = 0; 
    it.taille_tab_text = 0;      
    it.taille_tab_faces = 0;    
    it.taille_tab_props = 0;      

    FILE* f = fopen(line, "r");

    if(!f){ 
        perror("Erreur d'ouverture"); 
        exit(1); 
    }
    else{
        char ligne[256];
        while(fgets(ligne, sizeof(ligne), f)){
            if (strncmp(ligne, "v ", 2) == 0) {
                v sommet;
                int n = sscanf(ligne + 2, "%f %f %f %f", &sommet.position.x, &sommet.position.y, &sommet.position.z, &sommet.w);
                if(n < 4){
                    sommet.w = 1.0;
                }
                ajouter_sommet(&it, sommet);
            } 
            else if (strncmp(ligne, "vn ", 3) == 0) {
                vn normale;
                sscanf(ligne + 3, "%f %f %f", &normale.x, &normale.y, &normale.z);
                ajouter_normale(&it, normale);
            } 
            else if (strncmp(ligne, "vt ", 3) == 0) {
                vt tex;
                int n = sscanf(ligne + 3, "%f %f %f", &tex.u, &tex.v, &tex.w);
                if(n == 1){
                    tex.v = 0.0;
                    tex.w = 0.0;
                }
                else if(n == 2){
                    tex.w = 0.0;
                }
                ajouter_texture(&it, tex);
            } 
            else if (strncmp(ligne, "vp ", 3) == 0) {
                vp prop;
                int n = sscanf(ligne + 3, "%f %f %f", &prop.u, &prop.v, &prop.w);
                if(n < 3){
                    prop.w = 0.0;
                }
                ajouter_prop(&it, prop);
            } 
            else if (strncmp(ligne, "f ", 2) == 0) {
                char* ptr = ligne + 2;
                int i = 0;
                face f;
                while(i < 3){
                    int v, vt, vn;
                    if(sscanf(ptr, "%d/%d/%d", &v, &vt, &vn) == 3){
                        // Format v/vt/vn
                        f.sommet[i].v = v - 1; // Indices commencent à 1 dans .obj, on les ramène à 0
                        f.sommet[i].vt = vt - 1;
                        f.sommet[i].vn = vn - 1;
                    } 
                    else if(sscanf(ptr, "%d//%d", &v, &vn) == 2){
                        // Format v//vn
                        f.sommet[i].v = v - 1;
                        f.sommet[i].vt = -1; // Pas de coordonnée de texture
                        f.sommet[i].vn = vn - 1; 
                    }
                    else if(sscanf(ptr, "%d/%d", &v, &vt) == 2){
                        // Format v/vt
                        f.sommet[i].v = v - 1;
                        f.sommet[i].vt = vt - 1;
                        f.sommet[i].vn = -1; // Pas de normale
                    } 
                    else if(sscanf(ptr, "%d", &v) == 1) {
                        // Format v
                        f.sommet[i].v = v - 1;
                        f.sommet[i].vt = -1; // Pas de coordonnée de texture
                        f.sommet[i].vn = -1; // Pas de normale
                    } 
                    else{
                        perror("Erreur lecture face"); 
                        exit(1); 
                    }
                    ptr = strchr(ptr, ' ');
                    if(!ptr){
                        break;
                    }
                    ptr++; // avancer vers le triplet suivant
                    i++;
                }
                ajouter_face(&it, f);
            }
        }
    }

    //Utilisation de la base canonique
    it.u1 = (vect3){1, 0, 0};
    it.u2 = (vect3){0, 1, 0};
    it.u3 = (vect3){0, 0, 1};

    it.origine = (vect3){0, 0, 0}; // Origine de l'item

    return it;
}

void free_item(item* it) {
    free(it->tab_sommets);
    free(it->tab_normales);
    free(it->tab_text);
    free(it->tab_faces);
    free(it->tab_props);
}

void rotate_item(item* it, float angle, vect3 axis){
    mat3 rotation = rotation_mat(angle, axis);
    for (int i = 0; i < it->cpt_sommets; i++){
        it->tab_sommets[i].position.x -= it->origine.x; // Déplacer le sommet par rapport à l'origine
        it->tab_sommets[i].position.y -= it->origine.y;
        it->tab_sommets[i].position.z -= it->origine.z;
        it->tab_sommets[i].position = product_mat_vect3(rotation, it->tab_sommets[i].position); // Appliquer la rotation
        it->tab_sommets[i].position.x += it->origine.x; // Replacer le sommet à sa position d'origine
        it->tab_sommets[i].position.y += it->origine.y;
        it->tab_sommets[i].position.z += it->origine.z;
    }
    // Mettre à jour les vecteurs de base
    it->u1 = product_mat_vect3(rotation, it->u1);
    it->u2 = product_mat_vect3(rotation, it->u2);
    it->u3 = product_mat_vect3(rotation, it->u3);
}

void translate_item(item* it, vect3 translation) {
    for (int i = 0; i < it->cpt_sommets; i++) {
        it->tab_sommets[i].position.x += translation.x;
        it->tab_sommets[i].position.y += translation.y;
        it->tab_sommets[i].position.z += translation.z;
    }

    it->origine.x += translation.x;
    it->origine.y += translation.y;
    it->origine.z += translation.z;
}

void rotate_camera(scene* sc, float angle, vect3 axis) {
    mat3 rotation = rotation_mat(angle, axis);
    //sc->cam.position = product_mat_vect3(rotation, sc->cam.position);
    sc->cam.u1 = product_mat_vect3(rotation, sc->cam.u1);
    sc->cam.u2 = product_mat_vect3(rotation, sc->cam.u2);
    sc->cam.u3 = product_mat_vect3(rotation, sc->cam.u3);

    //change_ref_item_scene(sc); // Met à jour les références des items de la scène
}

void translate_camera(scene* sc, vect3 translation) {
    sc->cam.position.x += translation.x;
    sc->cam.position.y += translation.y;
    sc->cam.position.z += translation.z;
}

scene init_scene(){
    scene sc;
    sc.items = NULL;
    sc.items_ref_perso = NULL;
    sc.cam.position = (vect3){0, 0, 0}; // Position de la caméra
    sc.cam.u1 = (vect3){1, 0, 0}; // Vecteur de base pour référence
    sc.cam.u2 = (vect3){0, 1, 0}; // Vecteur de base pour référence
    sc.cam.u3 = (vect3){0, 0, 1}; // Vecteur de base pour référence
    sc.taille_tab_items = 0; // Taille du tableau d'items
    sc.cpt_items = 0; // Compteur d'items dans la scène
    return sc;
}

void ajouter_item(scene* sc, item it) {
    if(sc->cpt_items == sc->taille_tab_items){
        if(sc->taille_tab_items == 0){
            sc->taille_tab_items = 1;
        } 
        else{
            sc->taille_tab_items *= 2;
        }
        item* tmp_items = realloc(sc->items, sizeof(item) * sc->taille_tab_items);
        if (!tmp_items) { perror("realloc items failed"); exit(1); }
        sc->items = tmp_items;

        item* tmp_items_ref = realloc(sc->items_ref_perso, sizeof(item) * sc->taille_tab_items);
        if (!tmp_items_ref) { perror("realloc items_ref_perso failed"); exit(1); }
        sc->items_ref_perso = tmp_items_ref;
    }
    sc->items[sc->cpt_items] = it;
    sc->items_ref_perso[sc->cpt_items] = it;

    // On change la ref de l'item pour qu'il soit dans le repère de la caméra
    mat3 base_ref = {it.u1, it.u2, it.u3} ;
    mat3 new_ref = {sc->cam.u1, sc->cam.u2, sc->cam.u3};
    (&sc->items[sc->cpt_items])->u1 = normalize(change_ref(it.u1, base_ref, new_ref));
    (&sc->items[sc->cpt_items])->u2 = normalize(change_ref(it.u2, base_ref, new_ref));
    (&sc->items[sc->cpt_items])->u3 = normalize(change_ref(it.u3, base_ref, new_ref));
    for(int j = 0; j < it.cpt_sommets; j++){
        (&sc->items[sc->cpt_items])->tab_sommets[j].position = change_ref(it.tab_sommets[j].position, base_ref, new_ref);
        (&sc->items[sc->cpt_items])->tab_sommets[j].position.x = it.tab_sommets[j].position.x - sc->cam.position.x; //Afin de placer correctement les sommets dans le repère de la caméra
        (&sc->items[sc->cpt_items])->tab_sommets[j].position.y = it.tab_sommets[j].position.y - sc->cam.position.y;
        (&sc->items[sc->cpt_items])->tab_sommets[j].position.z = it.tab_sommets[j].position.z - sc->cam.position.z;
    }
    sc->cpt_items++;
}

void change_ref_item_scene(scene* sc){//Idée est de changer les références des items de la scène pour qu'ils soient dans le repère de la caméra
    for(int i = 0; i < sc->cpt_items; i++){
        item* it = &sc->items_ref_perso[i];
        item* it_ref_cam = &sc->items[i];
        mat3 base_ref = {it->u1, it->u2, it->u3} ;
        mat3 new_ref = {sc->cam.u1, sc->cam.u2, sc->cam.u3};
        it_ref_cam->u1 = normalize(change_ref(it->u1, base_ref, new_ref));
        it_ref_cam->u2 = normalize(change_ref(it->u2, base_ref, new_ref));
        it_ref_cam->u3 = normalize(change_ref(it->u3, base_ref, new_ref));
        it_ref_cam->origine = change_ref(it->origine, base_ref, new_ref);
        it_ref_cam->origine.x = it->origine.x - sc->cam.position.x; // Afin de placer correctement l'origine dans le repère de la caméra
        it_ref_cam->origine.y = it->origine.y - sc->cam.position.y;
        it_ref_cam->origine.z = it->origine.z - sc->cam.position.z;

        for(int j = 0; j < it->cpt_sommets; j++){
            it_ref_cam->tab_sommets[j].position = change_ref(it->tab_sommets[j].position, base_ref, new_ref);;
            /* it_ref_cam->tab_sommets[j].position.x = it->tab_sommets[j].position.x - sc->cam.position.x; //Afin de placer correctement les sommets dans le repère de la caméra
            it_ref_cam->tab_sommets[j].position.y = it->tab_sommets[j].position.y - sc->cam.position.y;
            it_ref_cam->tab_sommets[j].position.z = it->tab_sommets[j].position.z - sc->cam.position.z; */
        }
    }
}

void free_scene(scene* sc) {
    if (!sc) return;

    for(int i = 0; i < sc->cpt_items; i++) {
        free_item(&sc->items[i]); // libèration des ressources de chaque item
    }

    free(sc->items);
    sc->items = NULL;

    free(sc->items_ref_perso);
    sc->items_ref_perso = NULL;

    sc->cpt_items = 0;
    sc->taille_tab_items = 0;
}