
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

