#ifndef IGVTEXTURA_H
#define IGVTEXTURA_H

#include <string>
#if defined(__APPLE__) && defined(__MACH__)

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#else

#include <GL/glut.h>

#endif   // defined(__APPLE__) && defined(__MACH__)

/**
 * @class igvTextura
 * @brief Clase para representar una textura en OpenGL.
 *
 * Permite cargar una imagen desde un archivo y convertirla en una textura
 * para aplicarla a un objeto.
 */
class igvTextura
{
public:

    /**
     * Constructor que carga una imagen desde un archivo y la convierte en una textura.
     * @param imagenTextura Ruta de la imagen que será utilizada como textura.
     */
	igvTextura(const std::string& imagenTextura);


    /**
     * Método que asocia la textura almacenada para las operaciones de dibujo posteriores.
     */
	void asociarTextura();


    /**
     * Destructor de la clase.
     */
	virtual ~igvTextura();


    /**
   * @brief Constructor privado para la creación del fondo de la escena.
   * @param rutaImagen Ruta de la imagen para el fondo.
   * @param tamImagen Tamaño de la imagen.
   */
    igvTextura(const std::string rutaImagen, double tamImagen);

 /**
 * @brief Método que define el fondo de la escena.
 *
 * Este método configura una esfera que servirá como fondo de la escena, sobre la cual
 * se ubicarán los planetas y otros objetos. La esfera se dibuja con una textura y se puede
 * manipular su tamaño.
 */
    void fondo();

private:
    // Planetas
    igvTextura(const igvTextura& textura) {} ///< Constructor de copia privado.
    void operator=(const igvTextura& textura) {} ///< Operador de asignación privado.
    GLuint textura; ///< Identificador de la textura cargada para objetos.

    // Fondo
    igvTextura *texturaFondo; ///< Objeto que representa la textura de fondo.
    double tamFondo; ///< Tamaño del fondo (esfera).


};

#endif // IGVTEXTURA_H
