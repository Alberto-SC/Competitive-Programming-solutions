import java.io.*;
import java.util.*;
import java.math.*;

public class Paris {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	public Paris() {}

	public static void main(String[] args) throws Exception {
		new Paris().doProblem();
	}

	public static void out(Object o, boolean newline) {
		if (newline) System.out.println(o.toString());
		else System.out.print(o.toString());
		System.out.flush();
	}

	public static void out(Object o) {
		out(o, true);
	}

	public void doProblem() throws Exception {
		solve();
	}

	public void solve() throws Exception {
		graph g = read_graph();
		if (g == null) return;
        graph tree = this.max_spanning_tree(g);
        this.breadth_first(tree);
        print_result(tree);
	}

    public void print_result(graph g) {
        int destination = g.vertices.size() - 1;
        
        ArrayList<edge> result = new ArrayList<edge>();
        HashMap<Integer, edge> resultmap = new HashMap<Integer, edge>();
        vertex v_current = g.vertices.get(destination);
        vertex v_previous = v_current;

        while (true) {
            for (edge e : v_current.edges) {
                if (((v_current.parent != null && e.id != v_current.parent_edge.id) || v_current.parent == null) && e.id != v_previous.parent_edge.id && !resultmap.containsKey(e.id)) {
                    result.add(e);
                    resultmap.put(e.id, e);
                }
            }
            if (v_current.parent == null) break;
            v_previous = v_current;
            v_current = v_current.parent;
        }

        if (result.size() == 0) {
            out("none");
            return;
        }
        Collections.sort(result, new Comparator<edge>() {
            public int compare(edge e1, edge e2) {
                return new Integer(e1.id).compareTo(new Integer(e2.id));
            }
        });

        boolean first = true; 
        for (edge e : result) {
            if (first) {
                out(e.id, false);
                first = false;
            }
            else out(" " + e.id, false);
        } 
        out("");
    }

    public void breadth_first(graph g) {
        int destination = g.vertices.size() - 1;

        ArrayDeque queue = new ArrayDeque<vertex>();
        HashMap<Integer, vertex> visited = new HashMap<Integer, vertex>();
        HashMap<Integer, vertex> queuemap = new HashMap<Integer, vertex>();
        queue.add(g.vertices.get(0));
        queuemap.put(g.vertices.get(0).id, g.vertices.get(0));

        vertex v_current = g.vertices.get(0);
        v_current.parent = null; 

        while (v_current.id != g.vertices.get(destination).id) {
            v_current = (vertex)queue.remove();
            visited.put(v_current.id, v_current);
            for (edge e : v_current.edges) {
                if (!g.edgemap.containsKey(e.id)) continue;
                if (e.v1.id != v_current.id && e.v1.id != g.vertices.get(0).id && e.v1.parent == null) {
                    if (!queuemap.containsKey(e.v1.id) && !visited.containsKey(e.v1.id)) {
                        queue.add(e.v1);
                        queuemap.put(e.v1.id, e.v1);
                        e.v1.parent = v_current;
                        e.v1.parent_edge = e;
                    }
                }
                if (e.v2.id != v_current.id && e.v2.id != g.vertices.get(0).id && e.v2.parent == null) {
                    if (!queuemap.containsKey(e.v2.id) && !visited.containsKey(e.v2.id)) {
                        queue.add(e.v2);
                        queuemap.put(e.v2.id, e.v2);
                        e.v2.parent = v_current;
                        e.v2.parent_edge = e;
                    }
                }
            }
        }
    }

    public graph max_spanning_tree(graph g) {
        Collections.sort(g.vertices, new Comparator<vertex>() {
            public int compare(vertex v1, vertex v2) {
                return new Integer(v1.id).compareTo(new Integer(v2.id));
            }
        });

        ArrayList<vertex> vertices = new ArrayList<vertex>();
        HashMap<Integer, vertex> vertices_in_tree = new HashMap<Integer, vertex>();
        HashMap<Integer, edge> edges_in_tree = new HashMap<Integer, edge>();

        vertices.add(g.vertices.get(0));
        vertices_in_tree.put(g.vertices.get(0).id, g.vertices.get(0)); 
        while (!vertices_in_tree.containsKey(g.vertices.get(g.vertices.size() - 1).id)) {
            int max_weigth = 0;
            edge max_weight_edge = null;
            vertex v_to_add = null;
            for (vertex v : vertices) {
                for (edge e : v.edges) {
                    if (!vertices_in_tree.containsKey(e.v1.id)) {
                        if (e.c > max_weigth) {
                            max_weight_edge = e;
                            max_weigth = e.c;
                            v_to_add = e.v1;
                        }
                    }
                    if (!vertices_in_tree.containsKey(e.v2.id)) {
                        if (e.c > max_weigth) {
                            max_weight_edge = e;
                            max_weigth = e.c;
                            v_to_add = e.v2;
                        }
                    }
                }
            }
            if (max_weight_edge != null) {
                edges_in_tree.put(max_weight_edge.id, max_weight_edge);
                vertices_in_tree.put(v_to_add.id, v_to_add);
                vertices.add(v_to_add);
            }
        }

        graph result = new graph();
        result.vertices = vertices;
        result.edgemap = edges_in_tree;

        return result;
    }

	public graph read_graph() throws Exception {
		graph gr = new graph();
		String input = in.readLine();

        String[] parts = input.split(" ");
		int n = Integer.parseInt(parts[0]);
        int m = Integer.parseInt(parts[1]);

		HashMap<Integer, vertex> vertexset = new HashMap<Integer, vertex>();
		for (int i = 0; i < m; i++) {
			input = in.readLine();
			String[] a_b_c = input.split(" ");
			int a = Integer.parseInt(a_b_c[0]);
			int b = Integer.parseInt(a_b_c[1]);
            int c = Integer.parseInt(a_b_c[2]);

            if (a > b) {
                int s = a;
                a = b;
                b = s;
            }

			vertex v1, v2;
			if (!vertexset.containsKey(a)) {
				v1 = new vertex(a);
				vertexset.put(a, v1);
				gr.vertices.add(v1);
                gr.vertexmap.put(v1.id, v1);
			}
			else v1 = vertexset.get(a);
			if (!vertexset.containsKey(b)) {
				v2 = new vertex(b);
				vertexset.put(b, v2);
				gr.vertices.add(v2);
                gr.vertexmap.put(v2.id, v2);
			}
			else v2 = vertexset.get(b);

			edge e = new edge(i, v1, v2, c);
			v1.edges.add(e);
			v2.edges.add(e);
			gr.edges.add(e);
            gr.edgemap.put(e.id, e);
		} 

		return gr;
	}

    public class graph {
        public ArrayList<edge> edges;
        public ArrayList<vertex> vertices;
        public HashMap<Integer, edge> edgemap;
        public HashMap<Integer, vertex> vertexmap;

        public graph() {
            this.vertices = new ArrayList<vertex>();
            this.edges = new ArrayList<edge>();
            this.edgemap = new HashMap<Integer, edge>();
            this.vertexmap = new HashMap<Integer, vertex>();
        }

		public String toString() {
			String result = "";
			for (edge e : this.edges) {
				result += e.toString();
				result += '\n';
			}
			return result;
		}
    }
    
    public class vertex {
        public int id;
        public ArrayList<edge> edges;
        public vertex parent;
        public edge parent_edge;

        public vertex(int id) {
            this.id = id;
            this.edges = new ArrayList<edge>();
            this.parent = null;
            this.parent_edge = null;
        }
        public boolean Equals(Object o) {
            vertex v = (vertex)o;
            return this.id == v.id;
        }
        public String toString() {
            return "(" + this.id + ")";
        }
        @Override
        public int hashCode() {
            return this.id;
        }
    }

    public class edge {
        public vertex v1, v2;
		public int id;
        public int c;
        public edge(int id, vertex v1, vertex v2, int c) {
            this.v1 = v1;
            this.v2 = v2;
			this.id = id;
            this.c = c;
        }
        public boolean connected(vertex v) {
            return this.v1.id == v.id || this.v2.id == v.id;
        }
        public String toString() {
            return "[" + this.v1.id + " -> " + this.v2.id + "](" + this.c + ")";
        }
        public boolean Equals(Object o) {
            edge e = (edge)o;
            return this.id == e.id;
        }
        @Override
        public int hashCode() {
			return id;
        }
    }
}
