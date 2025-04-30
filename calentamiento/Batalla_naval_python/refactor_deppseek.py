def dimensiones(x: int, y: int) -> tuple:
    return (x, y)

def grilla(dimensiones: tuple) -> list:
    return [[0 for _ in range(dimensiones[0])] for _ in range(dimensiones[1])]

def colocar_objeto(grilla: list, coord: list, c=1) -> list:
    new_grid = [fila[:]  for fila in grilla]
    print("Esta es la grilla creaada en colocar: {}".format(new_grid))
    x, y = coord[0], coord[1]

    for _ in range(c):
        try:
            if verif_celdas(grid=grilla, obj_coords=(x, y)) and vlid_coord(coord, grilla):
                new_grid[y][x] = 1
            return new_grid
        except:
            raise "Error"

def verif_celdas(obj_coords: tuple, grid: list, is_valid=True) -> bool:
    cont = 0
    for y in range(obj_coords[1] - 1, obj_coords[1] + 1):
        for x in range(obj_coords[0] - 1, obj_coords[0] + 1):
            current_coord = grid[y][x]
            #print(f"La pieza actual es: {current_coord}, Y ésto sale en verif: {grid[y][x]} en las coordenadas: {(x, y)}")
            
            is_valid = celda_vacia(current_coord=current_coord, is_valid=is_valid)
            if not is_valid:
                cont += 1
            if cont > 1:
                return is_valid
    #print(f"Esto va a devolver verif: {is_valid}")
    return is_valid

def pedir_cantidad_objetos() -> int:
    return cantidad_objetos(c=int(input('Ingrese la cantidad de "Barcos" que usted desee:\t')))

def cantidad_objetos(c=1) -> int:
    return c

def celda_vacia(is_valid: bool, current_coord: int) -> tuple:
    #print(current_coord)
    if current_coord != 0 and current_coord is not None or current_coord == 2:
        is_valid = False
    current_coord = 2
    
    return is_valid

def graficar(grilla: list) -> None:
    for fila in grilla:
        print(fila)

def generar_coords(grid: list) -> tuple:
    from random import randint
    return (randint(0, len(grid[0]) - 1), (randint(0, len(grid) - 1)))

def vlid_coord(coords: tuple, grid: list) -> bool:
    if (coords[0] < 0 or coords[0] >= len(grid[0])) or (coords[1] < 0 or coords[1] >= len(grid)):
        return False
    #print(f"Las coordenadas {coords} son válidas")
    return True

def proc(coords: tuple, grid: list) -> None:
    graficar(grid)
    #print(f"El resultado de verif es:\t{verif_celdas(coords, grid)} con las coordenadas {coords}\n\n El resultado de valid es:{vlid_coord(coords, grid)} con las coordenadas {coords}")
    if verif_celdas(coords, grid) and vlid_coord(coords, grid):
        return colocar_objeto(grid, coords)
    

def main() -> None:
    cantidad = cantidad_objetos(c=int(input("Cuantos objetos quiere ingresar: ")))
    grid = grilla(dimensiones=dimensiones(int(input("X = ")), int(input("Y = "))))
    for _ in range(cantidad):
        coords = generar_coords(grid)
        proc(coords, grid)

if __name__ == "__main__":
    main()