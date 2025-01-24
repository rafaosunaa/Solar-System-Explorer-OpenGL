//
// Created by rafao on 04/12/2024.
//

#ifndef CAMARA_H
#define CAMARA_H

#if defined(__APPLE__) && defined(__MACH__)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
#endif

#include <cmath>

enum Vista {
    VISTA_NORMAL,
    VISTA_PLANTA,
    VISTA_PERFIL,
    VISTA_ABAJO,
};



class Camara {
private:
    Vista vistaActual;

    double arrastrarX, arrastrarY;
    double mouseX, mouseY;

public:
    Camara();

    void cambiarVista();
    void moverRaton(int key, int estado, int x, int y);
    void actualizarMovimiento(int x, int y);
    void ajustarVista(int ancho, int alto);
    Vista getVistaActual() const;

    void setVista(Vista nuevaVista);
    void incrementarZoom();
    void decrementarZoom();

    void setZoom(double nuevoZoom);
    double zoom;

    // Métodos de acceso
    double getMouseX() const { return mouseX; }
    double getMouseY() const { return mouseY; }
    double getArrastrarX() const { return arrastrarX; }
    double getArrastrarY() const { return arrastrarY; }
    double getZoom() const { return zoom; }
};

#endif // CAMARA_H

