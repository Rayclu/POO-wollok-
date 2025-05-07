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

def Mascota(atributos: dict) -> dict:
    import ObjetosPeroSinClases.mascota.ComportamientosMascota as mthMascota
    usr_want = input("Do you want to [eat/play/nothing]? ").lower()
    match usr_want:
        case "eat":
            mthMascota.Alimentar(atributos)
        case "play":
            mthMascota.Jugar(atributos)
        case "nothing":
            mthMascota.Dormir(atributos)
        case _:
            print("Invalid option.")
    return atributos

def Estado(atributos:dict)-> dict:
    import ObjetosPeroSinClases.estado as mthEstado

def Owner(atributos:dict)-> dict:
    import ObjetosPeroSinClases.user as mthUser

def main():
    while(True):
        nombreMascota:str
        if not(nombreMascota):
          # nombreMascota = input("")
           nombre = input("The pet is still waiting its name, what is that?")
        else:
            pass
        pet:dict = Mascota({
                "name" : nombre,
                "trick" : [],
                "owner" : Owner({}),
                "state" : Estado({})
            })
        
        
        if(input("Do you want to exit?, if the answer is yes write <exit> else write another one string pls").lower() == "exit"):
            break
main()