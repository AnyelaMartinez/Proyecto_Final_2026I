"""Genera las hojas de sprites para Chilly, Smedley y el pez dorado.
Estilo cartoon mas organico inspirado en los Looney Tunes clasicos.
Cada frame es de 96x96 px."""

from PIL import Image, ImageDraw
import os
import math

SIZE = 96
OUT_DIR = os.path.dirname(os.path.abspath(__file__))


def _vientre_blanco(d, cx, cy_top, cy_bot, w_top, w_bot):
    """Dibuja el vientre blanco con la curva 'tuxedo' del pinguino"""
    pts = []
    # Lado izquierdo (curva)
    for t in range(0, 11):
        f = t / 10.0
        x = cx - (w_top + (w_bot - w_top) * f) / 2
        y = cy_top + (cy_bot - cy_top) * f
        pts.append((x, y))
    # Lado derecho (curva, al reves)
    for t in range(10, -1, -1):
        f = t / 10.0
        x = cx + (w_top + (w_bot - w_top) * f) / 2
        y = cy_top + (cy_bot - cy_top) * f
        pts.append((x, y))
    d.polygon(pts, fill=(248, 248, 252))


# ============================================================================
# CHILLY WILLY (4 frames: saludando, caminando-izq, caminando-der, lanzando)
# ============================================================================

def _dibujar_escoba(d, angulo_grados, brillo=False):
    """Dibuja una escoba de curling con el angulo dado.
    Sale desde aprox (48, 60) y se extiende hacia abajo-derecha."""
    rad = math.radians(angulo_grados)
    x0, y0 = 48, 60  # origen (manos de chilly)
    largo = 38
    x1 = x0 + int(largo * math.cos(rad))
    y1 = y0 + int(largo * math.sin(rad))
    # Mango cafe
    d.line([(x0, y0), (x1, y1)], fill=(140, 85, 40), width=5)
    # Borde del mango
    d.line([(x0, y0), (x1, y1)], fill=(80, 50, 20), width=1)
    # Cabezal del cepillo (perpendicular al mango, rojo)
    perp = math.radians(angulo_grados + 90)
    bw = 12  # ancho del cabezal
    cx = x1 + int(6 * math.cos(rad))
    cy = y1 + int(6 * math.sin(rad))
    # Esquinas del rectangulo del cepillo
    p1 = (cx + int(bw * math.cos(perp)), cy + int(bw * math.sin(perp)))
    p2 = (cx - int(bw * math.cos(perp)), cy - int(bw * math.sin(perp)))
    # Hacer un rectangulo aplastado
    h = 5  # alto del cepillo
    p3 = (p2[0] + int(h * math.cos(rad)), p2[1] + int(h * math.sin(rad)))
    p4 = (p1[0] + int(h * math.cos(rad)), p1[1] + int(h * math.sin(rad)))
    d.polygon([p1, p2, p3, p4], fill=(200, 30, 30), outline=(120, 15, 15))
    # Cerdas amarillas debajo del cepillo
    p5 = (p3[0] + int(4 * math.cos(rad)), p3[1] + int(4 * math.sin(rad)))
    p6 = (p4[0] + int(4 * math.cos(rad)), p4[1] + int(4 * math.sin(rad)))
    d.polygon([p3, p4, p6, p5], fill=(220, 180, 60), outline=(160, 120, 30))
    # Lineas de barrido en el suelo (motion lines)
    if brillo:
        sx = cx + int(15 * math.cos(rad))
        sy = cy + int(15 * math.sin(rad)) + 4
        d.line([(sx - 8, sy), (sx + 8, sy)], fill=(200, 220, 240, 200), width=2)
        d.line([(sx - 6, sy + 3), (sx + 6, sy + 3)], fill=(200, 220, 240, 180), width=1)


def chilly_frame(idx):
    img = Image.new("RGBA", (SIZE, SIZE), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)

    # Sombra debajo (oval aplastado)
    d.ellipse([14, 86, 82, 94], fill=(0, 0, 0, 90))

    # ==== Cuerpo: combinacion de elipses para forma de pera ====
    # Cuerpo principal grande
    d.ellipse([18, 32, 78, 88], fill=(28, 32, 50), outline=(0, 0, 0), width=2)
    # Cabeza (oval mas pequeno arriba, fusionado)
    d.ellipse([22, 18, 74, 62], fill=(28, 32, 50), outline=(0, 0, 0), width=2)
    # Cubrir union (sin outline para que se vea continuo)
    d.ellipse([23, 30, 73, 50], fill=(28, 32, 50))

    # ==== Vientre blanco tipo "tuxedo" (estrecho arriba, ancho abajo) ====
    _vientre_blanco(d, cx=48, cy_top=42, cy_bot=84, w_top=24, w_bot=42)

    # ==== Gorro rojo (inclinado a la derecha) ====
    # Base del gorro
    d.polygon([(28, 28), (66, 22), (70, 14), (38, 12)],
              fill=(210, 30, 30), outline=(120, 15, 15), width=2)
    # Punta inclinada
    d.polygon([(66, 22), (70, 14), (78, 6), (74, 10)],
              fill=(210, 30, 30), outline=(120, 15, 15), width=2)
    # Banda blanca abajo
    d.polygon([(26, 28), (66, 22), (66, 26), (28, 32)],
              fill=(245, 245, 250), outline=(120, 15, 15), width=1)
    # Pompom blanco grande
    d.ellipse([72, 0, 90, 16], fill=(252, 252, 255), outline=(180, 180, 190), width=2)
    d.ellipse([75, 3, 81, 9], fill=(255, 255, 255))  # brillo

    # ==== Ojos enormes y expresivos ====
    # Sclera
    d.ellipse([26, 30, 50, 56], fill=(252, 252, 255), outline=(0, 0, 0), width=2)
    d.ellipse([48, 30, 72, 56], fill=(252, 252, 255), outline=(0, 0, 0), width=2)
    # Pupila grande
    d.ellipse([33, 38, 46, 54], fill=(15, 15, 25))
    d.ellipse([54, 38, 67, 54], fill=(15, 15, 25))
    # Brillo
    d.ellipse([36, 40, 42, 46], fill=(255, 255, 255))
    d.ellipse([57, 40, 63, 46], fill=(255, 255, 255))
    # Brillo pequeno
    d.ellipse([41, 47, 44, 50], fill=(255, 255, 255))
    d.ellipse([62, 47, 65, 50], fill=(255, 255, 255))

    # ==== Pico naranja ====
    if idx == 3:  # lanzando - pico abierto gritando
        # Pico superior
        d.polygon([(38, 56), (58, 56), (48, 62)],
                  fill=(255, 165, 30), outline=(180, 100, 15), width=2)
        # Boca abierta (negro)
        d.polygon([(42, 60), (54, 60), (48, 68)], fill=(80, 30, 10))
        # Lengua
        d.ellipse([45, 62, 51, 66], fill=(220, 80, 80))
    else:
        # Pico cerrado
        d.polygon([(40, 56), (56, 56), (48, 64)],
                  fill=(255, 165, 30), outline=(180, 100, 15), width=2)
        d.line([(40, 60), (56, 60)], fill=(180, 100, 15), width=1)

    # ==== Aletas (varian por frame) ====
    if idx == 0:  # saludando con la aleta derecha arriba
        # Aleta izquierda al costado
        d.polygon([(18, 50), (8, 55), (10, 75), (22, 72)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)
        # Aleta derecha levantada
        d.polygon([(78, 50), (88, 30), (92, 36), (82, 60)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)
        # "Dedos" de la aleta
        d.line([(86, 32), (90, 28)], fill=(0, 0, 0), width=1)
        d.line([(88, 36), (94, 34)], fill=(0, 0, 0), width=1)
    elif idx == 1:  # walk1 - aletas separadas
        d.polygon([(16, 48), (8, 60), (12, 78), (22, 70)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)
        d.polygon([(74, 48), (88, 56), (82, 76), (78, 70)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)
    elif idx == 2:  # walk2 - aletas pegadas
        d.polygon([(20, 50), (12, 56), (16, 78), (24, 72)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)
        d.polygon([(72, 50), (84, 56), (80, 78), (74, 72)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)
    elif idx == 3:  # lanzando - aleta derecha extendida adelante
        d.polygon([(20, 48), (10, 60), (14, 80), (24, 72)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)
        # Aleta derecha extendida al frente (hacia abajo-derecha)
        d.polygon([(74, 56), (94, 64), (92, 76), (76, 74)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)
    elif idx in (4, 5):  # barriendo - ambas aletas adelante agarrando la escoba
        # Aleta izquierda
        d.polygon([(28, 54), (38, 58), (42, 68), (32, 70)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)
        # Aleta derecha
        d.polygon([(58, 56), (52, 64), (54, 72), (62, 72)],
                  fill=(28, 32, 50), outline=(0, 0, 0), width=2)

    # ==== Pies naranjas (en patitas separadas) ====
    if idx in (0, 3, 4, 5):
        d.ellipse([28, 84, 46, 94], fill=(255, 165, 30), outline=(180, 100, 15), width=1)
        d.ellipse([50, 84, 68, 94], fill=(255, 165, 30), outline=(180, 100, 15), width=1)
    elif idx == 1:
        d.ellipse([24, 84, 44, 94], fill=(255, 165, 30), outline=(180, 100, 15), width=1)
        d.ellipse([52, 86, 70, 94], fill=(255, 165, 30), outline=(180, 100, 15), width=1)
    elif idx == 2:
        d.ellipse([26, 86, 44, 94], fill=(255, 165, 30), outline=(180, 100, 15), width=1)
        d.ellipse([52, 84, 70, 94], fill=(255, 165, 30), outline=(180, 100, 15), width=1)

    # ==== Escoba de curling (encima del cuerpo en frames 4 y 5) ====
    if idx == 4:
        _dibujar_escoba(d, angulo_grados=35, brillo=True)
    elif idx == 5:
        _dibujar_escoba(d, angulo_grados=50, brillo=True)

    return img


# ============================================================================
# SMEDLEY (5 frames: 4 corriendo + 1 gruñido)
# ============================================================================

def smedley_frame(idx):
    img = Image.new("RGBA", (SIZE, SIZE), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)

    # Sombra
    d.ellipse([8, 80, 88, 92], fill=(0, 0, 0, 90))

    # ==== Cuerpo: ovalo cafe ====
    d.ellipse([14, 42, 70, 80], fill=(155, 105, 60), outline=(70, 40, 15), width=2)
    # Vientre crema (mas pequeno)
    d.ellipse([22, 52, 60, 78], fill=(225, 195, 150))

    # ==== Cabeza grande (proporción cartoon) ====
    # Forma principal redonda
    d.ellipse([50, 22, 90, 66], fill=(155, 105, 60), outline=(70, 40, 15), width=2)
    # Hocico grande y prominente (crema)
    d.ellipse([60, 40, 92, 64], fill=(225, 195, 150), outline=(70, 40, 15), width=2)

    # ==== Nariz negra ENORME ====
    d.ellipse([78, 44, 94, 58], fill=(15, 15, 15), outline=(0, 0, 0))
    # Brillo de la nariz
    d.ellipse([82, 46, 86, 50], fill=(80, 80, 80))

    # ==== Orejas caidas ====
    # Oreja trasera (mas pequena, atras de la cabeza)
    d.polygon([(54, 28), (46, 30), (40, 54), (48, 60), (58, 50)],
              fill=(120, 75, 35), outline=(60, 30, 10), width=2)
    # Oreja frontal (caida, mas grande)
    d.polygon([(60, 22), (54, 30), (52, 56), (62, 60), (66, 30)],
              fill=(135, 85, 45), outline=(60, 30, 10), width=2)

    # ==== Ojos caidos / droopy (estilo Hanna-Barbera) ====
    if idx == 4:  # gruñido - ojos enfocados
        # Ojo principal
        d.ellipse([64, 30, 76, 42], fill=(252, 252, 255), outline=(0, 0, 0), width=2)
        d.ellipse([69, 33, 75, 41], fill=(15, 15, 25))
        d.ellipse([71, 34, 73, 36], fill=(255, 255, 255))
        # Ceja enojada
        d.polygon([(62, 26), (78, 30), (76, 32), (62, 30)],
                  fill=(60, 30, 10))
    else:
        # Ojo droopy (mitad cerrado)
        d.chord([64, 32, 76, 44], start=180, end=360,
                fill=(252, 252, 255), outline=(0, 0, 0), width=2)
        d.line([(64, 38), (76, 38)], fill=(0, 0, 0), width=2)
        # Pupila en la parte de abajo
        d.ellipse([68, 36, 74, 42], fill=(15, 15, 25))

    # ==== Boca ====
    if idx == 4:  # gruñido - boca abierta con dientes
        d.chord([62, 56, 82, 70], start=20, end=160, fill=(60, 20, 10),
                outline=(40, 15, 5), width=1)
        # Dientes
        d.polygon([(66, 58), (68, 64), (70, 58)], fill=(245, 245, 240))
        d.polygon([(72, 58), (74, 64), (76, 58)], fill=(245, 245, 240))
        d.polygon([(78, 58), (80, 64), (82, 58)], fill=(245, 245, 240))
    else:
        # Sonrisita simple
        d.arc([64, 56, 80, 66], start=10, end=170, fill=(60, 30, 10), width=2)

    # ==== Collar rojo ====
    # Forma curvada del collar
    d.polygon([(48, 60), (68, 56), (68, 66), (48, 70)],
              fill=(200, 30, 30), outline=(120, 15, 15), width=2)
    # Placa dorada
    d.ellipse([55, 60, 63, 68], fill=(220, 200, 50), outline=(140, 110, 20))

    # ==== Cola (corta) ====
    if idx in (0, 4):
        d.polygon([(14, 50), (4, 46), (10, 58)],
                  fill=(155, 105, 60), outline=(70, 40, 15), width=2)
    elif idx in (1, 3):
        # Cola levantada (corriendo)
        d.polygon([(14, 46), (6, 38), (12, 54)],
                  fill=(155, 105, 60), outline=(70, 40, 15), width=2)
    elif idx == 2:
        d.polygon([(14, 50), (4, 52), (10, 60)],
                  fill=(155, 105, 60), outline=(70, 40, 15), width=2)

    # ==== Patas (varian con el frame) ====
    # 4 patas: 2 delanteras (mas atras en x), 2 traseras (mas adelante)
    # Pero en vista lateral solo se ven 2 (1 delantera + 1 trasera)
    if idx == 0:
        # Parado
        d.rectangle([54, 76, 64, 92], fill=(125, 80, 40), outline=(60, 30, 10))
        d.rectangle([18, 76, 28, 92], fill=(125, 80, 40), outline=(60, 30, 10))
        # Patas: dedos
        d.ellipse([52, 88, 66, 94], fill=(125, 80, 40), outline=(60, 30, 10))
        d.ellipse([16, 88, 30, 94], fill=(125, 80, 40), outline=(60, 30, 10))
    elif idx == 1:
        # Patas adelantadas (corriendo)
        d.polygon([(56, 76), (66, 70), (72, 84), (60, 86)],
                  fill=(125, 80, 40), outline=(60, 30, 10), width=2)
        d.polygon([(14, 78), (24, 76), (22, 90), (12, 92)],
                  fill=(125, 80, 40), outline=(60, 30, 10), width=2)
    elif idx == 2:
        # Patas medias
        d.rectangle([56, 74, 66, 90], fill=(125, 80, 40), outline=(60, 30, 10))
        d.rectangle([18, 78, 28, 92], fill=(125, 80, 40), outline=(60, 30, 10))
    elif idx == 3:
        # Patas atrasadas (corriendo)
        d.polygon([(50, 76), (58, 80), (64, 92), (54, 92)],
                  fill=(125, 80, 40), outline=(60, 30, 10), width=2)
        d.polygon([(24, 76), (32, 76), (30, 90), (20, 88)],
                  fill=(125, 80, 40), outline=(60, 30, 10), width=2)
    elif idx == 4:
        # Gruñido - parado agachado
        d.rectangle([52, 78, 64, 92], fill=(125, 80, 40), outline=(60, 30, 10))
        d.rectangle([16, 78, 28, 92], fill=(125, 80, 40), outline=(60, 30, 10))

    return img


# ============================================================================
# PEZ DORADO (4 frames de aleteo)
# ============================================================================

def pescado_frame(idx):
    img = Image.new("RGBA", (SIZE, SIZE), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)

    # Sombra debajo
    d.ellipse([26, 82, 70, 90], fill=(0, 0, 0, 60))

    # ==== Cuerpo dorado (forma de gota) ====
    # Forma principal: usar polygon para curva mas suave
    body_pts = []
    cx, cy = 42, 50
    for angle in range(0, 360, 15):
        rad = math.radians(angle)
        # Mas ancho horizontalmente
        if 80 <= angle <= 100:  # arriba un poco aplastado
            r = 22
        elif 260 <= angle <= 280:  # abajo redondo
            r = 24
        else:
            r = 26 if angle < 180 else 24
        x = cx + r * math.cos(rad)
        y = cy + r * math.sin(rad) * 0.78  # aplastar verticalmente
        body_pts.append((x, y))
    d.polygon(body_pts, fill=(255, 200, 50), outline=(180, 110, 10), width=2)

    # ==== Vientre claro (zona de abajo) ====
    belly_pts = []
    for angle in range(180, 361, 15):
        rad = math.radians(angle)
        r = 18
        x = cx + r * math.cos(rad)
        y = cy + 4 + r * math.sin(rad) * 0.65
        belly_pts.append((x, y))
    d.polygon(belly_pts, fill=(255, 235, 130))

    # ==== Brillo dorado (reflejo) ====
    d.ellipse([18, 36, 32, 46], fill=(255, 245, 200))

    # ==== Branquia (linea curva) ====
    d.arc([24, 40, 38, 62], start=300, end=60, fill=(180, 110, 10), width=2)

    # ==== Cola (varia por frame) ====
    if idx == 0:
        # Cola recta horizontal
        d.polygon([(66, 50), (92, 36), (88, 50), (92, 64)],
                  fill=(255, 175, 30), outline=(180, 100, 10), width=2)
        d.line([(72, 44), (88, 40)], fill=(220, 130, 20), width=1)
        d.line([(72, 56), (88, 60)], fill=(220, 130, 20), width=1)
    elif idx == 1:
        # Cola hacia arriba
        d.polygon([(66, 50), (88, 28), (84, 44), (92, 56)],
                  fill=(255, 175, 30), outline=(180, 100, 10), width=2)
        d.line([(72, 44), (82, 32)], fill=(220, 130, 20), width=1)
    elif idx == 2:
        # Cola estirada
        d.polygon([(66, 50), (94, 38), (94, 62), (66, 54)],
                  fill=(255, 175, 30), outline=(180, 100, 10), width=2)
        d.line([(72, 44), (90, 42)], fill=(220, 130, 20), width=1)
        d.line([(72, 56), (90, 58)], fill=(220, 130, 20), width=1)
    elif idx == 3:
        # Cola hacia abajo
        d.polygon([(66, 50), (92, 72), (84, 56), (88, 44)],
                  fill=(255, 175, 30), outline=(180, 100, 10), width=2)
        d.line([(72, 56), (82, 68)], fill=(220, 130, 20), width=1)

    # ==== Aleta dorsal ====
    d.polygon([(28, 30), (40, 18), (52, 30)],
              fill=(255, 175, 30), outline=(180, 100, 10), width=2)
    d.line([(40, 18), (42, 28)], fill=(180, 100, 10), width=1)

    # ==== Aleta inferior ====
    d.polygon([(34, 72), (44, 82), (52, 72)],
              fill=(255, 175, 30), outline=(180, 100, 10), width=2)

    # ==== Aleta lateral (pectoral) ====
    d.ellipse([28, 54, 42, 64], fill=(255, 200, 50), outline=(180, 100, 10), width=1)

    # ==== Ojo GRANDE ====
    d.ellipse([16, 38, 30, 52], fill=(252, 252, 255), outline=(0, 0, 0), width=2)
    # Pupila (mira segun el frame)
    if idx % 2 == 0:
        d.ellipse([20, 42, 28, 50], fill=(15, 15, 25))
        d.ellipse([22, 43, 25, 46], fill=(255, 255, 255))
    else:
        d.ellipse([19, 42, 27, 50], fill=(15, 15, 25))
        d.ellipse([21, 43, 24, 46], fill=(255, 255, 255))

    # ==== Sonrisa ====
    d.arc([14, 48, 28, 60], start=10, end=80, fill=(180, 80, 10), width=2)

    # ==== Burbujas decorativas ====
    if idx in (0, 2):
        d.ellipse([76, 12, 84, 20], outline=(150, 200, 230), width=2)
        d.ellipse([78, 14, 80, 16], fill=(200, 230, 240))
    if idx in (1, 3):
        d.ellipse([82, 4, 88, 10], outline=(150, 200, 230), width=2)

    return img


# ============================================================================
# Crear las 3 hojas y guardarlas
# ============================================================================

def main():
    # Chilly: 6 frames (idle, walk1, walk2, lanzando, barrer1, barrer2)
    sheet = Image.new("RGBA", (SIZE * 6, SIZE), (0, 0, 0, 0))
    for i in range(6):
        sheet.paste(chilly_frame(i), (i * SIZE, 0), chilly_frame(i))
    sheet.save(os.path.join(OUT_DIR, "chilly_sheet.png"))
    print("Chilly OK")
    chilly_frame(0).save(os.path.join(OUT_DIR, "chilly.png"))

    # Smedley: 5 frames
    sheet = Image.new("RGBA", (SIZE * 5, SIZE), (0, 0, 0, 0))
    for i in range(5):
        sheet.paste(smedley_frame(i), (i * SIZE, 0), smedley_frame(i))
    sheet.save(os.path.join(OUT_DIR, "smedley_sheet.png"))
    print("Smedley OK")
    smedley_frame(0).save(os.path.join(OUT_DIR, "smedley.png"))

    # Pez: 4 frames
    sheet = Image.new("RGBA", (SIZE * 4, SIZE), (0, 0, 0, 0))
    for i in range(4):
        sheet.paste(pescado_frame(i), (i * SIZE, 0), pescado_frame(i))
    sheet.save(os.path.join(OUT_DIR, "pescado_sheet.png"))
    print("Pez OK")
    pescado_frame(0).save(os.path.join(OUT_DIR, "pescado.png"))


if __name__ == "__main__":
    main()
