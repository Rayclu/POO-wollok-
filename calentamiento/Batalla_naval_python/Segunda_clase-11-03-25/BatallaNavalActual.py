BARCOS = [
    (1, [(0, 0)]),  # Barco de tamaño 1
    (2, [(0, 0), (0, 1)]),  # Barco de tamaño 2 con rotación horizontal
    (3, [(0, 0), (0, 1), (0, 2)]),  # Barco de tamaño 3 con rotación horizontal
    (4, [(0, 0), (0, 1), (0, 2), (0, 3)])  # Barco de tamaño 4 con rotación horizontal
]

def dimensiones(x: int, y: int) -> tuple:
    return (x, y)


def grilla(dimensiones: tuple) -> list:
    return [[0 for _ in range(dimensiones[0])] for _ in range(dimensiones[1])]

def colocar_objeto(grilla: list, coord: list, c=1) -> list:
    new_grid = [fila[:] for fila in grilla]
    y, x = coord[0], coord[1]


    for _ in range(c):
        try:
            if verif_celdas(grid=grilla, obj_coords=(y, x)):
                new_grid[y][x] = 1
            return new_grid
        except:
            raise "Error"

def verif_celdas(obj_coords: tuple, grid: list, is_valid=True) -> bool:
    lenx = len(grid[0])
    leny = len(grid)
    ly = max(obj_coords[0] - 1, 0)
    lx = max(obj_coords[1] - 1, 0)
    by = min(obj_coords[0] + 1, leny)
    bx = min(obj_coords[1] + 1, lenx)
    is_valid = True
    for y in range(ly, min(leny, by+1)):
        for x in range(lx, min(lenx, bx+1)):
            current_coord = grid[y][x]
            is_valid = celda_vacia(current_coord)
            if is_valid==False:
                break
        if is_valid==False:
            break
    return is_valid


def pedir_cantidad_objetos() -> int:
    return cantidad_objetos(c=int(input('Ingrese la cantidad de "Barcos" que usted desee:\t')))


def cantidad_objetos(c=1) -> int:
    return c


def celda_vacia(current_coord: int):
    if current_coord != 0:
        return False
    return True


def graficar(grilla: list) -> None:
    for fila in grilla:
        print(fila, "\n")


def generar_coords(grid: list) -> tuple:
    from random import randint
    return (randint(0, len(grid[0]) - 1), (randint(0, len(grid) - 1)))


def put_in_grill_process(coords: tuple, grid: list) -> list:
    if verif_celdas(coords, grid):
        return colocar_objeto(grid, coords)
    else:
        return grid    

def are_cell_empty(aim:int)->bool:
        return aim == 1

def disparo(coord_apuntada:tuple, grid:list)->list:
    x,y,= coord_apuntada[1], coord_apuntada[0] 
    aiming = grid[y][x]
    is_a_boat = are_cell_empty(aiming)

    if is_a_boat:
        # 
        # **is_a_boat refiere a una variable del tipo booleano que indica
        # **al resto del programa si se ha acertado el disparo(si le pegó a un barco)
        # #
        grid[y][x] = 2
        return [grid, is_a_boat] #Este 'return' indica que se ACERTÓ el dísparo.(True)
    return [grid, is_a_boat] #Este otro 'return' indica que NO se acertó.(False)


def intelligence(coords:tuple, grid:list, UsedCoords = [])->list:
    if not UsedCoords: 
        #
        # **Si UsedCoords no tiene coordenadas guardadas, 
        # **el programa disparará automaticamente
        # #
        UsedCoords.append(coords)
        return disparo(coord_apuntada=coords, grid=grid)
    
    if disparo(coord_apuntada=coords, grid=grid)[1]:
        #
        # El barco tiene qe hundirse.#
        grid[coords[1]][coords[0]] = 2
        return grid

    #
    # El barco no debe hundirse.#    
    new_grid = grid[:]
    
    if not coords in UsedCoords:
        UsedCoords.append(coords)
        new_grid, collapse = disparo(coord_apuntada=coords, grid=new_grid)
        if collapse[1] is True:
            new_grid = collapse[0]
            return [new_grid, True]
    elif coords in UsedCoords:
        pass
    else:
        raise "Error"
    
def aiming(grid:list)->tuple:
    from random import randint
    return (randint(0, len(grid) -1), randint(0, len(grid[0]) - 1))

def shooting_process(grid: list, aiming_coords: tuple, used_coords : list)->None:
            res_shoot = disparo(coord_apuntada=aiming_coords, grid= grid)
            #
            #   ***********************************************************
            #   * Disparo puede devolver un Array dos valores distintos   *
            #   *         de los cuales uno puede variar                  *
            #   *     1er elem: Grilla Actualizada. |(elemento fijo)      *
            #   *     2do elem -> Puede variar.                           *
            #   *                     |->primer posibilidad: Agua(False)  * 
            #   *                     |_>Segunda posibilidad: Barco(True) *    
            #   ***********************************************************
            ##
            if res_shoot is False: 
              used_coords[0].append(aiming_coords)
            elif res_shoot is True:
                used_coords[1].append(aiming_coords)


def main() -> None:
    objs = input("Cuantos objetos quiere ingresar: ")
    cantidad = cantidad_objetos(c=int(objs))
    ix = input("X = ")
    iy = input("Y = ")
    grid = grilla(dimensiones=dimensiones(int(iy), int(ix)))

    for _ in range(cantidad):
        
        coords = aiming(grid)
        grid = put_in_grill_process(coords, grid)
        
    used_coords = [[], []] 
    #               |   |_> That elem contains a correct coords.
    #               |_> That elem containt the incorrect coords.

    for attemps in range(0, 10): # Ciclo 'cerrado' en e que se gneran 11 intentos
        aiming_coords = aiming(grid)# Obtengo coordenadas al 'azar' con el formato (y, x)

        if not aiming_coords in used_coords[0] and not aiming_coords in used_coords[1]:    
            #Si las coordenadas generadas no estan usadas se dispara con las coords generadas originalmente
            shooting_process(grid=grid, aiming_coords=aiming_coords, used_coords=used_coords)
        else:
            #Caso contrario se generarán otras coords
            shooting_process(grid=grid, aiming_coords=aiming(grid), used_coords=used_coords)
    print(graficar(grid))
  
    

main()