#include <utility>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include "validate.h"
using namespace std;

/* Check one test case. */
void check_case() {
    int n, c;
    judge_in >> n >> c;
    vector<pair<int, int>> apps(n);
    for (int i = 0; i < n; i++) judge_in >> apps[i].first >> apps[i].second;

    int judge_best;
    judge_ans >> judge_best;

    int author_best;
    if (!(author_out >> author_best)) {
        wrong_answer("Wrong output format.");
    }

    int installed_size = 0;
    set<int> installed;
    for (int i = 0; i < author_best; i++) {
        int idx;
        if (!(author_out >> idx)) wrong_answer("Wrong output format.");
        if (!(1 <= idx && idx <= n)) wrong_answer("App number out of range: %d", idx);
        idx--;
        if (installed.count(idx))
            wrong_answer("Tried to install an app twice.");
        installed.insert(idx);
        if (installed_size + apps[idx].first > c)
            wrong_answer("Exceeded storage capacity during an app download.");
        installed_size += apps[idx].second;
        if (installed_size > c)
            wrong_answer("Exceeded storage capacity during app installation.");
    }

    if (judge_best < author_best) {
        judge_error("Got better solution than judge (value %d, judge %d)\n",
                author_best, judge_best);
    } else if (author_best < judge_best) {
        wrong_answer("Suboptimal solution installing %d apps, opt = %d\n", author_best, judge_best);
    } else {
        /* Yay! */
        accept();
    }
}

int main(int argc, char **argv) {
    init_io(argc, argv);

    check_case();
}
