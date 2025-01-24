// SistemaSolar.cpp

#include "SistemaSolar.h"
#include "Camara.h"
#include "NodoGrafoEscena.h"


#if defined(__APPLE__) && defined(__MACH__)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

// ===========================================================================
// Variables globales
// ===========================================================================

/**
 * @brief Cámara utilizada para la visualización.
 */
Camara camara;

/**
 * @brief Puntero al planeta actualmente seleccionado.
 */
Planeta *planetaSeleccionado = nullptr;

/**
 * @brief Vector que contiene los planetas del sistema solar.
 */
vector<Planeta *> planetas;

/**
 * @brief Textura utilizada para el fondo del sistema solar.
 */
igvTextura *fondo = nullptr;

/**
 * @brief Bandera para alternar entre vista única y dividida.
 */
bool vistaDividida = false;

/**
 * @brief Bandera para mostrar u ocultar controles en pantalla.
 */
bool mostrarControlesFlag = true;

/**
 * @brief Factor para ajustar la velocidad de las órbitas.
 */
double multiplicarTiempo = 0.03;

/**
 * @brief Contador de tiempo para las actualizaciones de órbita.
 */
double contadorReloj = 0;

/**
 * @brief Grafo que representa el satélite en órbita.
 */
GrafoSatelite *satelite;

/**
 * @brief Velocidad de rotación del satélite.
 */
double velocidadRotacionSatelite = 0.01;

/**
 * @brief Ángulo actual de rotación del satélite.
 */
double anguloRotacionSatelite = 0.0;

/**
 * @brief Bandera para controlar la animación del satélite.
 */
bool animarSatelite = false;



// ===========================================================================
// Inicialización
// ===========================================================================

/**
 * @brief Inicializa el satélite en el sistema solar.
 */
void inicializarSatelite() {
    satelite = new GrafoSatelite();
}

/**
 * @brief Crea los planetas del sistema solar y los agrega al vector planetas.
 */
void crearPlanetas() {
    int escala = 20;

    // Crear el Sol (raíz del grafo)
    Planeta *sol = new Planeta("Sol", 0, 0, 0, 20, "../imagenes/Sol.png", 10.9);
    planetas.push_back(sol);

    // Crear planetas orbitando alrededor del Sol
    Planeta *mercurio = new Planeta("Mercurio", 7.0 * escala, 4.6 * escala, 0.24, 58.82, "../imagenes/Mercurio.png",
                                    0.38, sol);
    planetas.push_back(mercurio);

    Planeta *venus = new Planeta("Venus", 10.893 * escala, 10.747 * escala, 0.61, 243, "../imagenes/Venus.png", 0.815,
                                 sol);
    planetas.push_back(venus);

    Planeta *tierra = new Planeta("Tierra", 15.19 * escala, 14.95 * escala, 1.0, 1.0, "../imagenes/Tierra.png", 1.0,
                                  sol);
    planetas.push_back(tierra);

    // Crear la Luna orbitando la Tierra
    //Planeta *luna = new Planeta("Luna", 0.384 * escala, 0, 0.07, 27.3, "../imagenes/Luna.png", 0.27, tierra);
    //planetas.push_back(luna);

    Planeta *marte = new Planeta("Marte", 20.67 * escala, 24.92 * escala, 1.8821, 1.03, "../imagenes/Marte.png", 0.53,
                                 sol);
    planetas.push_back(marte);

    Planeta *jupiter = new Planeta("Júpiter", 81.6 * escala, 74.05 * escala, 11.86, 0.41, "../imagenes/Jupiter.png",
                                   11.0, sol);
    planetas.push_back(jupiter);

    Planeta *saturno = new Planeta("Saturno", 135.36 * escala, 151.3 * escala, 29.5, 0.445, "../imagenes/Saturno.png",
                                   9.13, sol);
    planetas.push_back(saturno);

    Planeta *urano = new Planeta("Urano", 300.6 * escala, 273.5 * escala, 84, -0.720, "../imagenes/Uranus.png", 4.0,
                                 sol);
    planetas.push_back(urano);

    Planeta *neptuno = new Planeta("Neptuno", 453.7 * escala, 445.9 * escala, 164.7, 0.67, "../imagenes/Neptuno.png",
                                   3.88, sol);
    planetas.push_back(neptuno);

    Planeta *pluton = new Planeta("Plutón", 730 * escala, 440 * escala, 247.68, 6.41, "../imagenes/Pluton.png", 0.186,
                                  sol);
    planetas.push_back(pluton);

    // Seleccionar la Tierra como planeta inicial
    planetaSeleccionado = tierra;
}


// ===========================================================================
// Dibujado de elementos
// ===========================================================================


/**
 * @brief Dibuja el satélite en la órbita de la Tierra
 */
void dibujarSatelite() {
    Planeta *tierra = planetas[3]; // Índice de la Tierra
    glPushMatrix();

    // Trasladamos al centro de la Tierra
    glTranslatef(tierra->pX, tierra->pY, tierra->pZ);

    // Aplicamos la rotación acumulada
    glRotatef(anguloRotacionSatelite, 0.0, 1.0, 0.0);

    // Desplazamiento a la órbita
    glTranslatef(2.0, 0.0, 0.0);

    // Escalado general del satélite
    glScalef(0.1, 0.1, 0.1);

    // Dibujar el satélite
    satelite->dibujar();

    glPopMatrix();
}


void drawText(const char *text, float x, float y) {
    glLoadIdentity(); // Asegúrate de que no hay transformaciones activas
    glRasterPos2f(x, y); // Posiciona el texto
    for (const char *c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

/**
 * @brief Muestra información detallada del planeta seleccionado en una ventana.
 */
void mostrarInfoPlanetaEnVentana() {
    if (planetaSeleccionado != nullptr) {
        // Dimensiones y posición del rectángulo de fondo
        float margenIzq = 20.0f;
        float margenSup = 50.0f;
        float anchoRect = 300.0f;
        float altoRect = 100.0f;
        float espaciadoLinea = 20.0f;

        // Configurar el modo ortogonal
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();


        // Dibujar el texto
        float xTexto = margenIzq + 10.0f; // Margen interno
        float yTexto = glutGet(GLUT_WINDOW_HEIGHT) - margenSup - 20.0f;

        // Texto destacado para el nombre del planeta
        glColor3f(1.0f, 0.8f, 0.2f); // Amarillo claro
        drawText(("Planeta: " + planetaSeleccionado->nombre).c_str(), xTexto, yTexto);
        yTexto -= espaciadoLinea;

        // Texto normal para la información adicional
        glColor3f(1.0f, 1.0f, 1.0f); // Blanco
        char info[256];
        snprintf(info, sizeof(info), "Aphelion: %.2f", planetaSeleccionado->aphelion);
        drawText(info, xTexto, yTexto);
        yTexto -= espaciadoLinea;

        snprintf(info, sizeof(info), "Perihelion: %.2f", planetaSeleccionado->perihelion);
        drawText(info, xTexto, yTexto);
        yTexto -= espaciadoLinea;

        snprintf(info, sizeof(info), "Periodo ROtacion: %.2f anios", planetaSeleccionado->periodoOrbital);
        drawText(info, xTexto, yTexto);

        // Restaurar las matrices
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
}


/**
 * @brief Dibuja el movimiento de la cámara y representa el fondo y los planetas.
 */
const char *nombresVistas[] = {"Vista Normal", "Vista Planta", "Vista Perfil"};

void dibujarMovimiento() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Mostrar información del planeta seleccionado
    mostrarInfoPlanetaEnVentana();

    if (mostrarControlesFlag) {
        mostrarControles(); // Mostrar los controles
    }

    if (vistaDividida) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        // Vista Normal
        glViewport(0, height / 2, width / 2, height / 2);
        camara.setVista(VISTA_NORMAL);
        camara.cambiarVista();
        renderizarEscena();

        // Vista Planta
        glViewport(width / 2, height / 2, width / 2, height / 2);
        camara.setVista(VISTA_PLANTA);
        camara.cambiarVista();
        renderizarEscena();

        // Vista Perfil
        glViewport(0, 0, width / 2, height / 2);
        camara.setVista(VISTA_PERFIL);
        camara.cambiarVista();
        renderizarEscena();

        glViewport(0, 0, width, height);
    } else {
        // Vista única
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        camara.cambiarVista();
        renderizarEscena();
    }

    // Mostrar el texto de la vista actual
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);

    glColor3f(1.0, 1.0, 1.0);
    drawText(vistaDividida ? "Vista Dividida" : nombresVistas[camara.getVistaActual()], 20,
             glutGet(GLUT_WINDOW_HEIGHT) - 30);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();


    glutSwapBuffers();
}


/**
 * @brief Renderiza los elementos de la escena, incluyendo el fondo, planetas y satélites.
 */
void renderizarEscena() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Obtener las coordenadas de la cámara desde la instancia de Camara
    double x, y, z;
    const double mitadPI = 3.1416 / 180;

    // Usar el zoom dinámico calculado en el cambio de planeta
    double distanciaCamara = camara.getZoom();

    x = sin((-camara.getMouseX() + camara.getArrastrarX()) * mitadPI) *
        cos((camara.getMouseY() - camara.getArrastrarY()) * mitadPI) * camara.getZoom();
    y = sin((camara.getMouseY() - camara.getArrastrarY()) * mitadPI) * camara.getZoom();
    z = cos((-camara.getMouseX() + camara.getArrastrarX()) * mitadPI) *
        cos((camara.getMouseY() - camara.getArrastrarY()) * mitadPI) * camara.getZoom();

    // Configurar la vista con gluLookAt
    gluLookAt(planetaSeleccionado->pX + x, planetaSeleccionado->pY + y, planetaSeleccionado->pZ + z,
              planetaSeleccionado->pX, planetaSeleccionado->pY, planetaSeleccionado->pZ,
              0.0, 1.0, 0.0);

    // Dibujar el fondo y los planetas
    glPushMatrix();
    fondo->fondo();

    for (size_t i = 0; i < planetas.size(); i++) {
        planetas[i]->dibujarPlaneta();
    }

    // Dibujar el satélite
    dibujarSatelite();

    glPopMatrix();
}


/**
 * @brief Muestra los controles de usuario en pantalla.
 */
void mostrarControles() {
    // Dimensiones y posición
    float margenIzq = 20.0f; // Margen izquierdo para los controles generales
    float margenInferior = 20.0f; // Margen inferior desde donde comienzan los textos
    float margenDer = glutGet(GLUT_WINDOW_WIDTH) - 300.0f; // Ajuste para el margen derecho
    float espaciadoLinea = 20.0f;

    // Configurar el modo ortogonal
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Dibujar el texto de los controles
    glColor3f(1.0f, 1.0f, 1.0f); // Blanco para el texto

    // Controles generales a la izquierda, comenzando desde el margen inferior
    float yTextoIzq = margenInferior; // Posición inicial del texto en la izquierda
    drawText("Controles Generales:", margenIzq, yTextoIzq);
    yTextoIzq += espaciadoLinea;

    drawText("Esc: Salir", margenIzq, yTextoIzq);
    yTextoIzq += espaciadoLinea;

    drawText("c: Activar/Desactivar info controles", margenIzq, yTextoIzq);
    yTextoIzq += espaciadoLinea;

    drawText("v: Cambiar vista", margenIzq, yTextoIzq);
    yTextoIzq += espaciadoLinea;

    drawText("f: Alternar vista dividida", margenIzq, yTextoIzq);
    yTextoIzq += espaciadoLinea;

    drawText("-: Alejar cámara (Zoom out)", margenIzq, yTextoIzq);
    yTextoIzq += espaciadoLinea;

    drawText("+: Acercar cámara (Zoom in)", margenIzq, yTextoIzq);
    yTextoIzq += espaciadoLinea;

    drawText("a: Aumentar velocidad de órbita", margenIzq, yTextoIzq);
    yTextoIzq += espaciadoLinea;

    drawText("d: Disminuir velocidad de órbita", margenIzq, yTextoIzq);

    // Controles del satélite a la derecha, comenzando desde el margen inferior
    float yTextoDer = margenInferior; // Posición inicial del texto en la derecha
    drawText("Controles del Satelite:", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;
	
	drawText("t: Activar/Desactivar animacion orbita", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;

    drawText("i: Rotar panel izquierdo hacia arriba", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;

    drawText("I: Rotar panel izquierdo hacia abajo", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;

    drawText("d: Rotar panel derecho hacia arriba", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;

    drawText("D: Rotar panel derecho hacia abajo", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;

    drawText("u: Rotar cuerpo1 ", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;

    drawText("j: Rotar cuerpo2", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;

    drawText("r: Aumentar velocidad de rotación ", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;

    drawText("R: Disminuir velocidad de rotación ", margenDer, yTextoDer);
    yTextoDer += espaciadoLinea;

    drawText("z: Resetear todas las posiciones", margenDer, yTextoDer);

    // Restaurar las matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
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


// ===========================================================================
// Eventos y lógica
// ===========================================================================
/**
 * @brief Ajusta la vista al redimensionar la ventana.
 * @param w Ancho de la ventana
 * @param h Alto de la ventana
 */
void reescalarVentana(int w, int h) {
    if (h == 0) {
        h = 1; // Prevenir divisiones por cero
    }

    // Relación de aspecto
    float aspecto = static_cast<float>(w) / static_cast<float>(h);

    // Ajustar el viewport a las nuevas dimensiones de la ventana
    glViewport(0, 0, w, h);

    // Configurar la proyección
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Ajustar el campo de visión con la relación de aspecto actualizada
    gluPerspective(60.0, aspecto, 1.0, 1500.0);

    // Volver al modo de modelado
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * @brief Actualiza la posición orbital de los planetas en el sistema solar.
 */
void orbita() {
    long nuevoContadorReloj = clock();
    double tiempoDelta = (nuevoContadorReloj - contadorReloj) / CLOCKS_PER_SEC;

    for (Planeta *planeta : planetas) {
        planeta->Orbita(multiplicarTiempo * tiempoDelta, 30.0);
    }

    if (animarSatelite) { // Solo actualizar si la animación está activa
        anguloRotacionSatelite += velocidadRotacionSatelite * tiempoDelta * 360.0;
        if (anguloRotacionSatelite >= 360.0) {
            anguloRotacionSatelite -= 360.0;
        }
    }

    contadorReloj = nuevoContadorReloj;
    glutPostRedisplay();
}



void actualizarAnimacion() {
    if (animarSatelite) { // Solo actualiza si la animación está activa
        anguloRotacionSatelite += velocidadRotacionSatelite; // Incrementar el ángulo
        if (anguloRotacionSatelite >= 360.0) {
            anguloRotacionSatelite -= 360.0; // Mantener el ángulo entre 0 y 360 grados
        }
    }
    glutPostRedisplay(); // Solicitar redibujado
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
        case '-': //zoom out
            camara.incrementarZoom();
            break;
        case '+': //zoom in
            camara.decrementarZoom();
            break;

        //aumentar velocidad giro orbita
        case 'a':
            multiplicarTiempo /= multiplicarTiempo < 0.001 ? 1 : 2;
            break;

        //disminuir giro orbita
        case 'A':
            multiplicarTiempo *= multiplicarTiempo > 10 ? 1 : 2;
            break;

        case 'v':
            // Cambiar la vista
            camara.setVista(static_cast<Vista>((camara.getVistaActual() + 1) % 3)); // Solo 3 vistas disponibles
            camara.cambiarVista();
            break;


        case 'f': // Alternar entre vista única y vista dividida
            if (vistaDividida) {
                vistaDividida = false; // Regresar a vista única
                camara.setVista(VISTA_NORMAL); // Asegurar que vuelve a la vista normal
            } else {
                vistaDividida = true; // Cambiar a vista dividida
            }
            camara.cambiarVista(); // Actualizar la vista según el estado
            break;

        case 'c': // Alternar la visibilidad de los controles
            mostrarControlesFlag = !mostrarControlesFlag;
            break;

        case 'i': // Rotar panel izquierdo hacia arriba
            satelite->panelIzquierdo->rotacionX += 5.0f;
            break;
        case 'I': // Rotar panel izquierdo hacia abajo
            satelite->panelIzquierdo->rotacionX -= 5.0f;
            break;
        case 'd': // Rotar panel derecho hacia arriba
            satelite->panelDerecho->rotacionX += 5.0f;
            break;
        case 'D': // Rotar panel derecho hacia abajo
            satelite->panelDerecho->rotacionX -= 5.0f;
            break;

        case 'u': // Rotar primer segmento del cuerpo hacia adelante/atrás
            satelite->cuerpo1->rotacionX += 5.0f;
            break;
        case 'j': // Rotar segundo segmento del cuerpo hacia adelante/atrás
            satelite->cuerpo2->rotacionX += 5.0f;
            break;

        case 'r': // Aumentar velocidad de rotación
            velocidadRotacionSatelite += 0.01; // Incrementar
            break;
        case 'R': // Disminuir velocidad de rotación
            velocidadRotacionSatelite = max(0.001, velocidadRotacionSatelite - 0.01); // Prevenir valores negativos
            break;


        case 'z': // Resetear todas las posiciones
            satelite->panelIzquierdo->rotacionX = 0.0f;
            satelite->panelDerecho->rotacionX = 0.0f;
            satelite->cuerpo1->rotacionZ = 0.0f;
            satelite->cuerpo2->rotacionX = 0.0f;
            break;

        // Activar/Desactivar animación del satélite
        case 't': // Tecla para alternar
            animarSatelite = !animarSatelite;
        break;


        case 27: // Tecla ESC para salir
            exit(1);
            break;
    }

    //Moverme entre planetas
    if (indice >= 0 && indice < planetas.size()) {
        planetaSeleccionado = planetas[indice];


        if (planetas[indice]->get_nombre() == "Luna") {
            return; // No hacer nada si es la Luna
        }
        // Calcular distancia segura basada en el tamaño del planeta
        double distanciaSegura = planetaSeleccionado->get_tamano() * 3.0; // Factor de escala ajustable

        // Ajuste para planetas especifico
        if (planetaSeleccionado->get_nombre() == "Pluton") {
            distanciaSegura *= 4.0; // Aumentar el zoom para Saturno
        }


        // Aplicar el zoom calculado
        camara.setZoom(distanciaSegura);

        // Mostrar la información del planeta
        mostrarInfoPlaneta();
    }

    glutPostRedisplay();
}


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
 * @brief Maneja la selección de planetas desde el menú.
 * @param opcion Índice del planeta seleccionado
 */
void menuSeleccion(int opcion) {
    if (opcion >= 1 && opcion <= planetas.size()) {
        planetaSeleccionado = planetas[opcion - 1];

        // Calcular distancia segura basada en el tamaño del planeta
        double distanciaSegura = planetaSeleccionado->get_tamano() * 3.0; // Factor de escala ajustable

        // Ajuste para planetas especifico
        if (planetaSeleccionado->get_nombre() == "Pluton") {
            distanciaSegura *= 4.0; // Aumentar el zoom para Saturno
        }

        // Aplicar el zoom calculado
        camara.setZoom(distanciaSegura);
    }
    glutPostRedisplay(); // Forzar redibujado
}

/**
 * @brief Crea un menú para seleccionar planetas con el botón derecho del ratón.
 */
void crearMenuPlanetas() {
    int menuPlanetas = glutCreateMenu(menuSeleccion); // Crear menú con función callback
    for (size_t i = 0; i < planetas.size(); i++) {
        if (planetas[i]->get_nombre() == "Luna") {
            continue; // Saltar la Luna
        }

        glutAddMenuEntry(planetas[i]->get_nombre().c_str(), i + 1); // Agregar cada planeta
    }
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Asociar al clic derecho
}


// ===========================================================================
// Configuración y entrada principal
// ===========================================================================

/**
 * @brief Configura la representación gráfica del sistema solar.
 * Inicia la ventana, crea los planetas, y define las funciones de manejo de eventos.
 */
void representarSistemaSolar() {
    crearPlanetas();
    inicializarSatelite();
    fondo = new igvTextura("../imagenes/fondoUniverso.png", 1200);

    // Configurar eventos de ventana y entrada utilizando la clase Camara
    glutReshapeFunc(reescalarVentana); // Usar la función reescalarVentana para ajustar la vista
    glutDisplayFunc(dibujarMovimiento);
    glutKeyboardFunc(keyboardFunc);
    glutMotionFunc([](int x, int y) { camara.actualizarMovimiento(x, y); });
    glutMouseFunc([](int key, int estado, int x, int y) { camara.moverRaton(key, estado, x, y); });

    // Crear el menú para seleccionar planetas
    crearMenuPlanetas();

    glutIdleFunc(actualizarAnimacion);

    // Configuraciones de OpenGL
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
