def dobles(numero):
    numero *= 2
    return numero
def cuadruples(numero):
    numero*=4
    return numero
def main():
    numero = int(input("Ingrese un número:\n"))
    Doble = dobles(numero)
    Cuadruple = cuadruples(numero)
    print("Estos son los resultados:\n"
    "Doble:{}".format(Doble), "\t", "Cuadruple:{}".format(Cuadruple))
main()