//
// Created by rafao on 13/12/2024.
//


#include "NodoGrafoEscena.h"

/**
 * @brief Constructor de la clase GrafoSatelite.
 * Llama a la funci�n inicializar para configurar los nodos del sat�lite.
 */
GrafoSatelite::GrafoSatelite() {
    inicializar();
}


/**
 * @brief Inicializa los nodos del grafo del sat�lite.
 * Crea los nodos que componen el sat�lite (panel izquierdo, panel derecho y cuerpos).
 * Establece la traslaci�n, escala y color para cada nodo.
 * Luego, agrega los nodos al grafo.
 */
void GrafoSatelite::inicializar() {
    // Crear nodos para los componentes del sat�lite
    panelIzquierdo = new NodoGrafoEscena();
    panelDerecho = new NodoGrafoEscena();
    cuerpo1 = new NodoGrafoEscena();
    cuerpo2 = new NodoGrafoEscena();

    // Configuraci�n de los paneles solares
    panelIzquierdo->traslacionX = -1.5f;
    panelIzquierdo->escalaX = 5.0f;
    panelIzquierdo->escalaY = 0.2f;
    panelIzquierdo->setColor(0.3f, 0.3f, 0.8f);

    panelDerecho->traslacionX = 1.5f;
    panelDerecho->escalaX = 3.0f;
    panelDerecho->escalaY = 0.2f;
    panelDerecho->setColor(0.3f, 0.3f, 0.8f);

    // Configuraci�n del cuerpo
    cuerpo1->traslacionY = -0.5f;
    cuerpo1->escalaY = 1.5f;
    cuerpo1->setColor(0.6f, 0.6f, 0.6f); // Gris met�lico

    cuerpo2->traslacionY = 1.5f;
    cuerpo2->escalaY = 1.0f;
    cuerpo2->setColor(0.6f, 0.6f, 0.6f); // Gris met�lico

    // Construcci�n del grafo
    agregarHijo(panelIzquierdo);
    agregarHijo(panelDerecho);
    cuerpo1->agregarHijo(cuerpo2);
    agregarHijo(cuerpo1);
}
