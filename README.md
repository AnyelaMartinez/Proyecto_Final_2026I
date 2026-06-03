# Mundo de Chilly Willy - Qt Widgets

Proyecto completo en C++/Qt con archivos en la misma carpeta, como los crea Qt Creator.

## Que incluye

- `mainwindow.ui` con la interfaz grafica.
- `QGraphicsView` y `QGraphicsScene` para dibujar el juego.
- Personajes visibles: Chilly Willy, Smedley y pescado dorado.
- Piedra de curling con fuerza, angulo, velocidad y friccion.
- Casa/objetivo con puntuacion.
- Zonas: hielo normal, hielo resbaladizo y nieve espesa.
- Nivel 1: lanzamiento con vista superior.
- Nivel 2: barrido con tecla espacio o boton.
- Agente IA con margen de error.
- Guardar y cargar partida en JSON.
- Musica con `QMediaPlayer`.

## Como abrir

1. Abre Qt Creator.
2. `File > Open File or Project`.
3. Abre `MundoChillyWillyQt.pro`.
4. Configura el kit.
5. Ejecuta.

## Musica

Para que suene musica, copia un archivo MP3 llamado:

```text
musica.mp3
```

junto al ejecutable, o crea esta carpeta junto al ejecutable:

```text
sonidos/musica.mp3
```

Si no encuentra la musica, el juego funciona igual.

## Controles

- Flecha arriba: mover Chilly Willy hacia arriba.
- Flecha abajo: mover Chilly Willy hacia abajo.
- Flecha izquierda: mover Chilly Willy hacia la izquierda.
- Flecha derecha: mover Chilly Willy hacia la derecha.
- Espacio: barrer.
- Slider de fuerza: controla fuerza del lanzamiento.
- Slider de angulo: controla direccion.
- Boton `Lanzar piedra`: lanza la piedra.
- Boton `Cambiar nivel`: alterna entre nivel 1 y nivel 2.

## Como agarrar el pescado

Mueve a Chilly Willy con las flechas hasta tocar el pescado dorado. El pescado se mueve de lado a lado y flota. Cuando Chilly lo toca, se activa un bonus de lanzamiento.

## Turno de la IA

Despues del lanzamiento de Chilly, aparece una segunda piedra para la IA. Esa piedra se mueve sola y suma puntos al oponente cuando se detiene.
