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

def CrearUsuario(nombre: str, mascotas = []) -> dict:
    """
    Crea un usuario con el nombre proporcionado.
    """
    import sqlite3 as sq
    conn = sq.connect("Mascotas.db")
    cur = conn.cursor()

    cur.execute("""
    CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT, 
    name TEXT UNIQUE  
    )
    """
    )

    cur.execute("""
    CREATE TABLE IF NOT EXISTS mascotas ( 
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    type TEXT, 
    name TEXT, 
    owner INTEGER,
    FOREIGN KEY(owner) REFERENCES users(id) 
    )
    """
    )

    cur.execute("SELECT name FROM users WHERE name = ?",(nombre,))
    usr_exists = cur.fetchall()
    print(usr_exists)
    if not nombre in usr_exists:
        cur.execute("INSERT INTO users (name) VALUES (?)", (nombre,))
    
    conn.commit()
    conn.close()
    
    return {"name": nombre, "mascotas": mascotas}

def AgregarMascota(usuario: dict, mascota: dict):
    """
    Agrega una mascota al usuario y la guarda en la base de datos.
    """
    import sqlite3 as sq
    conn = sq.connect("Mascotas.db")
    cur = conn.cursor()

    # Obtener el ID del usuario
    cur.execute("SELECT id FROM users WHERE name = ?", (usuario["name"],))
    user_id = cur.fetchone()
    if user_id:
        user_id = user_id[0]
        cur.execute("INSERT INTO mascotas (type, name, owner) VALUES (?, ?, ?)", (
            mascota["type"],
              mascota["name"],
                user_id
                )
            )
        usuario["mascotas"].append(mascota)
        print(f"{mascota['name']} ha sido agregado a las mascotas de {usuario['name']}.")
    else:
        raise ValueError(f"Usuario {usuario['name']} no encontrado.")
    
    conn.commit()
    conn.close()

def MostrarUsuario(usuario: dict):
    """
    Muestra la información del usuario y sus mascotas desde la base de datos.
    """
    import sqlite3 as sq
    conn = sq.connect("Mascotas.db")
    cur = conn.cursor()

    print(f"Usuario: {usuario['name']}")
    print("Mascotas:")

    # Obtener el ID del usuario
    cur.execute("SELECT id FROM users WHERE name = ?", (usuario["name"],))
    user_id = cur.fetchone()
    if user_id:
        user_id = user_id[0]
        cur.execute("SELECT name, type FROM mascotas WHERE owner = ?", (user_id,))
        mascotas = cur.fetchall()
        for mascota in mascotas:
            print(f"- {mascota[1]}: {mascota[0]}")
    else:
        print("No se encontraron mascotas para este usuario.")
        raise ValueError()
    
    conn.close()