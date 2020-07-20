/*
 * Solution for Paris.
 */

// @EXPECTED_RESULTS@: CORRECT

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static constexpr int MAXSTREET = 1000;
static constexpr int MAXNODE   = 1001;
static constexpr int MAXCAP    = 500000;

struct Street { int a, b, c; };

struct Graph {
    int maxnode;
    vector<Street> streets;
};

struct Path {
    vector<int> nodes;
};

// Check that graph does not contain multiple streets between nodes.
void check_no_multi_streets(const Graph& graph)
{
    set<pair<int,int>> got_street;

    for (const Street& st : graph.streets) {
        bool dupl_street = (got_street.count(make_pair(st.a, st.b)) > 0 ||
                            got_street.count(make_pair(st.b, st.a)) > 0);
        assert(!dupl_street);
        if (dupl_street) {
            exit(1);
        }
        got_street.insert(make_pair(st.a, st.b));
    }
}

// Find optimal path and check that graph is connected.
void find_path(const Graph& graph, vector<int> *path)
{
    vector<int> node_cap(graph.maxnode + 1);
    vector<int> node_street(graph.maxnode + 1);

    // Mark first node as reached.
    node_cap[0]    = MAXCAP + 1;
    node_street[0] = -1;

    // Discover more nodes.
    for (int i = 0; i < graph.maxnode; i++) {
        for (int s = 0, n = graph.streets.size(); s < n; s++) {
            int a = graph.streets[s].a;
            int b = graph.streets[s].b;
            int c = graph.streets[s].c;
            if (node_cap[a] > 0 &&
                node_cap[a] > node_cap[b] &&
                c > node_cap[b]) {
                node_cap[b] = min(node_cap[a], c);
                node_street[b] = s;
            }
            if (node_cap[b] > 0 &&
                node_cap[b] > node_cap[a] &&
                c > node_cap[a]) {
                node_cap[a] = min(node_cap[b], c);
                node_street[a] = s;
            }
        }
    }

    // Check that all nodes are reached.
    for (int p = 0; p <= graph.maxnode; p++) {
        bool node_reached = (node_cap[p] > 0);
        assert(node_reached);
        if (!node_reached) {
            exit(1);
        }
    }

    // Extract path from target to source.
    path->clear();
    for (int p = graph.maxnode; p != 0; ) {
        int s = node_street[p];
        path->push_back(s);
        if (graph.streets[s].a == p) {
            p = graph.streets[s].b;
        } else {
            p = graph.streets[s].a;
        }
    }

    // Reverse path to obtain path from source to target.
    reverse(path->begin(), path->end());
}


// Check that the max-cap path is unique.
void check_unique_path(const Graph& graph, const vector<int>& path)
{
    // Mark streets that are used in the path and determine path capacity.
    vector<bool> street_used(graph.streets.size());
    int pathcap = MAXCAP + 1;
    for (int s : path) {
        street_used[s] = true;
        pathcap = min(pathcap, graph.streets[s].c);
    }

    // Run shortest path algorithm from source to target, using only
    // streets with capacity at least pathcap, minimizing number of streets
    // that are on the path.
    vector<int> node_dist(graph.maxnode + 1);
    for (int p = 0; p <= graph.maxnode; p++) {
        node_dist[p] = MAXSTREET + 1;
    }

    node_dist[0] = 0;

    for (int i = 0; i < graph.maxnode; i++) {
        for (int s = 0, n = graph.streets.size(); s < n; s++) {
            if (graph.streets[s].c >= pathcap) {
                int a = graph.streets[s].a;
                int b = graph.streets[s].b;
                int d = street_used[s] ? 1 : 0;
                node_dist[a] = min(node_dist[a], node_dist[b] + d);
                node_dist[b] = min(node_dist[b], node_dist[a] + d);
            }
        }
    }

    // Any max-capacity path from source to target must use at least
    // all streets from the path. If the target can be reached while
    // not using some of the streets on path, that implies there exists
    // an alternative simple path with max-capacity.
    bool unique_path = ((unsigned int)node_dist[graph.maxnode] == path.size());
    assert(unique_path);
    if (!unique_path) {
        exit(1);
    }
}


// Determine list of streets to block.
void find_blocked_streets(const Graph& graph, const vector<int>& path,
                          vector<int> *blocked)
{
    // Mark nodes and streets on the path.
    vector<bool> node_used(graph.maxnode + 1);
    vector<bool> street_used(graph.streets.size());
    for (int s : path) {
        node_used[graph.streets[s].a] = true;
        node_used[graph.streets[s].b] = true;
        street_used[s] = true;
    }

    blocked->clear();

    // Consider each street. 
    for (int s = 0, n = graph.streets.size(); s < n; s++) {

        // Block the street if it is not on the path but at least
        // one of its endpoints is on the path.
        if ( (!street_used[s]) &&
             (node_used[graph.streets[s].a] ||
              node_used[graph.streets[s].b]) ) {
            blocked->push_back(s);
        }
    }
}

/* Main program. */
int main()
{
    // Read input.
    int n, m;
    scanf("%d %d", &n, &m);
    assert(m >= 1 && m <= MAXSTREET);
    assert(n >= 1 && n <= MAXNODE);

    Graph graph;
    graph.maxnode = n-1;

    set<int> nodeset;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        assert(a >= 0 && a < n);
        assert(b >= 0 && b < n);
        assert(a != b);
        assert(c >= 1 && c <= MAXCAP);
        graph.streets.push_back(Street{ a, b, c });
        nodeset.insert(a);
        nodeset.insert(b);
    }

    // Check that all nodes 0 .. n-1 occur in the graph
    assert(nodeset.size() == (unsigned int)n);

    // Check that graph does not contain multiple streets between nodes.
    check_no_multi_streets(graph);

    // Find optimal path and check that graph is connected.
    vector<int> path;
    find_path(graph, &path);

    // Check that the max-cap path is unique.
    check_unique_path(graph, path);

    // Determine list of streets to block.
    vector<int> blocked;
    find_blocked_streets(graph, path, &blocked);

    // Write output.
    if (blocked.empty()) {
        printf("none\n");
    } else {
        bool first = true;
        for (int s : blocked) {
            printf(first ? "%d" : " %d", s);
            first = false;
        }
        printf("\n");
    }

    return 0;
}
