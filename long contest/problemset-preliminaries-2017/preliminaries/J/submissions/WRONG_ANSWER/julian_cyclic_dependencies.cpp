// Assumes the graph is a DAG.

#include <iostream>

using namespace std;

const int M = 1 << 25;

int no_of_proofs[20],
    proof_lengths[20][10],
    deps[20][10]{0};

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> no_of_proofs[i];
        for (int j = 0; j < no_of_proofs[i]; j++) {
            int no_of_deps;
            cin >> proof_lengths[i][j] >> no_of_deps;
            for (int k = 0; k < no_of_deps; k++) {
                int dep;
                cin >> dep;
                deps[i][j] |= (1 << (dep - 1));
            }
        }
    }

    int ans = M;
    for (int m = 0; m < (1 << (n - 1)); m++) {
        int mask = (m << 1) + 1;
        int tsol = 0;
        for (int t = 0; t < n; t++) {
            if ((mask >> t) & 1) {
                int sol = M;
                for (int i = 0; i < no_of_proofs[t]; i++) {
                    if ((deps[t][i] & mask) == deps[t][i]) {
                        sol = min(sol, proof_lengths[t][i]);
                    }
                }
                tsol += sol;
            }
        }

        ans = min(ans, tsol);
    }

    cout << ans << endl;

    return 0;
}
