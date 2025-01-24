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

#include "Camara.h"
#include "Planeta.h"
#include "igvTextura.h"

// Declaración de variables globales
extern float intensidadLuz; ///< Intensidad de la luz en la escena.
extern Planeta *planetaSeleccionado; ///< Puntero al planeta actualmente seleccionado.
extern std::vector<Planeta *> planetas; ///< Lista de planetas en el sistema solar.
extern igvTextura *fondo; ///< Fondo del sistema solar, usualmente una textura esférica.

extern double multiplicarTiempo; ///< Factor de multiplicación para simular el paso del tiempo.
extern double contadorReloj; ///< Contador del reloj para simular el tiempo en la escena.
extern bool vistaCuadrante; ///< Bandera para determinar si se está mostrando la vista del cuadrante.

/// @brief Muestra los controles disponibles para el usuario.
void mostrarControles();

/// @brief Mueve la vista entre los planetas en el sistema solar.
void movermeEntrePlanetas(int indice);

/// @brief Muestra información detallada sobre el planeta seleccionado.
void mostrarInfoPlaneta();

/// @brief Maneja el movimiento de la cámara basado en el desplazamiento del mouse.
void movimientoCamara(int x, int y);

/// @brief Dibuja el movimiento de los planetas y su órbita en la escena.
void dibujarMovimiento();

/// @brief Función para manejar las pulsaciones de teclas.
void keyboardFunc(unsigned char key, int x, int y);

/// @brief Crea los planetas e inicializa sus parámetros.
void crearPlanetas();

/// @brief Reescala la ventana de visualización cuando el tamaño de la ventana cambia.
void reescalarVentana(int w, int h);

/// @brief Calcula y simula la órbita de los planetas en el sistema solar.
void orbita();

/// @brief Maneja las opciones del menú de selección del sistema solar.
void menuSeleccion(int opcion);

/// @brief Representa visualmente el sistema solar en la escena.
void representarSistemaSolar();

/// @brief Renderiza la escena actual con todos los objetos y luces.
void renderizarEscena();

/// @brief Muestra información del planeta seleccionado en la ventana de visualización.
void mostrarInfoPlanetaEnVentana();

/// @brief Dibuja un rectángulo en la pantalla con las especificaciones dadas.
void dibujarRectangulo(float x, float y, float ancho, float alto, float r, float g, float b, float alpha);

/// @brief Dibuja el texto en las coordenadas especificadas en la ventana.
void drawText(const char *text, float x, float y);

#endif // SISTEMA_SOLAR_H
