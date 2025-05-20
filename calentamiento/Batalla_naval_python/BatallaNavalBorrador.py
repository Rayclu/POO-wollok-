BARCOS = {
    1: [(0, 0)],  # Barco de tamaño 1
    2: [(0, 0), (0, 1)],  # Barco de tamaño 2 con rotación horizontal
    3: [(0, 0), (0, 1), (0, 2)],  # Barco de tamaño 3 con rotación horizontal
    4: [(0, 0), (0, 1), (0, 2), (0, 3)]  # Barco de tamaño 4 con rotación horizontal
}

def dimensiones(x: int, y: int) -> tuple:
    return (x, y)


def grilla(dimensiones: tuple) -> list:
    return [[0 for _ in range(dimensiones[0])] for _ in range(dimensiones[1])]

def colocar_objeto(grilla: list, coord: list, boat=[], c=1) -> list:
    new_grid = [fila[:] for fila in grilla]
    y, x = coord[0], coord[1]
    leny, lenx = len(grilla), len(grilla[0])

    for dy, dx in boat:
        try:
            new_y, new_x = y + dy, x + dx
            if 0 <= new_y < leny and 0 <= new_x < lenx and verif_celdas(grid=grilla, obj_coords=(new_y, new_x)):
                new_grid[new_y][new_x] = 1
        except:
            raise "Error"
    return new_grid

def verif_celdas(obj_coords: tuple, grid: list, is_valid=True, boat=[]) -> bool:
                        
    lenx = len(grid[0])
    leny = len(grid)

    ly = max(obj_coords[0] - 1, 0)
    lx = max(obj_coords[1] - 1, 0)
    by = min(obj_coords[0] + 1, leny)
    bx = min(obj_coords[1] + 1, lenx)

    is_valid = True

    for y in range(ly, min(leny, by+1)):
        for x in range(lx, min(lenx, bx+1)):
            
            # Se pasa una tupla con los índices de la celda
            is_valid = celda_vacia((y, x), boat, grid)
            if not is_valid:
                break
        if not is_valid:
            break
    return is_valid


def pedir_cantidad_objetos() -> int:
    return cantidad_objetos(c=int(input('Ingrese la cantidad de "Barcos" que usted desee:\t')))


def cantidad_objetos(c=1) -> int:
    return c


def celda_vacia(coord: tuple, boat: list, grid: list) -> bool:
    y, x = coord
    # Se verifica que la celda esté vacía (0) y opcionalmente que no forme parte del barco (boat)
    if grid[y][x] != 0 and coord not in boat:  #<-- Si se quiere tener en cuenta lo de boat, quitar el comentario
        return False
    return True


def graficar(grilla: list) -> None:
    for fila in grilla:
        print(fila, "\n")


def generar_coords(grid: list) -> tuple:
    from random import randint
    return (randint(0, len(grid[0]) - 1), (randint(0, len(grid) - 1)))


def put_in_grill_process(coords: tuple, grid: list, boat = []) -> list:
        print("This is the values of boat \t{}".format(boat))

  #  try:
        if verif_celdas(coords, grid, boat=boat):
            return colocar_objeto(grid, coords, boat)#, c=len(boat) )
        else:
            return grid    
   # except:

def are_cell_empty(aim:int)->bool:
        if aim == 1:
            aim = 2 
        return aim

def disparo(coord_apuntada:tuple, grid:list)->list:
    x,y,= coord_apuntada[1], coord_apuntada[0] 
    aiming = grid[y][x]
    is_a_boat = are_cell_empty(aiming) == 2 if True else False

    if is_a_boat:
        # 
        # **is_a_boat refiere a una variable del tipo booleano que indica
        # **al resto del programa si se ha acertado el disparo(si le pegó a un barco)
        # #
        grid[y][x] = 2
        return [grid, is_a_boat] #Este 'return' indica que se ACERTÓ el dísparo.(True)
    return [grid, is_a_boat] #Este otro 'return' indica que NO se acertó.(False)


"""def intelligence(coords:tuple, grid:list, UsedCoords = [])->list:
    if not UsedCoords: 
        #
        # **Si UsedCoords no tiene coordenadas guardadas, 
        # **el programa disparará automaticamente
        # #
        UsedCoords.append(coords)
        print("Acá en inte")
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
   """ 
def aiming(grid:list)->tuple:
    from random import randint
    return (randint(0, len(grid) -1), randint(0, len(grid[0]) - 1))

def shooting_process(grid: list, aiming_coords: tuple, used_coords : list)->None:
            
            print(aiming_coords)
            res_shoot = disparo(coord_apuntada=aiming_coords, grid= grid)
            #
            #   ***********************************************************
            #   * Disparo puede devolver un Array dos valores distintos   *
            #   *         de los cuales uno puede variar                  *
            #   *     1er elem: Grilla Actualizada. |(elemento fijo)      *
            #   *     2do elem -> Puede variar.                           *
            #   *                     |->primer posibilidad: Agua(False)  * 
            #   *                     |->Segunda posibilidad: Barco(True) *    
            #   ***********************************************************
            ##
            if res_shoot is False: 
              used_coords[0].append(aiming_coords)
            elif res_shoot is True:
                used_coords[1].append(aiming_coords)

def breaking_the_habit(types_boats_count: dict, breaker = False)-> bool:
    count_of_boats_downed = 0
    for types in range(1, len(types_boats_count)):
        if types_boats_count.get(types, None) == 0:
            count_of_boats_downed += 1
    if count_of_boats_downed == len(types_boats_count):
        breaker  = True
        return breaker
    return breaker

def get_coords_based(grid: tuple, bsed_coords: list)-> tuple:
    from random import randint
    boats = bsed_coords[1]
    water = bsed_coords[0]


    branch_of_BsedCoords = randint(0, 1)
    match branch_of_BsedCoords:
        case 1:
            for boats_kicked in boats:
                lenx = len(grid[0])
                leny = len(grid)
                ly = max(boats_kicked[0] - 1, 0) # limit of y (corner sup. left)
                lx = max(boats_kicked[1] - 1, 0) # limit of x (corner sup. right)
                by = min(boats_kicked[0] + 1, leny) # limit inf of y (corner inf. left)
                bx = min(boats_kicked[1] + 1, lenx) # limit inf of x (corner inf right)
                for y in range(ly, min(leny, by+1)):
                    for x in range(lx, min(lenx, bx+1)):
                        if (x == lx and y == ly) or (x == min(len(lenx, bx+1)) and y == min(len(lenx, by+1))):
                            continue

                        #if 

                        
                        
            
    
        case _:
            for water_cell in water:
                lenx = len(grid[0])
                leny = len(grid)

                ly = max(water_cell[0] - 1, 0)
                lx = max(water_cell[1] - 1, 0)
                by = min(water_cell[0] + 1, leny)
                bx = min(water_cell[1] + 1, lenx)

            pass
def main() -> None:
    from random import randint
    #objs = input("Cuantos objetos quiere ingresar: ")
   # cantidad = cantidad_objetos(c=int(objs))
    ix = input("X = ")
    iy = input("Y = ")
    grid = grilla(dimensiones=dimensiones(int(iy), int(ix)))
    
    numbers_of_types_boats = {
        1: 1,  # Barco de tamaño 1
        2: 1,  # Barco de tamaño 2 con rotación horizontal
        3: 1,  # Barco de tamaño 3 con rotación horizontal
        4: 1  #
    }

    for _ in range(len(numbers_of_types_boats)):
        key:int = randint(1, len(BARCOS))
        type_of_boat = BARCOS.get(key)
        all_placed = False

        while not all_placed:
            coords = aiming(grid)
            new_grid = put_in_grill_process(coords, grid, type_of_boat)
            if new_grid != grid:  # Si la grilla ha cambiado, el barco se colocó
                grid = new_grid
                all_placed = True

    used_coords = [[], []] 
    #               |   |_> That elem contains a correct coords.
    #               |_> That elem containt the incorrect coords.
    attemps = 0
    need_to_break = False
    while not need_to_break:
        attemps+=1
        if breaking_the_habit(numbers_of_types_boats):
            print(attemps)
            break
        else:
            coords = aiming(grid) if (len(used_coords[0]) == 0) and (len(used_coords[1]) == 0)  else get_coords_based(grid, used_coords)
            print("De acá se envia el puto booleano de mierda{}".format(coords))
            shooting_process(grid=grid, aiming_coords=coords, used_coords=used_coords)
            
    print(graficar(grid))

main()