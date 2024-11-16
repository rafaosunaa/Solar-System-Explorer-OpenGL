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
    * Método que define el fondo de la escena.
    * Trata de una esfera donde se ubicarán todos los planetas.
    */
    void fondo();

private:
    //Planetas
    igvTextura(const igvTextura& textura) {}
	void operator=(const igvTextura& textura) {}
	GLuint textura;

    //Fondo
    igvTextura *texturaFondo;
    double tamFondo;


};

#endif // IGVTEXTURA_H
