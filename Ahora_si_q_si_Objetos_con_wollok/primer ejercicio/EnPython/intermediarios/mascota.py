from .ObjetosPeroSinClases import ComportamientosMascota as ComporMascota
def AlimentarMascota(atributos: dict):
    """
    Alimenta a la mascota y actualiza su estado.
    """
    return ComporMascota.Alimentar(atributos)

def JugarConMascota(atributos: dict):
    """
    Juega con la mascota y actualiza su estado.
    """
    return ComporMascota.Jugar(atributos)

def DormirMascota(atributos: dict):
    """
    Hace que la mascota duerma y actualiza su estado.
    """
    return ComporMascota.Dormir(atributos)
def crearMascota(owner,name:str, animal:str) -> dict:
    
    from .user import CrearNuevoUsuario
    if not animal == "" and not name == "":
        return {
            "name": name,
            "animal": animal,
            "tricks": [],
            "owner": owner,
            "state": {
                "feliz": 0,
                "triste": 0,
                "hambriento": 0,
                "sueño": 0
            }
}
    else:
        
        return {
            "animal": input("What pet do you like to have? <turtle,dog,cat>").lower(),
            "name": input("The pet is still waiting its name, what is?"),
            "tricks": [],
            "owner":  CrearNuevoUsuario()
            }



"""
pet:dict = Mascota({
                "name" : nombreMascota,
                "trick" : [],
                "owner" : Owner({}),
                "state" : Estado({})
            })
        
"""