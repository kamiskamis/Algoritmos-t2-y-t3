import os
import random
import string

def generar_matriz_insertar():
    # Crear una matriz 1x26 llena de números aleatorios entre 1 y 10
    return [[random.randint(1, 10) for j in range(26)]]

def generar_matriz_eliminar():
    # Crear una matriz 26x1 llena de números aleatorios entre 1 y 10
    return [[random.randint(1, 10)] for i in range(26)]

def generar_matriz_sustituir():
    # Crear una matriz 26x26 llena de números aleatorios entre 1 y 10
    matriz = [[random.randint(1, 10) for j in range(26)] for i in range(26)]
    # Poner los valores de la diagonal principal a 0
    for i in range(26):
        matriz[i][i] = 0
    return matriz

def generar_matriz_transponer():
    # Crear una matriz 26x26 llena de números aleatorios entre 1 y 10
    matriz = [[random.randint(1, 10) for j in range(26)] for i in range(26)]
    # Poner los valores de la diagonal principal a 0
    for i in range(26):
        matriz[i][i] = 0
    return matriz

def guardar_matriz_en_archivo(nombre_archivo, matriz, carpeta='matrices_costos'):
    # Asegurarse de que la carpeta exista
    if not os.path.exists(carpeta):
        os.makedirs(carpeta)

    # Guardar el archivo en la carpeta especificada
    ruta_archivo = os.path.join(carpeta, nombre_archivo)
    with open(ruta_archivo, 'w') as f:
        for fila in matriz:
            f.write(' '.join(map(str, fila)) + '\n')

# Generar las matrices
matriz_insertar = generar_matriz_insertar()
matriz_eliminar = generar_matriz_eliminar()
matriz_sustituir = generar_matriz_sustituir()
matriz_transponer = generar_matriz_transponer()

# Guardar las matrices en la carpeta matrices_costos
guardar_matriz_en_archivo('cost_insert.txt', matriz_insertar)
guardar_matriz_en_archivo('cost_delete.txt', matriz_eliminar)
guardar_matriz_en_archivo('cost_replace.txt', matriz_sustituir)
guardar_matriz_en_archivo('cost_transpose.txt', matriz_transponer)

print("Archivos generados con éxito en la carpeta 'matrices_costos'.")


import string

def limpiar_cadena(cadena):
    # Eliminar saltos de línea y retorno de carro
    cadena = cadena.replace('\r', '').replace('\n', '')
    cadena = ''.join(filter(lambda ch: ch in string.printable, cadena))
    cadena = cadena.strip()
    return cadena




# Función para generar una cadena aleatoria de una longitud específica
def generar_cadena(longitud):
    return ''.join(random.choices(string.ascii_lowercase, k=longitud))

# Función para generar un caso de prueba aleatorio
def generar_casos_prueba():
    # Generar longitudes aleatorias para las cadenas
    longitud_1 = random.randint(3, 10)  # Longitud de la primera cadena entre 3 y 10
    longitud_2 = random.randint(3, 10)  # Longitud de la segunda cadena entre 3 y 10
    
    # Generar dos cadenas aleatorias
    s1 = generar_cadena(longitud_1)
    limpiar_cadena(s1)
    s2 = generar_cadena(longitud_2)
    limpiar_cadena(s2)
    
    # Abrir el archivo para escribir el caso
    with open("caso_prueba.txt", "w") as file:
        file.write(f"{s1}\n{s2}\n")
    
    print("Archivo 'caso_prueba.txt' generado con un solo caso.")

# Llamar a la función para generar el caso y guardarlo en un archivo
generar_casos_prueba()