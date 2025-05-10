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
    import intermediarios.mascota as mthMascota
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
    import intermediarios.estado as mthEstado

def Owner(atributos:dict)-> dict:
    import intermediarios.user as mthUser

def main():
    import intermediarios.user as usr
    import intermediarios.mascota as mascota
    import intermediarios.estado as state

    while(True):
        user = usr.CrearNuevoUsuario(input("Enter your name: "))
        pet = mascota.crearMascota(user, input("Enter the name of your pet: "), input("Enter the type of pet: "))
        print(pet)
        if(input("Do you want to exit?, if the answer is yes write <exit>:\n\t").lower() == "exit"):
            break
main()