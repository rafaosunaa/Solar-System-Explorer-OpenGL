#ifndef SISTEMA_SOLAR_H
#define SISTEMA_SOLAR_H

#if defined(__APPLE__) && defined(__MACH__)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <vector>
#include "Planeta.h"
#include "igvTextura.h"

// Enum para diferentes vistas
enum Vista {
    VISTA_NORMAL,
    VISTA_PLANTA,    // Vista desde arriba (plano)
    VISTA_PERFIL,    // Vista lateral (perfil)
    VISTA_ABAJO,     // Vista desde abajo
    VISTA_TRASERA    // Vista desde atrás
};

// Variables globales
extern Vista vistaActual;
extern Planeta *planetaSeleccionado;
extern std::vector<Planeta *> planetas;
extern igvTextura *fondo;

extern double multiplicarTiempo;
extern double contadorReloj;
extern double zoom;
extern double arrastrarX;
extern double arrastrarY;
extern double mouseX;
extern double mouseY;
extern bool vistaCuadrante;

// Declaración de funciones
void movermeEntrePlanetas(int indice);
void mostrarInfoPlaneta();
void cambiarVista();
void movimientoCamara(int x, int y);
void dibujarMovimiento();
void keyboardFunc(unsigned char key, int x, int y);
void crearPlanetas();
void reescalarVentana(int w, int h);
void orbita();
void menuSeleccion(int opcion);
void representarSistemaSolar();

#endif // SISTEMA_SOLAR_H
