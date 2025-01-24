# Solar System Explorer 🌌
Described in detail in the document titled **"Documentación.pdf"**.

This project is an interactive simulation that allows users to explore the solar system in detail. Through dynamic views and intuitive controls, users can study the planets, their orbits, and their relationships with satellites, as well as interact with a functional satellite model.

---

## Main Features
- **View Navigation**: Switch between different perspectives (normal, top-down, side, and split view).
- **Zoom and Camera Movement**: Zoom in to observe details or zoom out for an overview.
- **Planet Selection**: Switch between planets using keys or a context menu.
- **Satellite Interaction**: Control solar panels and rotations.
- **Animation**: Enable/disable animations and adjust orbital speeds.

---

## 🎥 Demonstration Video  
You can watch the full functionality of the project in this video:  
[![Solar System Explorer - Video](https://img.youtube.com/vi/zb7eA66MRnI/0.jpg)](https://youtu.be/zb7eA66MRnI)

---

## Detailed Controls

### View Navigation
- **Switch views**: Press `v` to toggle between:
  - Normal View: Default perspective.
  - Top-Down View: A perspective from above to analyze orbital positions.
  - Side View: A lateral perspective ideal for alignments.
- **Split View**: Press `f` to toggle between a single view and a split view showing multiple perspectives simultaneously (top-down, side, and normal).

### Zoom and Camera Movement
- **Zoom**:
  - Zoom in: Press `+`
  - Zoom out: Press `-`
- **Move the camera**: Drag the mouse while holding the left button.

### Planet Selection
- Use numeric keys (`1-9`) to select a planet directly.
- Right-click to open a context menu with advanced options, such as orbit adjustments.

### Satellite Interaction
- **Control solar panels**:
  - Rotate the left panel: `i` / `I` (up/down)
  - Rotate the right panel: `d` / `D` (up/down)
- **Rotate satellite body segments**:
  - Rotate forward: `u`
  - Rotate backward: `j`
- **Adjust rotation speed**:
  - Increase speed: `r`
  - Decrease speed: `R`

### Additional Controls
- **Show/Hide on-screen controls**: Press `c`.
- **Exit the application**: Press `Esc`.

### Animation
- **Enable/Disable satellite animation**: Press `t`.
- **Adjust orbital speed**:
  - Accelerate: Press `a`
  - Decelerate: Press `A`.

---

## Technologies Used
- **OpenGL**: Real-time graphical rendering.
- **LodePNG**: PNG texture handling.
- **Scene Graph Hierarchy**: Structured organization of planets, satellites, and cameras.

---

## Installation
1. Clone this repository:
   ```bash
   git clone <repository>
   cd <directory>
2.Asegúrate de tener las siguientes dependencias:
-OpenGL
-Biblioteca lodepng

3.Compila el proyecto (ejemplo para GCC):
```bash
g++ -o ExploradorSistemaSolar main.cpp -lGL -lGLU -lglut
```



---




# Explorador del Sistema Solar 🌌
Descrito en detalle en el documento titulado **"Documentación.pdf"**.

Este proyecto es una simulación interactiva que permite explorar el sistema solar en detalle. A través de vistas dinámicas y controles intuitivos, los usuarios pueden estudiar los planetas, sus órbitas y la relación con sus satélites, además de interactuar con un modelo de satélite funcional.

---

## Características principales
- **Navegación entre vistas**: Cambia entre diferentes perspectivas (normal, planta, perfil y vista dividida).
- **Zoom y movimiento de cámara**: Acércate para observar detalles o aléjate para una vista general.
- **Selección de planetas**: Alterna entre planetas usando teclas o un menú contextual.
- **Interacción con satélites**: Controla paneles solares y rotaciones.
- **Animación**: Activa/desactiva animaciones y ajusta velocidades orbitales.

---

## 🎥 Vídeo de demostración  
Puedes ver el funcionamiento completo del proyecto en el siguiente video:  
[![Explorador del Sistema Solar - Vídeo](https://img.youtube.com/vi/zb7eA66MRnI/0.jpg)](https://youtu.be/zb7eA66MRnI)

---

## Controles detallados

### Navegación entre vistas
- **Cambiar vistas**: Presiona `v` para alternar entre:
  - Vista Normal: perspectiva predeterminada.
  - Vista de Planta: vista desde arriba para analizar posiciones orbitales.
  - Vista de Perfil: vista lateral ideal para alineaciones.
- **Vista dividida**: Presiona `f` para alternar entre una sola vista y una división en múltiples vistas simultáneas (planta, perfil y normal).

### Zoom y movimiento de cámara
- **Zoom**:
  - Acercar: Presiona `+`
  - Alejar: Presiona `-`
- **Mover la cámara**: Arrastra el ratón mientras mantienes presionado el botón izquierdo.

### Selección de planetas
- Usa las teclas numéricas (`1-9`) para seleccionar un planeta directamente.
- Haz clic derecho para abrir un menú contextual con opciones avanzadas, como ajustes de órbita.

### Interacción con satélites
- **Control de paneles solares**:
  - Rotar el panel izquierdo: `i` / `I` (arriba/abajo)
  - Rotar el panel derecho: `d` / `D` (arriba/abajo)
- **Rotación de segmentos del cuerpo del satélite**:
  - Rotar hacia adelante: `u`
  - Rotar hacia atrás: `j`
- **Ajustar velocidad de rotación**:
  - Aumentar velocidad: `r`
  - Disminuir velocidad: `R`

### Controles adicionales
- **Mostrar/Ocultar controles en pantalla**: Presiona `c`.
- **Salir de la aplicación**: Presiona `Esc`.

### Animación
- **Activar/Desactivar animación del satélite**: Presiona `t`.
- **Ajustar velocidad orbital**:
  - Acelerar: Presiona `a`
  - Desacelerar: Presiona `A`.

---

## Tecnologías utilizadas
- **OpenGL**: Renderizado gráfico en tiempo real.
- **LodePNG**: Manejo de texturas en formato PNG.
- **Jerarquía de grafos de escena**: Organización estructurada de planetas, satélites y cámaras.

---

## Instalación
1. Clona este repositorio:
   ```bash
   git clone <repositorio>
   cd <directorio>

2.Asegúrate de tener las siguientes dependencias:
-OpenGL
-Biblioteca lodepng

3.Compila el proyecto (ejemplo para GCC):
```bash
g++ -o ExploradorSistemaSolar main.cpp -lGL -lGLU -lglut  
