#include <iostream>
#include <math.h>
#include "Planeta.h"
#include "igvTextura.h"


/**
 * @brief Constructor de la clase Planeta.
 * @param nombre Nombre del planeta.
 * @param aphelion Distancia máxima del planeta al Sol.
 * @param perihelion Distancia mínima del planeta al Sol.
 * @param periodoOrbital Tiempo en años que tarda el planeta en completar una órbita alrededor del Sol.
 * @param periodoRotacion Tiempo que tarda el planeta en completar una rotación sobre su eje.
 * @param rutaImagen Ruta de la imagen que representa el planeta.
 * @param tamano Tamaño del planeta.
 * @param inclinacion Ángulo de inclinación orbital del planeta respecto al plano de la eclíptica.
 * @param satelite Puntero al planeta satélite (si lo tiene).
 */
Planeta::Planeta(string nombre, double aphelion, double perihelion, double periodoOrbital,
                 double periodoRotacion,
                 string rutaImagen, double tamano, double inclinacion, Planeta *satelite):
        textura(new igvTextura(rutaImagen)),
        rotacion(periodoRotacion),
        nombre(nombre),
        aphelion(aphelion),
        ubicacionActualEje(0),
        perihelion(perihelion),
        periodoOrbital(periodoOrbital),
        rutaImagen(rutaImagen),
        tamano(tamano),
        satelite(satelite),
        inclinacionZ(inclinacion),
        inclinacionY(rand() % 180)
{

}


/**
 * Destructor
 */
Planeta::~Planeta() {
    delete textura;
    delete satelite;
}


/**
 * @brief Calcula la órbita del planeta.
 * calcula la posición del planeta basándose en el grado de rotación.
 * @param grado Grado de rotación para simular el movimiento.
 * @param escalaRotacionEje Escala de rotación del eje.
 */
void Planeta::Orbita(double grado, double escalaRotacionEje)
{
    ubicacionActualEje += grado * escalaRotacionEje / rotacion;
    ubicacionActualSistema += grado / (periodoOrbital == 0 ? 1 : periodoOrbital);

    ubicacionActualSistema = ubicacionActualSistema > 360 ? ubicacionActualSistema - 360 : ubicacionActualSistema;
    ubicacionActualEje = ubicacionActualEje > 360 ? ubicacionActualEje - 360 : ubicacionActualEje;
}


/**
 * Metodo que dibuja un planeta co nsus caracteristicas
 */
void Planeta::dibujarPlaneta()
{
    // Definición de la posición de la luz y del ambiente
    GLfloat posicion[] = {-2.0, 0.0, 0.0, 1.0};
    GLfloat luzAmbiente[] = {0.3, 0.3, 0.3, 1.0};

    const double pi = 3.1416;
    const double gradosARadianes = 57.29577951;
    double trasladoSistemaX = 0.05 * (aphelion + perihelion);
    double trasladoSistemaZ = 0.05 * (aphelion + perihelion);




    // Determinar la posición del planeta en función de su ubicación en la órbita
    if(nombre == "Sol")
        pX = -2;
    else
        pX = -cos((double)(ubicacionActualSistema / gradosARadianes + pi)) * trasladoSistemaX;

    pY = 0;

    if(satelite == NULL)
        pZ = sin((double)(ubicacionActualSistema / gradosARadianes + pi)) * trasladoSistemaZ;
    else
        pZ = sin((double)(ubicacionActualSistema / gradosARadianes + pi)) * trasladoSistemaX;

    // Configuración de las luces
    if(nombre == "Sol")
    {
        glLightfv(GL_LIGHT0, GL_POSITION, posicion);
        glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
    }
    else
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        //glEnable(GL_LIGHT1);
        if(satelite == NULL)
        {
            pX += -(trasladoSistemaX + trasladoSistemaZ) / 3;
        }
    }

    if(satelite != NULL)
    {
        glPushMatrix();
        glTranslated(satelite->pX, satelite->pY, satelite->pZ);
    }

    // Se dibuja la órbita si no es el Sol y no tiene satélite
    glPushMatrix();
    if(satelite == NULL && nombre != "Sol")
    {
        glTranslated(-(trasladoSistemaX + trasladoSistemaZ) / 3, 0, 0);
        glScaled(1, 1, trasladoSistemaZ / trasladoSistemaX);
        glRotated(90, 1.0, 0.0, 0.0);


        glDisable(GL_LIGHTING);
        glColor3f(0.1f, 0.3f, 0.5f);
        dibujarEsfera(trasladoSistemaX);
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_LIGHTING);

    }
    glPopMatrix();

    // Se establece la inclinación del planeta si tiene satélite
    glPushMatrix();
    if(satelite != NULL)
    {
        glRotated(inclinacionY, 0, 1, 0);
        glRotated(inclinacionZ, 1, 0, 0);
    }
    glTranslated(pX, pY, pZ);

    //se crea el planeta
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    glRotated(270.0f, 1.0f, 0.0f, 0.0f);
    textura->asociarTextura();// Asociar la textura al planeta

    glPushMatrix();
    glRotated(ubicacionActualEje, 0, 0, 1);
    gluSphere(qobj, tamano/3, 30, 30);// Dibuja el planeta
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(qobj);

    //No aplicamos luces si se trata del sol
    if(nombre != "Sol")
    {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
    }
    glPopMatrix();




    if(satelite != NULL)
    {
        glPopMatrix();
    }


}




/**
 * Metodo que Dibuja una esfera con una cierta escala y detalle
 * @param escala : escala que tendra la esfera
 * detalle :  controla la "suavidad" o la cantidad de segmentos que se utilizan para aproximar la forma circular
 */
void Planeta::dibujarEsfera(float escala) {

    int detalle = 180; // Cantidad de segmentos para dibujar la esfera

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

