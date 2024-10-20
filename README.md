
# Tarea N1 Sistemas Operativos 

Se solicita simular una carrera de autos utilizando programaci´on multihebras. Cada autom´ovil competidor correr´a en una hebra distinta. La carrera consiste en que cada auto
recorrer´a una distancia de M metros en intervalos de tiempo aleatorios.

## Compilar el programa

- Instalar g++ en el equipo (Debian)
```bash
  sudo apt install g++
```
- Ejecutar el archivo MakeFile

```bash
  make
```

## Ejecutar el programa

Orden de parametros del codigo 
```bash
./CarreradeBuses <Distancia_de_la_carrera> <Cantidad_de_autos> <Modo_de_la_carrera>
````
- Distancia_de_la_carrera = Distancia que deberan recorrer los autos para termianr la carrera
- Cantidad_de_autos = Cantidad de autos que participaran en la carrera
- Modo_de_la_carrera = Modo en el que se ejecutara la carrera 

  (0) Modo Normal: Cumple con los requisitos establecidos en la rúbrica de evaluación del profesor, el cual hace que el nombre de los autos sean (Auto0, Auto1, etc).

  (1) Modo Personalizado: Ejecuta la carrera en un modo personalizado, el cual hace que el nombre de los autos sean nombres de autos reales, hasta una variedad de 50 autos, esta version no cumple con los requisitos de la rúbrica.

## Hecho por

- [@BenjahYKP](https://github.com/BenjahYKP)
- [@Nicoflenn](https://github.com/Nicoflenn)

