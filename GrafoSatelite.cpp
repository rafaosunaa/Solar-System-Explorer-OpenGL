//
// Created by rafao on 13/12/2024.
//


#include "NodoGrafoEscena.h"

/**
 * @brief Constructor de la clase GrafoSatelite.
 * Llama a la función inicializar para configurar los nodos del satélite.
 */
GrafoSatelite::GrafoSatelite() {
    inicializar();
}


/**
 * @brief Inicializa los nodos del grafo del satélite.
 * Crea los nodos que componen el satélite (panel izquierdo, panel derecho y cuerpos).
 * Establece la traslación, escala y color para cada nodo.
 * Luego, agrega los nodos al grafo.
 */
void GrafoSatelite::inicializar() {
    // Crear nodos para los componentes del satélite
    panelIzquierdo = new NodoGrafoEscena();
    panelDerecho = new NodoGrafoEscena();
    cuerpo1 = new NodoGrafoEscena();
    cuerpo2 = new NodoGrafoEscena();

    // Configuración de los paneles solares
    panelIzquierdo->traslacionX = -1.5f;
    panelIzquierdo->escalaX = 5.0f;
    panelIzquierdo->escalaY = 0.2f;
    panelIzquierdo->setColor(0.3f, 0.3f, 0.8f);

    panelDerecho->traslacionX = 1.5f;
    panelDerecho->escalaX = 3.0f;
    panelDerecho->escalaY = 0.2f;
    panelDerecho->setColor(0.3f, 0.3f, 0.8f);

    // Configuración del cuerpo
    cuerpo1->traslacionY = -0.5f;
    cuerpo1->escalaY = 1.5f;
    cuerpo1->setColor(0.6f, 0.6f, 0.6f); // Gris metálico

    cuerpo2->traslacionY = 1.5f;
    cuerpo2->escalaY = 1.0f;
    cuerpo2->setColor(0.6f, 0.6f, 0.6f); // Gris metálico

    // Construcción del grafo
    agregarHijo(panelIzquierdo);
    agregarHijo(panelDerecho);
    cuerpo1->agregarHijo(cuerpo2);
    agregarHijo(cuerpo1);
}
