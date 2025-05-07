def Alimentar(mascota):
    print(f"Alimentando a {mascota['name']}...")
    mascota["state"]["hambriento"] = max(mascota["state"].get("hambriento", 0) - 1, 0)
    print(f"Estado de {mascota['name']} después de alimentar: {mascota['state']}")

def Jugar(mascota):
    print(f"Jugando con {mascota['name']}...")
    mascota["state"]["feliz"] = mascota["state"].get("feliz", 0) + 1
    print(f"Estado de {mascota['name']} después de jugar: {mascota['state']}")

def Dormir(mascota):
    print(f"Haciendo dormir a {mascota['name']}...")
    mascota["state"]["sueño"] = max(mascota["state"].get("sueño", 0) - 1, 0)
    print(f"Estado de {mascota['name']} después de dormir: {mascota['state']}")