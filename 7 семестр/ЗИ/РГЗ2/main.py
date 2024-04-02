import networkx as nx
import matplotlib.pyplot as plt
import math
import random

def extgcd(a: int, b: int) -> tuple:
    if a <= 0 or b <= 0:
        raise ValueError("Числа могут быть только натуральными")
    # if a < b:
    #     a, b = b, a  # Ломает алгоритм
    u1, u2, u3 = a, 1, 0
    v1, v2, v3 = b, 0, 1
    while v1:
        q = u1 // v1
        t1, t2, t3 = u1 % v1, u2 - q * v2, u3 - q * v3
        u1, u2, u3 = v1, v2, v3
        v1, v2, v3 = t1, t2, t3
    return u1, u2, u3


def gen_mutually_prime(a):
    while True:
        b = random.randrange(2, a)
        if math.gcd(a, b) == 1:
            return b


def is_prime(n, trials=8):
    """
    Miller-Rabin primality test.

    A return value of False means n is certainly not prime. A return value of
    True means n is very likely a prime.
    """
    if n != int(n):
        return False
    n = int(n)
    # Miller-Rabin test for prime
    if n == 0 or n == 1 or n == 4 or n == 6 or n == 8 or n == 9:
        return False

    if n == 2 or n == 3 or n == 5 or n == 7:
        return True
    6
    s = 0
    d = n - 1
    while d % 2 == 0:
        d >>= 1
        s += 1
    assert (2 ** s * d == n - 1)

    def trial_composite(a):
        if pow(a, d, n) == 1:
            return False
        for i in range(s):
            if pow(a, 2 ** i * d, n) == n - 1:
                return False
        return True

    for i in range(trials):  # number of trials
        a = random.randrange(2, n)
        if trial_composite(a):
            return False

    return True


def generate_prime(a: int, b: int):
    number = 0
    while not is_prime(number):
        number = random.randint(a, b)
    return number


########## Создание графа ##########
def create_graph(n, m):
    edges = []
    colors = ('R', 'B', 'Y')
    vertex_colors = {}

    if m == n:
        count = 0
        for i in range(n):
            v1 = i + 1
            v2 = (i + 1) % n + 1
            color = colors[count % len(colors)]
            count += 1
            edges.append((v1, v2))
            if v1 not in vertex_colors:
                vertex_colors[v1] = color
            if v2 not in vertex_colors:
                color = colors[count % len(colors)]
                vertex_colors[v2] = color
    elif m > n:
        count = 0
        existing_edges = set()
        for i in range(n):
            v1 = i + 1
            v2 = (i + 1) % n + 1
            color = colors[count % len(colors)]
            count += 1
            edges.append((v1, v2))
            if v1 not in vertex_colors:
                vertex_colors[v1] = color
            if v2 not in vertex_colors:
                color = colors[count % len(colors)]
                vertex_colors[v2] = color
            existing_edges.add((v1, v2))

        remaining_edges = m - n
        for i in range(remaining_edges):
            v1, v2 = find_unused_vertices(existing_edges, n)
            color = colors[count % len(colors) % m]
            count += 1
            edges.append((v1, v2))
            if v1 not in vertex_colors:
                vertex_colors[v1] = color
            if v2 not in vertex_colors:
                color = colors[count % len(colors)]
                vertex_colors[v2] = color
            existing_edges.add((v1, v2))
    else:  # если m < n
        count = 0
        for i in range(m):
            v1 = i + 1
            v2 = (i + 1) % n + 1
            color = colors[count % len(colors)]
            count += 1
            edges.append((v1, v2))
            if v1 not in vertex_colors:
                vertex_colors[v1] = color
            if v2 not in vertex_colors:
                color = colors[count % len(colors)]
                vertex_colors[v2] = color
    print(edges)
    print(vertex_colors)
    return edges, vertex_colors

def find_unused_vertices(existing_edges, n):
    for v1 in range(1, n):
        for v2 in range(v1+1, n):  # избегаем дублирования и ребер вида (1,1)
            if (v1, v2) not in existing_edges and (v2, v1) not in existing_edges:
                return v1, v2
    return 1, 2

########## Запись в файл ##########
def write_to_file(filename, edges, vertex_colors, n, m):
    with open(filename, 'w') as file:
        file.write(f"{n} {m}\n")
        for edge in edges:
            file.write(f"{edge[0]}, {edge[1]}\n")

        file.write("Vertex Colors:\n")
        for vertex, color in vertex_colors.items():
            file.write(f"{vertex}: {color}\n")

def _graph():
    with open('input.txt') as f:
        lines = f.readlines()

    n, m = lines[0].split(' ')

    n = int(n)
    m = int(m)

    edges_from_file = lines[1:m+1]
    edges = {'start': [], 'end': []}
    for edge in edges_from_file:
        x, y = edge.split(' ')
        edges['start'].append(int(x))
        edges['end'].append(int(y))
    colors_from_file = lines[-1].split(' ')
    vertex_colors = {}
    for i in range(len(colors_from_file)):
        vertex_colors[i+1] = colors_from_file[i].strip()
    return edges, vertex_colors, n

########## Перемешивание цветов ##########
def shuffle_clr(colors):

    print(f'Исходная последовательность цветов: {colors}')

    name_color = ['R', 'B', 'Y']
    shift = random.randint(1, 3)
    shuffled_name_color = name_color.copy()
    shuffled_name_color = shuffled_name_color[shift:] + shuffled_name_color[:shift]

    shuffled_colors = {}
    for vertex, color in colors.items():
        color_index = name_color.index(color)
        shuffled_color = shuffled_name_color[color_index]
        shuffled_colors[vertex] = shuffled_color

    print(f'Граф после перемешивания: {shuffled_colors}')
    return shuffled_colors

########## Отрисовка графа ##########
def draw_graph(edge_data, vertex_colors):
    G = nx.Graph()

    for start, end in zip(edge_data['start'], edge_data['end']):
        G.add_edge(start, end)

    pos = nx.circular_layout(G)

    node_colors = [vertex_colors[vertex] for vertex in G.nodes]
    numerical_node_colors = [color_map[color] for color in node_colors]

    nx.draw(G, pos, with_labels=True, node_color=numerical_node_colors, font_weight='bold', node_size=700, edge_color='black')
    plt.show()

color_map = {'R': 'red', 'B': 'blue', 'Y': 'yellow'}

def main():
    edge_data, shuffled_colors, num_vertices = _graph()
    shuffled_colors = shuffle_clr(shuffled_colors)

    r_v, P, Q, N, Phi, D, C, Z = [],[],[],[],[],[],[],[]

    for i in shuffled_colors.values():
        r_ = random.randint(0, 2**32)

        binary_number = bin(r_)[2:].zfill(32)

        if i == 'R':
            binary_number = binary_number[:-2] + '00'
        elif i == 'B':
            binary_number = binary_number[:-2] + '01'
        elif i == 'Y':
            binary_number = binary_number[:-2] + '10'

        updated_number = int(binary_number, 2)
        r_v.append(updated_number)
 
    for _ in range(num_vertices):
        P.append(generate_prime(10**5, 10 ** 9))
        Q.append(generate_prime(10**5, 10 ** 9))

    for i in range(num_vertices):
        N.append(P[i] * Q[i])
        Phi.append((P[i] - 1) * (Q[i] - 1))
        D.append(gen_mutually_prime(Phi[i]))
        c_temp = extgcd(D[i], Phi[i])[1]
        if c_temp < 0:
            c_temp += Phi[i]
        C.append(c_temp)
        Z.append(pow(r_v[i], D[i], N[i]))
    print(Z)
    i = 1
    for start, end in zip(edge_data['start'], edge_data['end']):
        start_index, end_index = start - 1, end - 1
        Z_1 = pow(Z[start_index], C[start_index], N[start_index])
        Z_2 = pow(Z[end_index], C[end_index], N[end_index])

        # print(bin(Z_1), bin(Z_2))

        if bin(Z_1)[-2:] == bin(Z_2)[-2:]:
            print(f'Ребро {i} имеет вершины {start},{end} с одинаковыми цветами и младшими битами:')
            print(f'Цвет вершины: {start_index + 1} Z_1: {bin(Z_1)},')
            print(f'Цвет вершины: {end_index + 1} Z_2: {bin(Z_2)}')
        else:
            print(f'Ребро {i} имеет вершины {start},{end} разных цветов и разные два младших бита')
        i += 1
    #draw_graph(graph, colors)
    draw_graph(edge_data, shuffled_colors)

if __name__ == '__main__':
    main()
