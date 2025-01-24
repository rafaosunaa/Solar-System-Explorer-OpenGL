#include "igvTextura.h"
#include "lodepng.h"
#include <iostream>

/**
 * Constructor que carga una imagen PNG desde un archivo y la convierte en una textura para OpenGL.
 * @param imagenTextura Ruta de la imagen que será la textura a usar.
 */
igvTextura::igvTextura(const std::string& imagenTextura)
{
    std::vector<unsigned char> data; // Vector para almacenar los datos de la imagen
    unsigned ancho, alto;

    // Decodifica la imagen PNG
    unsigned error = lodepng::decode(data, ancho, alto, imagenTextura.c_str());
    if (error) {
        std::cerr << "Error cargando la imagen PNG (" << imagenTextura << "): "
                  << lodepng_error_text(error) << std::endl;
        return; // Salir si hubo un error
    }

    // Genera un identificador para la textura
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);

    // Modo envoltura de textura horizontal y vertical
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filtrado lineal para minimizar y maximizar
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Carga los datos de la imagen en la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
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

/**
 * Constructor adicional para inicializar con fondo.
 */
igvTextura::igvTextura(const std::string rutaImagen, double tamImagen)
    : texturaFondo(new igvTextura(rutaImagen)), tamFondo(tamImagen) {}



/**
 * @brief Configura y dibuja una esfera como fondo, aplicando textura, iluminación y material.
 *
 * Este método crea una esfera , configurando la textura, iluminación,
 * y el material antes de dibujarla. La esfera se dibuja en un plano 3D con iluminación, normales,
 * y textura aplicadas. Se utiliza la primera luz disponible y se configura el material difuso y especular
 * de la esfera.
 */
void igvTextura::fondo()
{
    GLUquadric* qobj = gluNewQuadric();
    gluQuadricOrientation(qobj, GLU_INSIDE);
    gluQuadricTexture(qobj, GL_TRUE);

    // Configura las normales para el sombreado de Gouraud
    gluQuadricNormals(qobj, GLU_SMOOTH);

    // Activar iluminación
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Usar la primera luz

    // Configuración básica de la luz
    GLfloat luzPosicion[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Posición de la luz
    GLfloat luzDifusa[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // Componente difusa
    GLfloat luzEspecular[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Componente especular
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    // Configura el material
    GLfloat materialDifuso[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Material difuso
    GLfloat materialEspecular[] = { 0.3f, 0.3f, 0.3f, 1.0f }; // Material especular
    GLfloat brillo[] = { 50.0f }; // Brillo del material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDifuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialEspecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brillo);

    glEnable(GL_TEXTURE_2D);
    texturaFondo->asociarTextura();

    glPushMatrix();
    glRotated(270.0f, 1.0f, 0.0f, 0.0f); // Rota la esfera
    gluSphere(qobj, tamFondo, 30, 30);  // Dibuja la esfera con normales y textura
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING); // Desactiva la iluminación después de usarla
    gluDeleteQuadric(qobj);
}

