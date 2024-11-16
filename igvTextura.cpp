#include "igvTextura.h"
#include "stb_image.h"
#include <iostream>


/**
 * Constructor que carga una imagen desde un archivo que se convertira en una textura para aplicarla a un objeto
 * @param imagenTextura ruta de la imagen que sera la textura a usar
 */
igvTextura::igvTextura(const std::string& imagenTextura)
{
	int ancho;
    int alto;
    int nComponentes;
    unsigned char* data = stbi_load((imagenTextura).c_str(), &ancho, &alto, &nComponentes, 4);

    //Generamos un identificador para la textura
    //Asociamos el identificar y la textura para aplicar todas las operaciones sobre esta
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);

    //Modo evoltura de textura horizontal y vertical
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Se aplica filtrado lineal, y filtro de textura para minimizacion y magnificacion
    //ASi se ve bien en diferentes escalas
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Carga los datos de la imagen en la textura asociada
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //Libera la memoria usada de la imagen
    stbi_image_free(data);
}


/**
 * Destructor
 */
igvTextura::~igvTextura()
{
	glDeleteTextures(1, &textura);
}


/**
 * Método que asocia la textura almacenada para las operaciones de dibujo posteriores
 */
void igvTextura::asociarTextura()
{
	glBindTexture(GL_TEXTURE_2D, textura);
}



igvTextura::igvTextura(const std::string rutaImagen, double tamImagen):
        texturaFondo(new igvTextura(rutaImagen)),
        tamFondo(tamImagen) {

}




/**
* @brief Dibuja el fondo de la escena utilizando una esfera
 * Esta función se encarga de dibujar el fondo de la escena mediante una esfera ,utilizando una textura asignada al fondo de la escena.
 */
void igvTextura::fondo() {
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricOrientation(qobj, GLU_INSIDE);
    gluQuadricTexture(qobj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    glRotated(270.0f, 1.0f, 0.0f, 0.0f); // Rota la esfera para ajustar la orientación
    texturaFondo->asociarTextura(); // Asocia la textura al fondo

    glPushMatrix();
    gluSphere(qobj, tamFondo, 30, 30); // Dibuja la esfera con la textura asignada
    glPopMatrix();

    glDisable(GL_TEXTURE_2D); // Deshabilita la textura después de su uso
    gluDeleteQuadric(qobj);
    glPopMatrix();
}
