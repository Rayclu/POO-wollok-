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
    usr_want = atributos["dueño"[input("Do you want to...")]]
    match usr_want:
        case "comer":
            mthMascota.Alimentar(atributos)
        case "jugar":
            mthMascota.Jugar(atributos)
            pass
        case _:
            mthMascota.Dormir(atributos)
            pass
    
def Estado(atributos:dict)-> dict:
    import ComportamientosClaseEstado as mthEstado

def Owner(atributos:dict)-> dict:
    import ComportamientosUser as mthUser

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