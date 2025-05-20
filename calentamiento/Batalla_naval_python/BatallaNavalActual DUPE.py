from random import randint
BARCOS = {
    1: [[(0, 0)]],  # Barco de tamaño 1
    2: [ [(0, 0), (0, 1)], [(0,0), (1,0)] ],  # Barco de tamaño 2 con rotación horizontal
    3: [[(0, 0), (0, 1), (0, 2)], [(0,0),(1,0),(2,0),(3,0)]],  # Barco de tamaño 3 con rotación horizontal
    4: [[(0, 0), (0, 1), (0, 2), (0, 3)], [(0, 0), (1, 0), (2, 0), (3, 0)]]  # Barco de tamaño 4 con rotación horizontal
}

def dimensiones_grilla(x: int, y: int) -> tuple:
    return (x, y)


def grilla(dimensiones_grilla: tuple) -> list:
    return [[0 for _ in range(dimensiones_grilla[0])] for _ in range(dimensiones_grilla[1])]

def colocar_objeto(grilla: list, coord: list, boat=[], c=1) -> list:
    new_grid = [fila[:] for fila in grilla]
    y, x = coord[0], coord[1]
    leny, lenx = len(grilla), len(grilla[0])

    for dy, dx in boat:
        try:
            new_y, new_x = y + dy, x + dx
            if 0 <= new_y < leny and 0 <= new_x < lenx and verificar_alrededores(grid=grilla, obj_coords=(new_y, new_x)):
                new_grid[new_y][new_x] = 1
        except:
            raise "Error"
    return new_grid
def limites(boat:tuple, len_x:int, len_y:int)->int:
    print("A limites llega:\t",boat)
    SupY = max(boat[0] - 1, 0) # limit of y (corner sup. left)
    Left = max(boat[1] - 1, 0) # limit of x (corner sup. right)
    InfY = min(boat[0] + 1, len_y) # limit inf of y (corner inf. left)
    Right = min(boat[1] + 1, len_x) # limit inf of x (corner inf right)

    return SupY, InfY, Left, Right

def verificar_alrededores(obj_coords: tuple, grid: list, is_valid=True, boat=[]) -> bool:
                        
    lenx = len(grid[0])-1
    leny = len(grid)-1

    lims = limites(obj_coords, lenx, leny)
    
    ly = lims[0]
    by = lims[1]
    lx = lims[2]
    bx = lims[3]
    is_valid = True

    for y in range(ly, min(leny, by+1)):
        for x in range(lx, min(lenx, bx+1)):
            
            # Se pasa una tupla con los índices de la celda
            is_valid = celda_grilla_vacia((y, x), boat, grid)
            if not is_valid:
                break
        if not is_valid:
            break
    return is_valid


def pedir_la_cantidad_objetos_usuario() -> int:
    return cantidad_objetos(c=int(input('Ingrese la cantidad de "Barcos" que usted desee:\t')))


def cantidad_objetos(c=1) -> int:
    return c


def celda_grilla_vacia(coord: tuple, boat: list, grid: list) -> bool:
    y, x = coord
    # Se verifica que la celda esté vacía (0) y opcionalmente que no forme parte del barco (boat)
    if grid[y][x] != 0 and coord not in boat:
        return False
    return True


def graficar_grilla(grilla: list) -> None:
    for fila in grilla:
        print(fila, "\n")


def generacion_coordenadas_disparo(grid: list) -> tuple:
    return (randint(0, len(grid[0]) - 1), randint(0, len(grid) - 1))


def puesta_de_barcos_en_grilla(coords: tuple, grid: list, boat = []) -> list:
  #  print("This is the values of boat \t{}".format(boat))
    if verificar_alrededores(coords, grid, boat=boat):
        return colocar_objeto(grid, coords, boat)#, c=len(boat) )
    else:
        return grid    

def pregunta_celdas_vacias(aim:int)->bool:
        return aim == 1

def disparo(coord_apuntada:tuple, grid:list)->list:
    print("El NoneType en cuestion:\t{}".format(coord_apuntada))
    try:
        x,y,= coord_apuntada[1], coord_apuntada[0] 
    except TypeError:
        
        x,y = generacion_coordenadas_disparo(grid) 
    aiming = grid[y][x]
    is_a_boat = pregunta_celdas_vacias(aiming)

    if is_a_boat:
        # 
        # **is_a_boat refiere a una variable del tipo booleano que indica
        # **al resto del programa si se ha acertado el disparo(si le pegó a un barco)
        # #
        grid[y][x] = 2
        return [grid, is_a_boat] #Este 'return' indica que se ACERTÓ el dísparo.(True)
    return [grid, is_a_boat] #Este otro 'return' indica que NO se acertó.(False)
    

def proceso_de_disparo(grid: list, aiming_coords: tuple, used_coords : list)->None:
            print("El 'NoneType' en shooting_proc:\t{}".format(aiming_coords))
            if aiming_coords in used_coords:
                raise ValueError
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
            if res_shoot[1] is False: 
                used_coords[0].append(aiming_coords)
            elif res_shoot[1] is True:
                used_coords[1].append(aiming_coords)
            
            return res_shoot, used_coords

def cuestionamiento_barcos_bajados(types_boats_count: dict, breaker = False)-> bool:
    count_of_boats_downed = 0
    for types in range(1, len(types_boats_count)):
        if types_boats_count.get(types, None) == 0:
            count_of_boats_downed += 1
    if count_of_boats_downed == len(types_boats_count):
        breaker  = True
        return breaker
    return breaker

def coordenadas_basadas_en_coordenadas_previas(grid: tuple, bsed_coords: list)-> tuple:
   # print(bsed_coords)
    print("The father var of water:", bsed_coords)
    boats = bsed_coords[1]
    water = bsed_coords[0]
    lenx = len(grid[0])-1
    leny = len(grid)-1
    branch_of_BsedCoords = randint(0, 1)
    match branch_of_BsedCoords:
        
        case 1:
            for boats_kicked in boats:

                lim_sup_y, lim_inf_y, lim_left_x, lim_right_x = limites(boats_kicked, lenx, leny)
                for y in range(lim_sup_y, lim_inf_y):
                    for x in range(lim_left_x, lim_right_x):
                        if (x == lim_left_x and y == lim_sup_y) or (x == lim_right_x and y == lim_inf_y):
                            continue
                        elif (x == lim_left_x and y == lim_inf_y) or (x == lim_right_x and y == lim_inf_y):
                            continue
                        elif grid[y][x] == 2 or (y,x) == boats_kicked:
                            continue
                        if grid[y][x] == 1:
                            return y,x
                bsed_coords[1].pop(0)
                return coordenadas_basadas_en_coordenadas_previas(grid, bsed_coords)
                        
        case _:
            print("This is water", water)
            for water_cell in water:
                lim_sup_y, lim_inf_y, lim_left_x, lim_right_x = limites(water_cell, lenx, leny)  
                for y in range(lim_sup_y, lim_inf_y):
                    for x in range(lim_left_x, lim_right_x):
                        if (y,x)==water_cell:
                            continue
                        else:
                            if grid[y][x] == 1:
                                return y,x
            return generacion_coordenadas_disparo(grid)
            
def main() -> None:
    ix = input("X = ")
    iy = input("Y = ")
    grid = grilla(dimensiones_grilla=dimensiones_grilla(int(iy), int(ix)))
    
    numbers_of_types_boats = {
        1: 1,  # Barco de tamaño 1
        2: 1,  # Barco de tamaño 2 con rotación horizontal
        3: 1,  # Barco de tamaño 3 con rotación horizontal
        4: 1  #
    }

    for _ in range(len(numbers_of_types_boats)):
        key:int = randint(1, len(BARCOS))
        type_of_boat = BARCOS.get(key)[randint(0, len(BARCOS[key])-1)]
        all_placed = False

        while not all_placed:
            coords = generacion_coordenadas_disparo(grid)
            new_grid = puesta_de_barcos_en_grilla(coords, grid, type_of_boat)
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
        print("Numb of attemps: ", attemps)
        if cuestionamiento_barcos_bajados(numbers_of_types_boats):
            print("Num of attemps:\t",attemps)
            break
        else:
            print("+++++++++++++++++++++++++++++++++++++++++++++++++++++++")
            print("|    Así está el diccionario con los barcos tirados:  |")
            print("|        -El barco de una coord:{}                    |".format(numbers_of_types_boats[1]))
            print("|        -El barco de dos coord:{}                    |".format(numbers_of_types_boats[2]))
            print("|        -El barco de tres coord:{}                   |".format(numbers_of_types_boats[3]))
            print("|        -El barco de cuatro coord:{}                 |".format(numbers_of_types_boats[4]))
            print("+++++++++++++++++++++++++++++++++++++++++++++++++++++++")
            coords =  generacion_coordenadas_disparo(grid) if (len(used_coords[0]) == 0) and (len(used_coords[1]) == 0) else coordenadas_basadas_en_coordenadas_previas(grid, used_coords)
            try:
                print("generó error en el try")
                proceso_de_disparo(grid=grid, aiming_coords=coords, used_coords=used_coords)
                for state in used_coords:
                    for i in range(len(state)):
                        if state[i] is None:
                            print("Se encontro un None.")
                            state.pop(i)
                graficar_grilla(new_grid)               
            except:
                print("generó error la excepcion")
                proceso_de_disparo(grid, coordenadas_basadas_en_coordenadas_previas(grid, [used_coords[i] for i in range(0, len(used_coords))]), used_coords)
                
    

main()
