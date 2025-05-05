"""
mascota:
    nombre:str,
    trucos:int | str,
    dueño & estado: function (dict),
    {
    feliz:bool | int
    triste: bool | int
    hambriento: bool | int
    } <- podemos llevar a cabo los comportamientos.
"""
def Mascota(atributos:dict)-> dict:
    import ComportamientosMascota as mthMascota


def Estado(atributos:dict)-> dict:
    import ComportamientosClaseEstado as mthEstado

def Mascota(atributos:dict)-> dict:
    import ComportamientosUser as mthUser
