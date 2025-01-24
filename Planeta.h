#ifndef Planeta_h
#define Planeta_h

#if defined(__APPLE__) && defined(__MACH__)
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)
#include <stdio.h>
#include <string>
#include <vector>

#include "igvTextura.h"


using namespace std;

/**
 * @class Planeta
 * @brief Representa un planeta en un sistema solar 3D.
 *
 * Esta clase simula un planeta con caracter�sticas f�sicas como el tama�o, la �rbita, la rotaci�n,
 * la inclinaci�n y la textura. Los planetas tambi�n pueden tener sat�lites y estar organizados en una jerarqu�a.
 */
class Planeta {
public:
    std::string nombre; ///< Nombre del planeta.
    float aphelion, perihelion, periodoOrbital, rotacion, inclinacionY, inclinacionZ, tamano, radio; ///< Atributos f�sicos del planeta.
    double velocidadOrbital, tiempoDelta, ubicacionActualEje, ubicacionActualSistema; ///< Velocidad orbital, tiempo y ubicaciones del planeta.
    float pX, pY, pZ; ///< Posici�n del planeta en el espacio 3D.
    std::string rutaImagen; ///< Ruta de la imagen para la textura del planeta.
    igvTextura *textura; ///< Textura del planeta.
    Planeta *satelite;   ///< Puntero al sat�lite del planeta.
    Planeta *padre;      ///< Puntero al planeta padre (si existe).
    std::vector<Planeta *> hijos; ///< Lista de los planetas hijos.

    /**
     * @brief Constructor de la clase Planeta.
     * @param nombre Nombre del planeta.
     * @param aphelion Distancia m�xima del planeta al Sol.
     * @param perihelion Distancia m�nima del planeta al Sol.
     * @param periodoOrbital Tiempo en a�os que tarda el planeta en completar una �rbita alrededor del Sol.
     * @param periodoRotacion Tiempo que tarda el planeta en completar una rotaci�n sobre su eje.
     * @param rutaImagen Ruta de la imagen que representa el planeta.
     * @param tamano Tama�o del planeta.
     * @param padre Puntero al planeta padre (si tiene).
     */
    Planeta(const std::string &nombre, float aphelion, float perihelion, float periodoOrbital,
        float periodoRotacion, const std::string &rutaImagen, float tamano, Planeta *padre = nullptr);

    /**
     * @brief Destructor de la clase Planeta.
     * Libera la memoria ocupada por la textura y el sat�lite.
     */
    ~Planeta();

    /**
     * @brief Calcula la �rbita del planeta.
     * @param grado Grado de rotaci�n utilizado para simular el movimiento del planeta.
     * @param escalaRotacionEje Escala de la rotaci�n del eje del planeta.
     */
    void Orbita(double grado, double escalaRotacionEje);

    /**
     * @brief Dibuja el planeta en la escena 3D.
     */
    void dibujarPlaneta();

    /**
     * @brief Dibuja una esfera representando la �rbita del planeta.
     * @param escala Escala de la esfera para ajustar el tama�o de la �rbita.
     */
    void dibujarEsfera(float escala);

    // M�todos de acceso (getters)

    /**
     * @brief Obtiene el radio del planeta.
     * @return El radio del planeta.
     */
    float get_radio() const;

    /**
     * @brief Obtiene el nombre del planeta.
     * @return El nombre del planeta.
     */
    std::string get_nombre() const;

    /**
     * @brief Obtiene la velocidad orbital del planeta.
     * @return La velocidad orbital del planeta.
     */
    double get_velocidad_orbital() const;

    /**
     * @brief Obtiene la distancia m�xima del planeta al Sol (Aphelion).
     * @return La distancia m�xima (Aphelion).
     */
    double get_aphelion() const;

    /**
     * @brief Obtiene la distancia m�nima del planeta al Sol (Perihelion).
     * @return La distancia m�nima (Perihelion).
     */
    double get_perihelion() const;

    /**
     * @brief Obtiene el per�odo orbital del planeta.
     * @return El per�odo orbital del planeta en a�os.
     */
    double get_periodo_orbital() const;

    /**
     * @brief Obtiene el per�odo de rotaci�n del planeta.
     * @return El per�odo de rotaci�n en d�as.
     */
    double get_rotacion() const;

    /**
     * @brief Obtiene la inclinaci�n del planeta en el eje Z.
     * @return El valor de la inclinaci�n en Z.
     */
    double get_inclinacion_z() const;

    /**
     * @brief Obtiene la inclinaci�n del planeta en el eje Y.
     * @return El valor de la inclinaci�n en Y.
     */
    double get_inclinacion_y() const;

    /**
     * @brief Obtiene el tama�o del planeta.
     * @return El tama�o del planeta.
     */
    double get_tamano() const;

    /**
     * @brief Obtiene el tiempo delta utilizado en las simulaciones.
     * @return El tiempo delta.
     */
    double get_tiempo_delta() const;

    /**
     * @brief Obtiene la ubicaci�n actual del planeta en el eje X.
     * @return La ubicaci�n actual en el eje X.
     */
    double get_ubicacion_actual_eje() const;

    /**
     * @brief Obtiene la ubicaci�n actual del planeta en el sistema solar.
     * @return La ubicaci�n actual en el sistema solar.
     */
    double get_ubicacion_actual_sistema() const;

    /**
     * @brief Obtiene la posici�n X del planeta.
     * @return La posici�n X del planeta.
     */
    double get_p_x() const;

    /**
     * @brief Obtiene la posici�n Y del planeta.
     * @return La posici�n Y del planeta.
     */
    double get_p_y() const;

    /**
     * @brief Obtiene la posici�n Z del planeta.
     * @return La posici�n Z del planeta.
     */
    double get_p_z() const;

    /**
     * @brief Obtiene la ruta de la imagen que representa el planeta.
     * @return La ruta de la imagen.
     */
    std::string get_ruta_imagen() const;

    /**
     * @brief Obtiene la textura asociada al planeta.
     * @return Puntero a la textura del planeta.
     */
    igvTextura *get_textura() const;

    /**
     * @brief Obtiene el sat�lite del planeta, si lo tiene.
     * @return Puntero al sat�lite del planeta.
     */
    Planeta *get_satelite() const;

    // M�todos jer�rquicos

    /**
     * @brief Establece un nuevo padre para el planeta.
     * @param nuevoPadre El nuevo planeta padre.
     */
    void set_padre(Planeta *nuevoPadre);

    /**
     * @brief Obtiene los planetas hijos del planeta actual.
     * @return Un vector de punteros a los planetas hijos.
     */
    std::vector<Planeta *> get_hijos() const;
};

#endif /* Planeta_h */
