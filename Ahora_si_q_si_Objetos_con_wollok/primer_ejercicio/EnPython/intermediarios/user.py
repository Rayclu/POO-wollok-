from .ObjetosPeroSinClases import ComportamientosUser as ComporUser

def CrearNuevoUsuario(nombre: str) -> dict:
    """
    Crea un nuevo usuario con el nombre proporcionado.
    """
    #print("Pero antes debe de iniciar sesión, Ingrese su nombre: \t")
    #input()
    print("Iniciando sesión... \n")

    return ComporUser.CrearUsuario(nombre)

def AñadirMascotaAUsuario(usuario: dict, mascota: dict):
    """
    Añade una mascota al usuario.
    """
    ComporUser.AgregarMascota(usuario, mascota)

def VerUsuario(usuario: dict):
    """
    Muestra la información del usuario.
    """
    ComporUser.MostrarUsuario(usuario)