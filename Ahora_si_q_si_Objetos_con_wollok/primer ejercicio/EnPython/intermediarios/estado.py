from .ObjetosPeroSinClases import ComportamientosClaseEstado as ComporState
def CrearEstado() -> dict:
    """
    Crea un estado inicial para la mascota.
    """
    return {
        "feliz": 0,
        "triste": 0,
        "hambriento": 0,
        "sueño": 0
    }

def ActualizarEstado(estado: dict, key: str, valor: int):
    """
    Actualiza un atributo específico del estado.
    """
    ComporState.ModifState(estado, key, valor)

def VerEstado(estado: dict):
    """
    Muestra el estado actual de la mascota.
    """
    ComporState.MostrarEstado(estado)