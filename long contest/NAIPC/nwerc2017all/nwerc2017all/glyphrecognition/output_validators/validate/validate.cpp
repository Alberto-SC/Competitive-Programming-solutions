#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

const int min_k = 3, max_k = 8;
const double float_abs_tol = 1e-6;

bool compare_double(double jval, double tval) {
	return fabs(jval - tval) <= float_abs_tol;
}

int n;
vector<int> x, y;

double score(int k) {
	double sector = 2*M_PI/k;
	double rmin = 1e100, rmax = 0;
	for (int i = 0; i < n; i++) {
		double alpha = atan2(y[i],x[i]);
		if (alpha < 0) alpha += 2*M_PI;
		while (alpha > sector) alpha -= sector;
		
		double r = hypot(x[i],y[i]) * cos(alpha - sector/2);
		rmin = min(rmin,r);
		rmax = max(rmax,r);
	}
	return (rmin*rmin) / (rmax*rmax);
}

int main(int argc, char **argv) {
	init_io(argc,argv);
	
	judge_in >> n;
	
	x.resize(n), y.resize(n);
	for (int i = 0; i < n; i++) judge_in >> x[i] >> y[i];
	
	int best_k, author_k;
	double best_score, author_score;

	judge_ans >> best_k >> best_score;
	
	if (!(author_out >> author_k >> author_score))
		wrong_answer("Wrong output format: expected an integer and a real number.\n");
	
	if (author_k < min_k || author_k > max_k)
		wrong_answer("Wrong answer: the given value of k is outside of the allowed "
			"range [%d,%d].\n", min_k, max_k);
	
	if (!compare_double(score(author_k), author_score))
		wrong_answer("Wrong answer: the given value of k results in a score of %.8f, which "
			"does not match the given score.\n");
	
	if (!compare_double(best_score, author_score)) {
		if (author_score > best_score)
			judge_error("Judge error: the author found a better answer than the judges!\n");
		wrong_answer("Wrong answer: the given score is less than the optimal score of %.8f "
			" (k = %d).\n", best_score, best_k);
	}
	
	string junk;
	if (author_out >> junk)
		wrong_answer("Wrong output format: found trailing junk (following a correct "
			"answer).\n");
	
	accept();
}
