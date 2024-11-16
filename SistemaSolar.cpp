// SistemaSolar.cpp

#include "SistemaSolar.h"

#if defined(__APPLE__) && defined(__MACH__)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

using namespace std;


// Inicialización de las variables globales definidas en el .h
Vista vistaActual = VISTA_NORMAL;
Planeta *planetaSeleccionado = nullptr;
vector<Planeta *> planetas;
igvTextura *fondo = nullptr;

double multiplicarTiempo = 0.03;
double contadorReloj = 0;
double zoom = 2;
double arrastrarX = -1;
double arrastrarY = -1;
double mouseX;
double mouseY;

/**
 * @brief Moverse entre planetas.
 * Esta función permite cambiar el planeta seleccionado.
 * @param indice Índice del planeta al que se quiere mover.
 */
void movermeEntrePlanetas(int indice) {
    if (indice >= 0 && indice < planetas.size()) {
        planetaSeleccionado = planetas[indice];
    }
}

/**
 * @brief Cambiar la vista de la cámara.
 * Esta función ajusta la perspectiva de la cámara entre las distintas vistas.
 */
void cambiarVista() {
    switch (vistaActual) {
        case VISTA_NORMAL:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60.0, (GLfloat) glutGet(GLUT_WINDOW_WIDTH) / (GLfloat) glutGet(GLUT_WINDOW_HEIGHT), 1.0,
                           1500.0);
            glMatrixMode(GL_MODELVIEW);
            break;
        case VISTA_PLANTA:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom); // Ortho para vista de planta
            glMatrixMode(GL_MODELVIEW);
            break;
        case VISTA_PERFIL:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom); // Ortho para vista de perfil
            glRotatef(90.0, 0.0, 0.0, 1.0); // Girar para vista de perfil
            glMatrixMode(GL_MODELVIEW);
            break;
    }
}

/**
 * @brief Muestra la información del planeta seleccionado.
 * Imprime en la consola detalles como nombre, aphelion, perihelion y período orbital.
 */
void mostrarInfoPlaneta() {
    if (planetaSeleccionado != nullptr) {
        cout << "Informacion de " << planetaSeleccionado->nombre << ":" << endl;
        cout << "Aphelion: " << planetaSeleccionado->aphelion << endl;
        cout << "Perihelion: " << planetaSeleccionado->perihelion << endl;
        cout << "Periodo Orbital: " << planetaSeleccionado->periodoOrbital << endl;
    }
}

/**
 * @brief Maneja el movimiento del ratón para controlar la cámara.
 * Captura el movimiento y el estado del ratón para ajustar la vista.
 * @param key Botón del ratón (0: izquierdo, 1: derecho)
 * @param estado Estado del botón (presionado o no)
 * @param x Coordenada X del ratón
 * @param y Coordenada Y del ratón
 */
void moviminetoRaton(int key, int estado, int x, int y) {
    switch (key) {
        case 0: // Botón izquierdo del ratón
            if (estado == 0) {
                // Si el botón está presionado
                if (arrastrarX == -1) {
                    arrastrarX = x;
                    arrastrarY = y;
                } else {
                    arrastrarX += x - mouseX; // Ajusta el desplazamiento en X
                    arrastrarY += y - mouseY; // Ajusta el desplazamiento en Y
                }
                mouseX = x; // Actualiza la posición X del ratón
                mouseY = y; // Actualiza la posición Y del ratón
            }
            break;
        case 1: // Botón derecho del ratón
            break;
        default:
            break;
    }
}

/**
 * @brief Actualiza el movimiento de la cámara basado en el ratón.
 * @param x Coordenada X del ratón
 * @param y Coordenada Y del ratón
 */
void movimientoCamara(int x, int y) {
    mouseX = x;
    mouseY = y;
}

/**
 * @brief Dibuja el movimiento de la cámara y representa el fondo y los planetas.
 */
void dibujarMovimiento() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double x, y, z;
    const double mitadPI = 3.1416 / 180;

    x = sin((-mouseX + arrastrarX) * mitadPI) * cos((mouseY - arrastrarY) * mitadPI) * zoom;
    y = sin((mouseY - arrastrarY) * mitadPI) * zoom;
    z = cos((-mouseX + arrastrarX) * mitadPI) * cos((mouseY - arrastrarY) * mitadPI) * zoom;

    gluLookAt(planetaSeleccionado->pX + x, planetaSeleccionado->pY + y, planetaSeleccionado->pZ + z,
              planetaSeleccionado->pX, planetaSeleccionado->pY, planetaSeleccionado->pZ, 0.0, 1.0, 0.0);

    glPushMatrix();

    fondo->fondo();

    for (size_t i = 0; i < planetas.size(); i++) {
        planetas[i]->dibujarPlaneta();
    }

    glPopMatrix();

    glutSwapBuffers();
}

/**
 * @brief Maneja los eventos del teclado para controlar el zoom, velocidad y cambio de vista.
 * @param key Código de la tecla pulsada
 * @param x Coordenada X del ratón al pulsar la tecla
 * @param y Coordenada Y del ratón al pulsar la tecla
 */
void keyboardFunc(unsigned char key, int x, int y) {
    int indice = key - '0';
    switch (key) {
        case '-':
            zoom++;
            break;
        case '+':
            zoom--;
            break;
        case 'a':
            multiplicarTiempo /= multiplicarTiempo < 0.001 ? 1 : 2;
            break;
        case 'd':
            multiplicarTiempo *= multiplicarTiempo > 10 ? 1 : 2;
            break;

        case 'v':
            // Alternar entre vistas al presionar 'p' o 'P' o 'v' o 'V'
            vistaActual = static_cast<Vista>((vistaActual + 1) % 3);
            cambiarVista(); // Llamar a cambiarVista() después de cambiar la vista
            break;

        case 27: // Tecla ESC para salir
            exit(1);
            break;
    }

    if (indice >= 0 && indice < planetas.size()) {
        planetaSeleccionado = planetas[indice];
        mostrarInfoPlaneta();
    }

    glutPostRedisplay();
}


/**
 * @brief Crea los planetas del sistema solar y los agrega al vector planetas.
 */
void crearPlanetas() {
    int escala = 20;

    planetas.push_back(new Planeta("Sol", 0, 0, 0, 20, "../imagenes/Sol.jpg", 109 / 20., 1.0));
    planetas.push_back(new Planeta("Mercurio", 7.0 * escala, 4.6 * escala, 0.24, 58.82, "../imagenes/Mercurio.jpg", .38,
                                   1.0));
    planetas.push_back(new Planeta("Venus", 10.893 * escala, 10.747 * escala, 0.61, 243, "../imagenes/Venus.jpg", .815,
                                   1.0));
    planetas.push_back(
        new Planeta("Tierra", 15.19 * escala, 14.95 * escala, 4.15, 1, "../imagenes/Tierra.jpg", 1, 25.0));
    planetas.push_back(new Planeta("Marte", 20.67 * escala, 24.92 * escala, 1.8821, 1, "../imagenes/Marte.jpg", .53,
                                   23.0));
    planetas.push_back(new Planeta("Jupiter", 81.6 * escala, 74.05 * escala, 11.86, 0.41, "../imagenes/Jupiter.jpg", 11,
                                   1));
    planetas.push_back(new Planeta("Saturno", 135.36 * escala, 151.3 * escala, 29.5, 0.445, "../imagenes/Saturno.jpg",
                                   9.13, 23.0));
    planetas.push_back(
        new Planeta("Urano", 300.6 * escala, 273.5 * escala, 84, -0.720, "../imagenes/Uranus.jpg", 4, 98));
    planetas.push_back(new Planeta("Neptuno", 453.7 * escala, 445.9 * escala, 164.7, 1, "../imagenes/Neptuno.jpg", 3.88,
                                   1));
    planetas.push_back(new Planeta("Plutón", 730 * escala, 440 * escala, 247.68, 6.41, "../imagenes/Pluton.jpg", 0.186,
                                   120));
    planetas.push_back(new Planeta("Luna", 8, 8, 0.07, 2.5, "../imagenes/Luna.jpg", 0.18, 15.0, planetas[3]));

    planetaSeleccionado = planetas[3];
}

/**
 * @brief Ajusta la vista al redimensionar la ventana.
 * @param w Ancho de la ventana
 * @param h Alto de la ventana
 */
void reescalarVentana(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 1500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * @brief Actualiza la posición orbital de los planetas en el sistema solar.
 */
void orbita() {
    long nuevoContadorReloj = clock();

    for (int i = 0; i < planetas.size(); i++)
        planetas[i]->Orbita(multiplicarTiempo * ((nuevoContadorReloj - contadorReloj) / 20), 30);

    contadorReloj = nuevoContadorReloj;
    glutPostRedisplay();
}

/**
 * @brief Maneja la selección de planetas desde el menú.
 * @param opcion Índice del planeta seleccionado
 */
void menuSeleccion(int opcion) {
    if (opcion >= 1 && opcion <= planetas.size()) {
        planetaSeleccionado = planetas[opcion - 1];
    }
    glutPostRedisplay();
}

/**
 * @brief Configura la representación gráfica del sistema solar.
 * Inicia la ventana, crea los planetas, y define las funciones de manejo de eventos.
 */
void representarSistemaSolar() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Proyecto Sistema Solar");

    crearPlanetas();
    fondo = new igvTextura("../imagenes/fondoUniverso.jpg", 1200);

    glutReshapeFunc(reescalarVentana);
    glutDisplayFunc(dibujarMovimiento);
    glutKeyboardFunc(keyboardFunc);
    glutMotionFunc(movimientoCamara);
    glutMouseFunc(moviminetoRaton);

    int menuPlanetas = glutCreateMenu(menuSeleccion);
    for (size_t i = 0; i < planetas.size(); i++) {
        glutAddMenuEntry(planetas[i]->nombre.c_str(), i + 1);
    }
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GLUT_MULTISAMPLE);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutIdleFunc(orbita);
    glutMainLoop();
}
