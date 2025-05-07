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
    import mascota.ComportamientosMascota as mthMascota


def Estado(atributos:dict)-> dict:
    import estado.ComportamientosClaseEstado as mthEstado

def Mascota(atributos:dict)-> dict:
    import user.ComportamientosUser as mthUser
