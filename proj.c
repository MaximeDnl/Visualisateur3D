#include "proj.h"

plan* init_plan(int longueur, int largeur){
    plan *p = malloc(sizeof(plan));
    p->longueur = longueur;
    p->largeur = largeur;
    p->positions_x = NULL;
    p->positions_y = NULL;
    p->taille_positions = 0;
    p->cpt_positions = 0;
    return p;
}

void free_plan(plan* p){
    free(p->positions_x);
    free(p->positions_y);
    free(p);
}

void projeter_sommet(plan* p, vect3 sommet){
    float x = sommet.x / sommet.z; // Projection perspective
    float y = sommet.y / sommet.z; // Projection perspective

    if(p-> taille_positions == p->cpt_positions){
        if(p->taille_positions == 0){
            p->taille_positions = 1;
        } 
        else{
            p->taille_positions *= 2;
        }
        p->positions_x = realloc(p->positions_x, sizeof(float) * p->taille_positions);
        p->positions_y = realloc(p->positions_y, sizeof(float) * p->taille_positions);
    }

    float scale = 400.0;
    p->positions_x[p->cpt_positions] = x * scale + (p->longueur / 2); // Décalage pour centrer dans le plan
    p->positions_y[p->cpt_positions] = y * scale + (p->largeur / 2); // Décalage pour centrer dans le plan
    p->cpt_positions++;
}

plan* projeter_scene(scene* sc) {
    plan* p = init_plan(1000, 1000); // Initialisation d'un plan de projection de 100x100 unités
    change_ref_item_scene(sc); // Changement de référence de la caméra pour projeter

    for(int i = 0; i < sc->cpt_items; i++){
        item* it = &sc->items[i];
        for(int j = 0; j < it->cpt_sommets; j++){
            projeter_sommet(p, it->tab_sommets[j].position);
        }
    }

    return p;
}

void dessiner_boule(JSAMPLE* buffer, int largeur, int longueur, int cx, int cy, int r, JSAMPLE r_color, JSAMPLE g_color, JSAMPLE b_color){
    for (int y = cy - r; y <= cy + r; y++) {
        for (int x = cx - r; x <= cx + r; x++) {
            if (x >= 0 && x < largeur && y >= 0 && y < longueur) {
                int dx = x - cx;
                int dy = y - cy;
                if (dx*dx + dy*dy <= r*r) { // à l’intérieur du cercle
                    int idx = (y * largeur + x) * 3;
                    buffer[idx + 0] = r_color; // Rouge
                    buffer[idx + 1] = g_color; // Vert
                    buffer[idx + 2] = b_color; // Bleu
                }
            }
        }
    }
}

void dessiner_segment(JSAMPLE* buffer, int largeur, int longueur, int x0, int y0, int x1, int y1, JSAMPLE r, JSAMPLE g, JSAMPLE b) {
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);

    int sx, sy;
    if(x0 < x1){
        sx = 1;
    } 
    else {
        sx = -1;
    }
    if(y0 < y1){
        sy = 1;
    } 
    else {
        sy = -1;
    }

    int err = dx + dy;
    int e2;

    int max_steps = largeur + longueur; // or some large enough value
    int steps = 0;
    while (true) {
        if (x0 >= 0 && x0 < largeur && y0 >= 0 && y0 < longueur) {
            int idx = (y0 * largeur + x0) * 3;
            buffer[idx + 0] = r;
            buffer[idx + 1] = g;
            buffer[idx + 2] = b;
        }
        if (x0 == x1 && y0 == y1) {
            break;
        }
        if (++steps > max_steps) {
            // Prevent infinite loop
            break;
        }
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void affichage_plan(plan* p, scene* sc, char* fichier){
    FILE *outfile = fopen(fichier, "wb");

    if(!outfile){
        perror("Erreur ouverture fichier sortie");
        return;
    }

    JSAMPLE* buffer = malloc(p->largeur * p->longueur * 3 * sizeof(JSAMPLE)); // Buffer pour les pixels RGB
    // Puisque la librairie jpeglib remplit le jpeg ligne par ligne.

    // Initialisation du buffer
    for(int i = 0; i < p->largeur * p->longueur * 3; i++){
        buffer[i] = 0; // Initialisation à noir
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr); //Permet de gérer les erreurs de compression JPEG
    jpeg_create_compress(&cinfo);

    jpeg_stdio_dest(&cinfo, outfile); // Permet de définir le fichier de sortie pour la compression JPEG

    cinfo.image_width = p->longueur;
    cinfo.image_height = p->largeur;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo); // Initialise les paramètres par défaut de la compression JPEG
    jpeg_set_quality(&cinfo, 90, TRUE); // Définit la qualité de compression JPEG (90% ici)

    jpeg_start_compress(&cinfo, TRUE); // Commence la compression JPEG

    for(int i = 0; i < p->cpt_positions; i++){
        if(p->positions_x[i] >= 0 || p->positions_x[i] < p->longueur || p->positions_y[i] >= 0 || p->positions_y[i] < p->largeur){
        /* int idx = (int)((p->positions_y[i] * p->largeur + p->positions_x[i]) * 3);

        buffer[idx + 0] = 255; // Rouge
        buffer[idx + 1] = 0;   // Vert
        buffer[idx + 2] = 0;   // Bleu  */
        dessiner_boule(buffer, p->longueur, p->largeur, (int)p->positions_x[i], (int)p->positions_y[i], 3, 225, 0, 0); // Dessine une boule rouge de rayon 10
        }
    }

    for(int i = 0 ; i < sc->cpt_items; i++){
        for(int num_face = 0; num_face < sc->items[i].cpt_faces ; num_face++){
            face f = sc->items[i].tab_faces[num_face]; // On prend la première face de l'item pour dessiner les segments
            int idx0 = f.sommet[0].v;
            int idx1 = f.sommet[1].v;
            int idx2 = f.sommet[2].v;
            //printf("Face %d de l'item %d : sommets %d, %d, %d\n", num_face, i, idx0, idx1, idx2);

            dessiner_segment(buffer, p->longueur, p->largeur, (int)p->positions_x[idx0], (int)p->positions_y[idx0], (int)p->positions_x[idx1], (int)p->positions_y[idx1], 0, 255, 0);
            dessiner_segment(buffer, p->longueur, p->largeur, (int)p->positions_x[idx1], (int)p->positions_y[idx1], (int)p->positions_x[idx2], (int)p->positions_y[idx2], 0, 255, 0);
            dessiner_segment(buffer, p->longueur, p->largeur, (int)p->positions_x[idx2], (int)p->positions_y[idx2], (int)p->positions_x[idx0], (int)p->positions_y[idx0], 0, 255, 0);
        }
    }

    //dessiner_segment(buffer, p->longueur, p->largeur, (int)p->positions_x[3], (int)p->positions_y[3], (int)p->positions_x[1], (int)p->positions_y[1], 0, 255, 0);

    //dessiner_boule(buffer, p->longueur, p->largeur, 25, 25, 100, 255, 0, 0); // Dessine une boule rouge de rayon 10
        
    for (int y = 0; y < p->largeur; y++){ // Ecriture du jpeg ligne par ligne
        JSAMPROW ligne = &buffer[y * p->largeur * 3];
        jpeg_write_scanlines(&cinfo, &ligne, 1);
    }

    free(buffer); // Libération du buffer

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);
}


int main(){
    item it = deserialize_item("cow.obj");
    
    scene sc = init_scene();
    sc.cam.position = (vect3){0, 0, -8}; //Pour cow
    //sc.cam.position = (vect3){0, 2, -4.3}; //Pour teapot

    ajouter_item(&sc, it);

    rotate_item(&sc.items[0], M_PI, sc.items[0].u3);

    plan* p = projeter_scene(&sc); // Re-projeter la scène après rotation
    affichage_plan(p, &sc, "projection001.jpg");
   
    int steps = 361; // Number of frames in the circle

    for(int i = 0; i < steps; i++){
        free_plan(p);
        usleep(500000);

        //printf("%d\n", i);
        rotate_item(&sc.items[0], (M_PI * 2) / 360, sc.items[0].u2);
        //rotate_camera(&sc, (M_PI*2)/360, sc.cam.u2);

        p = projeter_scene(&sc);
        affichage_plan(p, &sc, "projection.jpg"); // Save the projection to a file
    }

    free_scene(&sc);
    free_plan(p);

    return 0;
}

//Executer le main après la commande : gcc -Wextra -Werror -pedantic -fsanitize=address -o main proj.c scene.c mat.c -lm -ljpeg
//Calcul dans "projection.jpg" les différentes images de la vaches tournant sur elle-même