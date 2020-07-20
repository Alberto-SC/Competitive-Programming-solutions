vector<iii> out; // The minimum spanning tree
void kruskal(){ // pick smallest edges that both vertex weren't picked
	for(int i = 0; i < n_vertices; i++) make_set(i);
	sort(graph.bg(), graph.nd()); // ii(peso, ii(u, v))
	for(int i = 0; i < graph.size(); i++)
		if(find(graph[i].ss.ff) != find(graph[i].ss.ss)) {
			joint(graph[i].ss.ff, graph[i].ss.ss);
			out.pb(graph[i]);
		}
}
