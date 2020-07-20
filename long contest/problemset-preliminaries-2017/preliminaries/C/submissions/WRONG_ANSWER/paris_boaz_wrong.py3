# *** This variant of the solution solves the variant of creating a maximum capacity path and removing all adjacent edges not part of that path ***
# *** This solution produces the wrong output, as it won't remove any duplicate edges from the result ***

import sys
import code
from collections import deque
# gc "..\testcases\sample-testcases.in" | python .\paris_boaz.py
# gc = Get-Content / cat / type
# gc ..\testcases\big_random.in | python .\paris_boaz.py | Out-File ..\testcases\big_random.out
# Optionally, add -Encoding utf8 to Out-File as the default encoding is not really ideal for many uses.
MIN_EDGES = 1
MIN_VERTEX_ID = 0
MAX_EDGES = 1000
MAX_VERTEX_ID = 1001
MIN_C = 1
MAX_C = 500000
instr = sys.stdin
case_number = 0

class graph:
    def __init__(self):
        self.edges = []
        self.vertices = []
    
    def __init__(self, vertices, edges):
        self.vertices = vertices
        self.edges = edges
    
    def __str__(self):
        result = ""
        result += "Vertices:\n"
        for v in self.vertices:
            result += "\t" + str(v) + "\n"
        result += "Edges:\n"
        for e in self.edges:
            result += "\t" + str(e) + "\n"
        return result

    def __repr__(self):
        return self.__str__()

class vertex:
    def __init__(self, id):
        self.id = id
        self.edges = []
        self.parent = None
        self.parent_edge = None

    def __str__(self):
        return "(" + str(self.id) + ")"

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other):
        return (isinstance(other, self.__class__) and self.id == other.id)

    def __ne__(self, other):
        return not self.__eq__(other)
        
    def __hash__(self):
        return self.id

class edge:
    def __init__(self, id, v1, v2, c):
        self.id = id
        self.v1 = v1
        self.v2 = v2
        self.c = c
        
    def connected(self, vertex):
        return self.v1.id == vertex.id or self.v2.id == vertex.id
        
    def __str__(self):
        return "[{self.v1} -> {self.v2}]({self.id}; {self.c})"

    def __repr__(self):
        return self.__str__()
        
    def __eq__(self, other):
        return (isinstance(other, self.__class__) and self.__dict__ == other.__dict__)

    def __ne__(self, other):
        return not self.__eq__(other)
        
    def __hash__(self):
        return self.v1.id + self.v2.id * 2000

def solve(verbose = False):
    while True:
        global case_number
        case_number += 1
        
        g = read_graph()
        if g is None: return
        if verbose:
            print("Case: {}".format(case_number)) 
            print(g)
        
        input_check_connected(g)
        input_check_duplicate_edges(g)
        tree, edges_in_tree = max_spanning_tree(g)
        breadth_first(tree, edges_in_tree)
        print_result(tree)

def print_result(gr, verbose = False):
    destination = len(gr.vertices) - 1
    result = []
    if verbose: print("Reversed path: ", end="")

    v_current = gr.vertices[destination]
    v_previous = v_current
    while True:
        if verbose: print("{v_current} ", end="")
        for e in v_current.edges:
            if ((v_current.parent and e != v_current.parent_edge) or not v_current.parent) and e != v_previous.parent_edge:
                result.append(e)
                if verbose: print("This edge WILL be removed: {e}")
            elif verbose: print("This edge won't be removed: {e}")
        if v_current.parent == None: break
        v_previous = v_current
        v_current = v_current.parent
    if verbose: print("Done")

    if len(result) == 0: print("none")
    else:
        result = sorted(result, key = lambda e: e.id)
        if verbose: print("Edges to remove: ", end="")
        first = True
        for e in result:
            if first:
                first = False
            else:
                print(" ", end="")
            print(e.id, end="")
        print("")

def breadth_first(gr, edges_in_tree, verbose = False):
    destination = len(gr.vertices) - 1

    queue = deque()
    queue.append(gr.vertices[0])
    v_current = gr.vertices[0]
    v_current.parent = None

    while v_current != gr.vertices[destination]:
        v_current = queue.popleft()
        if verbose: print("Current vertex to search: {v_current}")
        for e in v_current.edges:
            if e not in edges_in_tree: continue
            if e.v1.id != v_current.id and not e.v1 == gr.vertices[0] and (not e.v1.parent):
                queue.append(e.v1)
                e.v1.parent = v_current
                e.v1.parent_edge = e
            elif (not e.v2.parent) and not e.v2 == gr.vertices[0]:
                queue.append(e.v2)
                e.v2.parent = v_current
                e.v2.parent_edge = e
  
def max_spanning_tree(gr, verbose = True):
    # 1. Initialize a tree with a single vertex, chosen arbitrarily from the graph.
    # 2. Grow the tree by one edge: of the edges that connect the tree to vertices not yet in the tree, find the minimum-weight edge, and transfer it to the tree.
    # 3. Repeat step 2 (until all vertices are in the tree).
    gr.vertices = sorted(gr.vertices, key=lambda x: x.id)
    vertices_in_tree = set([gr.vertices[0]])
    edges_in_tree = set([])
    
    while gr.vertices[len(gr.vertices) - 1] not in vertices_in_tree:
        max_weigth = 0
        max_weight_edge = None
        v_to_add = 0
        for v in vertices_in_tree:
            for e in v.edges:
                if e.v1 not in vertices_in_tree:
                    if e.c > max_weigth:
                        max_weight_edge = e
                        max_weigth = e.c
                        v_to_add = e.v1
                if e.v2 not in vertices_in_tree:
                    if e.c > max_weigth:
                        max_weight_edge = e
                        max_weigth = e.c
                        v_to_add = e.v2
                
        edges_in_tree.add(max_weight_edge)
        vertices_in_tree.add(v_to_add)

    result = graph(gr.vertices, edges_in_tree)
    return result, edges_in_tree
        
def read_graph(verbose = False):
    input = instr.readline()
    if not input: return None
    inputs = input.split(' ')
    
    try:
        n = int(inputs[0])
        m = int(inputs[1])
    except ValueError:
        raise Exception("Expected integer while reading number of streets")
        
    if m < MIN_EDGES or m > MAX_EDGES:
        raise Exception("Input value [n] is out of range: {}".format(m))
    
    edges = []
    vertices = []
    edgeset = set([])
    verticeset = set([])
    for i in range(0, m):
        input = instr.readline()
        inputs = input.split(' ')
        n_s1 = int(inputs[0])
        n_s2 = int(inputs[1])
        n_c = int(inputs[2])
        
        assert n_s1 >= MIN_VERTEX_ID and n_s1 < n
        assert n_s2 >= MIN_VERTEX_ID and n_s2 < n
        assert n_s1 != n_s2
        assert n_c >= MIN_C and n_c <= MAX_C

        v1 = vertex(n_s1)
        v2 = vertex(n_s2)
        if v1 not in verticeset:
            vertices.append(v1)
            verticeset.add(v1)
        else: v1 = vertices[vertices.index(v1)]
        if v2 not in verticeset:
            vertices.append(v2)
            verticeset.add(v2)
        else: v2 = vertices[vertices.index(v2)]
        
        # Make sure that n_s1 < n_s2 so as to make the merging of edges easier
        if v1.id > v2.id:
            v1,v2 = v2,v1 # Swap
        
        e = edge(i, v1, v2, n_c)
        assert e not in edgeset
        edges.append(e)
        edgeset.add(e)
        v1.edges.append(e)
        v2.edges.append(e)
        
    return graph(vertices, edges)

def input_check_duplicate_edges(gr, verbose = False):
    parsed_edges = set()
    for e in gr.edges:
        if e.__hash__() in parsed_edges:
            print("Assertion will fail: {e}")
        assert e.__hash__() not in parsed_edges
        parsed_edges.add(e.__hash__())

def input_check_connected(gr, verbose = False):
    to_search = set([gr.vertices[0]])
    visited = set()

    while len(to_search) > 0:
        v = to_search.pop()
        if verbose: print(v)

        visited.add(v)

        for e in v.edges:
            start = e.v1
            end = e.v2
            if (e.v1 != v and e.v1 not in visited):
                if e.v1 not in to_search:
                    to_search.add(e.v1)
            if (e.v2 != v and e.v2 not in visited):
                if e.v2 not in to_search:
                    to_search.add(e.v2)

    assert len(visited) == len(gr.vertices)

def main():
    solve()

if __name__ == "__main__":
    main()
