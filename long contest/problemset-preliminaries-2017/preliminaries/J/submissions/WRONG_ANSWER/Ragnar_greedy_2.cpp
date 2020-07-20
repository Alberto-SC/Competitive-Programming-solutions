// Solution by Ragnar
// Proofs
// (n-1)! solution by checking all permutations of  theorems
// Permutations that only differ after the occurrence of theorem 1 are only checked once

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <istream>
#include <ostream>
#include <queue>
#include <vector>

// datastructure to hold a proof: the length and the theorem numbers of the dependencies
// the `mask` member is a bitmask corresponding to the dependencies
struct Proof {
	int length;
	std::vector<int> dependencies; // 0 based
	int dependencies_mask;

	friend std::ostream &operator<<(std::ostream &o, const Proof &proof) {
		o << proof.length << ' ' << proof.dependencies.size();
		for(auto d : proof.dependencies) o << ' ' << d + 1;
		o << "\n";
		return o;
	}

	friend std::istream &operator>>(std::istream &i, Proof &proof) {
		i >> proof.length;
		int num_dependencies;
		i >> num_dependencies;
		proof.dependencies_mask = 0;
		proof.dependencies.resize(num_dependencies);
		for(auto &d : proof.dependencies) {
			i >> d;
			//--d;
			proof.dependencies_mask |= 1 << d;
		}
		return i;
	}
};

// a theorem is simply a list of possible proofs
using Theorem = std::vector<Proof>;

// input: the number of theorems and a list of theorems
struct Input {
	int n;
	std::vector<Theorem> theorems;

	friend std::istream &operator>>(std::istream &i, Input &input) {
		i >> input.n;
		input.theorems.resize(input.n);
		for(auto &theorem : input.theorems) {
			int p;
			i >> p;
			theorem.resize(p);
			for(auto &proof : theorem) i >> proof;
		}
		return i;
	}
};

struct Output {
	Output(int n = 0) : length(1e9), proof_indices(n, -1) {}
	int length;
	std::vector<int> proof_indices; // 0 based, -1 when unused

	friend std::ostream &operator<<(std::ostream &o, const Output &output) {
		o << output.length << "\n";
		// Do not print which proofs were used
		// for(auto index : output.proof_indices) o << index + 1 << "\n";
		return o;
	}
};

struct S {
	int dist, mask;
	bool operator<(const S &r) const { return dist > r.dist; }
};
int greedy(const Input &input) {
	// sort the proofs on number of dependencies;
	// iterate over them until a suitable one is found;
	// add it to the state until thm 1 is proven

	using PL = std::pair<Proof, int>;
	std::vector<PL> proofs; // we also need the thm number
	for(int i = 0; i < input.n; ++i)
		for(auto &p : input.theorems[i]) proofs.push_back({p, i});

	sort(proofs.begin(), proofs.end(), [](const PL &l, const PL &r) {
		return l.first.dependencies.size() < r.first.dependencies.size();
	});

	int state  = 0;
	int length = 0;

	while(true) {
		for(auto &p : proofs) {
			// theorem already known?
			if(state & (1 << p.second)) continue;
			if((p.first.dependencies_mask & state) == p.first.dependencies_mask) {
				length += p.first.length;
				if(p.second == 0) return length;

				state |= 1 << p.second;
				goto end;
			}
		}

		assert(false);
	end:;
	}
}

int main() {
	// Read the relevant data
	Input input;
	std::cin >> input;
	std::cout << greedy(input) << std::endl;
}
