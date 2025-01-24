//
// Created by rafao on 04/12/2024.
//

#include "Camara.h"

Camara::Camara()
    : vistaActual(VISTA_NORMAL), zoom(2), arrastrarX(-1), arrastrarY(-1), mouseX(0), mouseY(0) {}

void Camara::cambiarVista() {
    switch (vistaActual) {
        case VISTA_NORMAL:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60.0, 1.0, 1.0, 1500.0);
            glMatrixMode(GL_MODELVIEW);
            break;

        case VISTA_PLANTA:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);
            glMatrixMode(GL_MODELVIEW);
            break;

        case VISTA_PERFIL:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);
            glRotatef(90.0, 0.0, 0.0, 1.0);
            glMatrixMode(GL_MODELVIEW);
            break;

        case VISTA_ABAJO:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);
            glRotatef(180.0, 0.0, 0.0, 1.0);
            glMatrixMode(GL_MODELVIEW);
            break;
    }
}

void Camara::moverRaton(int key, int estado, int x, int y) {
    if (key == 0 && estado == 0) { // Bot�n izquierdo presionado
        if (arrastrarX == -1) {
            arrastrarX = x;
            arrastrarY = y;
        } else {
            arrastrarX += x - mouseX;
            arrastrarY += y - mouseY;
        }
        mouseX = x;
        mouseY = y;
    }
}

void Camara::actualizarMovimiento(int x, int y) {
    mouseX = x;
    mouseY = y;
}

void Camara::ajustarVista(int ancho, int alto) {
    glViewport(0, 0, ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)ancho / (GLfloat)alto, 1.0, 1500.0);
    glMatrixMode(GL_MODELVIEW);
}

void Camara::setZoom(double nuevoZoom) {
    zoom = nuevoZoom > 1.0 ? nuevoZoom : 1.0;
}


Vista Camara::getVistaActual() const {
    return vistaActual;
}

void Camara::setVista(Vista nuevaVista) {
    vistaActual = nuevaVista;
}

void Camara::incrementarZoom() {
    zoom++;
}

void Camara::decrementarZoom() {
    zoom--;
}


