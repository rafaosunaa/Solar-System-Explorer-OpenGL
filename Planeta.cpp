#include <iostream>
#include <math.h>
#include "Planeta.h"
#include "igvTextura.h"


/**
 * @brief Constructor de la clase Planeta.
 * @param nombre Nombre del planeta.
 * @param aphelion Distancia m�xima del planeta al Sol.
 * @param perihelion Distancia m�nima del planeta al Sol.
 * @param periodoOrbital Tiempo en a�os que tarda el planeta en completar una �rbita alrededor del Sol.
 * @param periodoRotacion Tiempo que tarda el planeta en completar una rotaci�n sobre su eje.
 * @param rutaImagen Ruta de la imagen que representa el planeta.
 * @param tamano Tama�o del planeta.
 * @param inclinacion �ngulo de inclinaci�n orbital del planeta respecto al plano de la ecl�ptica.
 * @param satelite Puntero al planeta sat�lite (si lo tiene).
 */
Planeta::Planeta(const std::string &nombre, float aphelion, float perihelion, float periodoOrbital,
                 float periodoRotacion, const std::string &rutaImagen, float tamano, Planeta *padre)
    : nombre(nombre), aphelion(aphelion), perihelion(perihelion), periodoOrbital(periodoOrbital),
      rotacion(periodoRotacion), inclinacionY(0), inclinacionZ(0), tamano(tamano), radio(0),
      velocidadOrbital(0), tiempoDelta(0), ubicacionActualEje(0), ubicacionActualSistema(0),
      pX(0), pY(0), pZ(0), rutaImagen(rutaImagen), textura(new igvTextura(rutaImagen)),
      satelite(nullptr), padre(padre) {
    if (padre) {
        padre->hijos.push_back(this);
    }
}


/**
 * @brief Destructor de la clase Planeta.
 * Libera la memoria ocupada por la textura y el satélite, si existen.
 */
Planeta::~Planeta() {
    delete textura;
    delete satelite;
}

/**
 * @brief Establece un nuevo padre para el planeta y lo agrega a la lista de hijos del nuevo padre.
 * @param nuevoPadre El nuevo planeta padre del planeta actual.
 */
void Planeta::set_padre(Planeta *nuevoPadre) {
    padre = nuevoPadre;
    if (nuevoPadre) {
        nuevoPadre->hijos.push_back(this);
    }
}

/**
 * @brief Obtiene la lista de los planetas hijos del planeta actual.
 * @return Un vector de punteros a los planetas hijos.
 */
std::vector<Planeta *> Planeta::get_hijos() const {
    return hijos;
}

/**
 * @brief Calcula la órbita del planeta y actualiza su posición en el sistema solar.
 * @param grado Grado de rotación utilizado para simular el movimiento del planeta.
 * @param escalaRotacionEje Escala de la rotación del eje del planeta.
 */
void Planeta::Orbita(double grado, double escalaRotacionEje)
{
    ubicacionActualEje += grado * escalaRotacionEje / rotacion;
    ubicacionActualSistema += grado / (periodoOrbital == 0 ? 1 : periodoOrbital);

    ubicacionActualSistema = ubicacionActualSistema > 360 ? ubicacionActualSistema - 360 : ubicacionActualSistema;
    ubicacionActualEje = ubicacionActualEje > 360 ? ubicacionActualEje - 360 : ubicacionActualEje;
}

/**
 * @brief Dibuja el planeta con sus características, incluyendo su órbita, textura y posición.
 */
void Planeta::dibujarPlaneta() {
    // Definición de la posición de la luz y del ambiente
    GLfloat posicion[] = {-2.0, 0.0, 0.0, 1.0};
    const double pi = 3.1416;
    const double gradosARadianes = 57.29577951;

    // Cálculo del desplazamiento en la órbita
    double trasladoSistemaX = 0.05 * (aphelion + perihelion);
    double trasladoSistemaZ = 0.05 * (aphelion + perihelion);

    // Determinar la posición del planeta en función de su órbita
    if (nombre == "Sol") {
        pX = -2.0;
    } else {
        pX = -cos((double)(ubicacionActualSistema / gradosARadianes + pi)) * trasladoSistemaX;
    }
    pY = 0.0;
    if (satelite == nullptr) {
        pZ = sin((double)(ubicacionActualSistema / gradosARadianes + pi)) * trasladoSistemaZ;
    } else {
        pZ = sin((double)(ubicacionActualSistema / gradosARadianes + pi)) * trasladoSistemaX;
    }

    // Configuración de las luces
    if (nombre == "Sol") {
        glLightfv(GL_LIGHT0, GL_POSITION, posicion);
    } else {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }

    // Ajustar la posición si no es un satélite
    if (satelite == nullptr) {
        pX += -(trasladoSistemaX + trasladoSistemaZ) / 3.0;
    }

    // Si es un satélite, se traslada a la posición de su planeta padre
    if (satelite != nullptr) {
        glPushMatrix();
        glTranslated(satelite->pX, satelite->pY, satelite->pZ);
    }

    // Dibujar la órbita si no es el Sol y no es un satélite
    glPushMatrix();
    if (satelite == nullptr && nombre != "Sol") {
        glTranslated(-(trasladoSistemaX + trasladoSistemaZ) / 3.0, 0.0, 0.0);
        glScaled(1.0, 1.0, trasladoSistemaZ / trasladoSistemaX);
        glRotated(90, 1.0, 0.0, 0.0);

        glDisable(GL_LIGHTING);
        glColor3f(0.1f, 0.3f, 0.5f);
        dibujarEsfera(trasladoSistemaX); // Dibuja la órbita como una esfera
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();

    // Establecer inclinación si es un satélite
    glPushMatrix();
    if (satelite != nullptr) {
        glRotated(inclinacionY, 0.0, 1.0, 0.0);
        glRotated(inclinacionZ, 1.0, 0.0, 0.0);
    }
    glTranslated(pX, pY, pZ);

    // Dibujar el planeta
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    glRotated(270.0, 1.0, 0.0, 0.0);
    textura->asociarTextura(); // Asociar la textura al planeta

    glPushMatrix();
    glRotated(ubicacionActualEje, 0, 0, 1); // Rotación propia del planeta
    gluSphere(qobj, tamano / 3.0, 60, 60); // Dibuja el planeta
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(qobj);

    // Deshabilitar luces si no es el Sol
    if (nombre != "Sol") {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
    }
    glPopMatrix();

    // Si es un satélite, restaurar la matriz previa
    if (satelite != nullptr) {
        glPopMatrix();
    }

    // Dibujar los hijos recursivamente
    for (Planeta* hijo : hijos) {
        hijo->dibujarPlaneta();
    }
}

/**
 * @brief Dibuja una esfera con una cierta escala y detalle.
 * @param escala Escala de la esfera.
 * @param detalle Número de segmentos para aproximar la forma circular de la esfera.
 */
void Planeta::dibujarEsfera(float escala) {
    int detalle = 500; // Aumentar el detalle para más segmentos

    glPushMatrix();
    glScaled(escala, escala, escala); // Escala la esfera según el tamaño proporcionado

    // Dibuja la esfera como un conjunto de líneas conectadas para simular la forma
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < detalle; ++i) {
        // Calcula los puntos en el perímetro de la esfera usando funciones trigonométricas
        glVertex2d(cos(2 * i * M_PI / detalle), sin(2 * i * M_PI / detalle));
    }
    glEnd();
    glPopMatrix();
}

/**
 * Métodos de acceso para obtener las propiedades del planeta.
 * Estos métodos permiten obtener el nombre, tamaño, velocidad orbital, etc., del planeta.
 */
float Planeta::get_radio() const {
    return radio;
}

string Planeta::get_nombre() const {
    return nombre;
}

double Planeta::get_velocidad_orbital() const {
    return velocidadOrbital;
}

double Planeta::get_aphelion() const {
    return aphelion;
}

double Planeta::get_perihelion() const {
    return perihelion;
}

double Planeta::get_periodo_orbital() const {
    return periodoOrbital;
}

double Planeta::get_rotacion() const {
    return rotacion;
}

double Planeta::get_inclinacion_z() const {
    return inclinacionZ;
}

double Planeta::get_inclinacion_y() const {
    return inclinacionY;
}

double Planeta::get_tamano() const {
    return tamano;
}

double Planeta::get_tiempo_delta() const {
    return tiempoDelta;
}

double Planeta::get_ubicacion_actual_eje() const {
    return ubicacionActualEje;
}

double Planeta::get_ubicacion_actual_sistema() const {
    return ubicacionActualSistema;
}

double Planeta::get_p_x() const {
    return pX;
}

double Planeta::get_p_y() const {
    return pY;
}

double Planeta::get_p_z() const {
    return pZ;
}

string Planeta::get_ruta_imagen() const {
    return rutaImagen;
}

igvTextura * Planeta::get_textura() const {
    return textura;
}

Planeta * Planeta::get_satelite() const {
    return satelite;
}
