#ifndef GRAFO_SATELITE_H
#define GRAFO_SATELITE_H

#include <vector>
#include <GL/glut.h>

/**
 * @class NodoGrafoEscena
 * @brief Representa un nodo en un grafo de escena 3D.
 *
 * Esta clase es utilizada para modelar un nodo dentro de un grafo de escena.
 * Cada nodo puede tener transformaciones (traslación, rotación, escala) y color.
 * También puede tener hijos, que son otros nodos que se dibujan en relación a él.
 */
class NodoGrafoEscena {
public:
    float traslacionX, traslacionY, traslacionZ; ///< Traslación del nodo en el espacio 3D.
    float rotacionX, rotacionY, rotacionZ; ///< Rotación del nodo en el espacio 3D.
    float escalaX, escalaY, escalaZ; ///< Escala del nodo en el espacio 3D.
    float colorR, colorG, colorB; ///< Componentes de color RGB del nodo.

    std::vector<NodoGrafoEscena*> hijos; ///< Hijos del nodo en el grafo de escena.

    /**
     * @brief Constructor por defecto que inicializa las transformaciones y el color del nodo.
     *
     * Establece las transformaciones a valores predeterminados (0 para traslación y rotación, 1 para escala)
     * y el color a un gris predeterminado (0.5f, 0.5f, 0.5f).
     */
    NodoGrafoEscena()
        : traslacionX(0), traslacionY(0), traslacionZ(0),
          rotacionX(0), rotacionY(0), rotacionZ(0),
          escalaX(1), escalaY(1), escalaZ(1),
          colorR(0.5f), colorG(0.5f), colorB(0.5f) {} // Color gris predeterminado

    /**
     * @brief Agrega un nodo hijo al nodo actual.
     * @param nodo Puntero al nodo hijo que será agregado al nodo actual.
     */
    void agregarHijo(NodoGrafoEscena* nodo) {
        hijos.push_back(nodo);
    }

    /**
     * @brief Establece el color del nodo.
     * @param r Componente roja del color.
     * @param g Componente verde del color.
     * @param b Componente azul del color.
     */
    void setColor(float r, float g, float b) {
        colorR = r;
        colorG = g;
        colorB = b;
    }

    /**
     * @brief Dibuja el nodo y sus hijos aplicando transformaciones y colores.
     *
     * Este método realiza la traducción, rotación, y escala del nodo actual
     * y luego dibuja la forma del nodo. Después, recursivamente dibuja todos los nodos hijos.
     */
    virtual void dibujar() {
        glPushMatrix();

        // Aplicar transformaciones locales
        glTranslatef(traslacionX, traslacionY, traslacionZ);
        glRotatef(rotacionX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotacionY, 0.0f, 1.0f, 0.0f);
        glRotatef(rotacionZ, 0.0f, 0.0f, 1.0f);
        glScalef(escalaX, escalaY, escalaZ);

        // Establecer el color
        glColor3f(colorR, colorG, colorB);

        // Dibujar la forma del nodo
        dibujarForma();

        // Dibujar los hijos
        for (auto hijo : hijos) {
            hijo->dibujar();
        }

        glPopMatrix();
    }

    /**
     * @brief Dibuja la forma del nodo.
     *
     * Este método es virtual y puede ser sobrescrito en clases derivadas para dibujar diferentes tipos de formas.
     */
    virtual void dibujarForma() {
        glutSolidCube(1.0); ///< Dibuja un cubo sólido por defecto.
    }
};

/**
 * @class GrafoSatelite
 * @brief Representa un grafo específico para un satélite, extendiendo NodoGrafoEscena.
 *
 * Esta clase hereda de `NodoGrafoEscena` y representa un satélite compuesto por nodos para
 * los paneles solares y los cuerpos del satélite. Los nodos hijos se agregan y configuran
 * para representar el satélite de manera visual.
 */
class GrafoSatelite : public NodoGrafoEscena {
public:
    NodoGrafoEscena* panelIzquierdo; ///< Nodo para el panel izquierdo del satélite.
    NodoGrafoEscena* panelDerecho; ///< Nodo para el panel derecho del satélite.
    NodoGrafoEscena* cuerpo1; ///< Nodo para el primer cuerpo del satélite.
    NodoGrafoEscena* cuerpo2; ///< Nodo para el segundo cuerpo del satélite.

    /**
     * @brief Constructor que inicializa los nodos y las transformaciones del satélite.
     *
     * Este constructor llama al método `inicializar` para configurar los nodos del satélite
     * (paneles solares y cuerpos), estableciendo sus transformaciones y colores.
     */
    GrafoSatelite();

    /**
     * @brief Inicializa los nodos del satélite.
     *
     * Este método crea los nodos del satélite, asigna las transformaciones (traslación, escala, rotación),
     * configura el color de los nodos y agrega los nodos al grafo.
     */
    void inicializar();
};

#endif
