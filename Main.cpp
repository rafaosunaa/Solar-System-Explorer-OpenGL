#include <GL/freeglut_std.h>
#include "SistemaSolar.h"

/**
 * @file SistemaSolar.cpp
 * @brief Sistema Solar - Representación gráfica del sistema solar en OpenGL.
 * Autor:  Rafael Osuna Ventura <rov00005@red.ujaen.es>
 */

int main(int argc, char **argv) {
    // Inicialización de GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Proyecto Sistema Solar");

    // Configuración del sistema solar (escena)
    representarSistemaSolar(); // Configura el grafo de escena del sistema solar



    return 0; // GLUT toma el control, normalmente no se llega aquía
}
