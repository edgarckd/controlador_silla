import sympy as sp
import numpy as np

def obtener_serie_taylor(funcion, punto, orden):
    #global x
    x = sp.symbols('x')
    serie_taylor = sp.series(funcion, x, x0=punto, n=orden).removeO()
    return str(serie_taylor)

# Definir la función original
x = np.arange(0,100,1000)
f = sp.sin(x)

# Punto de expansión
punto_expansion = 0

# Orden de la serie de Taylor
orden_serie = 5

# Obtener la serie de Taylor
serie_taylor = obtener_serie_taylor(f, punto_expansion, orden_serie)

print('Serie de Taylor:')
print(serie_taylor)
