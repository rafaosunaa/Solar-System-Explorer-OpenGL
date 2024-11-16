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
#include "igvTextura.h"


using namespace std;

class Planeta
{
public:
    // Atributos p�blicos

    float radio = 100.0; //radio del planeta
    string nombre; //nomrbe del planeta
    double velocidadOrbital; // velocidad del planeta alrededor del Sol
    double aphelion; //punto en la �rbita de un objeto alrededor del Sol donde est� m�s alejado de �ste.
    double perihelion; //punto en la �rbita de un cuerpo celeste alrededor del Sol en el que este cuerpo est� m�s cerca del Sol.
    double periodoOrbital;
    double rotacion;
    double inclinacionZ;
    double inclinacionY;
    double tamano;
    double tiempoDelta;

    double ubicacionActualEje;
    double ubicacionActualSistema;

    double pX;
    double pY;
    double pZ;

    string rutaImagen;
    igvTextura *textura;
    Planeta *satelite;

    // Atributos espec�ficos para los anillos de Urano
    double radioInteriorAnillo;
    double radioExteriorAnillo;
    void dibujarAnillosUrano();

    Planeta(string nombre, double aphelion, double perihelion, double periodoOrbital, double periodoRotacion,
            const std::string rutaImagen, double tamano, double inclinacion, Planeta *sateliteDe = NULL);

    virtual ~Planeta();

    void Orbita(double grado, double escalaRotacionEje);

    void dibujarPlaneta();



private:
    Planeta(const Planeta& planeta) {}
    void operator=(const Planeta& planeta) {}
    void dibujarEsfera(float escala);

};


#endif /* Planeta_h */