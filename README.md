# Lab4_QuadTrees

### En este lab se buscó hallar la relación de compresión entre el archivo .pgm y el archivo binario generado para guardar la imagen.

## Conversión de megabyte a byte
1 Megabyte = 1,048,576 bytes

### Bytes de las imágenes usadas para la relación:
* baboon.pgm -> 1,363,148.8 bytes
* dog.pgm -> 3,250,585.6 bytes
* dragon.pgm -> 3,565,158.4 bytes

### Bytes de las imágenes comprimidas:
* baboon_bin -> 5,198,580 bytes
* dog_bin -> 5,981,740 bytes
* dragon_bin -> 1,507,480 bytes

### Bytes de las imágenes reconstruidas:
* baboon_new.pgm -> 992,928 bytes
* dog_new.pgm -> 2,622,027 bytes
* dragon_new.pgm -> 3,329,336 bytes

## Relación entre el archivo original .pgm y el archivo binario
$$ \frac{sin comprimir}{comprimido} $$
$$\frac{1363148.8}{54522595.2} = 0.025$$
$$\frac{3250585.6}{6291456} = 0.52$$
$$\frac{3565158.4}{1572864} = 2.27$$
\
$$\frac{0.025 + 0.52 + 2.27}{3} = 0.938$$

## Resultados
A partir de los cálculos se puede observar que la diferencia entre una imagen sin comprimir y comprimida es mínima, es decir, la cantidad de bytes en ambos casos es casi equivalente, pues su relación es casi de 1:1.
