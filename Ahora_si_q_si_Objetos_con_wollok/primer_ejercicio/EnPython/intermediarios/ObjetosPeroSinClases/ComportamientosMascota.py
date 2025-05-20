def Alimentar(atributos: dict):
    estado = atributos.get("state", {})
    estado["hambriento"] = max(estado.get("hambriento", 0) - 1, 0)
    print(f"{atributos['name']} ha sido alimentado. Hambre actual: {estado['hambriento']}")

def Jugar(atributos: dict):
    estado = atributos.get("state", {})
    estado["feliz"] = estado.get("feliz", 0) + 1
    estado["hambriento"] = estado.get("hambriento", 0) + 1
    print(f"{atributos['name']} ha jugado. Felicidad: {estado['feliz']}, Hambre: {estado['hambriento']}")

def Dormir(atributos: dict):
    estado = atributos.get("state", {})
    estado["sueño"] = max(estado.get("sueño", 0) - 1, 0)
    print(f"{atributos['name']} ha dormido. Sueño actual: {estado['sueño']}")