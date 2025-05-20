def WhoState(key: str, estado: dict) -> int:
    """
    Devuelve el valor del atributo especificado en el estado.
    Si el atributo no existe, devuelve 0.
    """
    return estado.get(key, 0)

def ModifState(estado: dict, key: str, masMenos: int) -> dict:
    """
    Modifica el valor del atributo especificado en el estado.
    Si el atributo no existe, lo crea con el valor inicial proporcionado.
    """
    if key in estado:
        estado[key] += masMenos
    else:
        estado[key] = masMenos
    return estado

def MostrarEstado(estado: dict):
    """
    Muestra el estado actual de la mascota.
    """
    print("Estado actual de la mascota:")
    for key, value in estado.items():
        print(f"{key.capitalize()}: {value}")

