// Solution by Ragnar
// Proofs

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
std::array<int, 1 << 20> dist;
int dijkstra(const Input &input) {
	dist.fill(1e9);
	std::priority_queue<S> q;
	q.push({0, 0});
	dist[0] = 0;
	while(!q.empty()) {
		auto mask   = q.top().mask;
		auto length = q.top().dist;
		q.pop();
		if(length != dist[mask]) continue;

		// when the root theorem is included we're done :)
		if(mask & 1) return length;

		// loop over unproven (theorem, proof) pairs; update when proof is subset of mask
		for(int i = 0; i < input.n; ++i) {
			if(mask & (1 << i)) continue;
			auto &theorem = input.theorems[i];
			for(size_t j = 0; j < theorem.size(); ++j) {
				auto &proof = theorem[j];
				if((proof.dependencies_mask | mask) == mask) {
					int new_mask   = mask | (1 << i);
					int new_length = length + proof.length;
					if(new_length < dist[new_mask]) {
						dist[new_mask] = new_length;
						q.push({new_length, new_mask});
					}
				}
			}
		}
	}
	// theorem 1 is given to be provable
	assert(false);
}

int main() {
	// Read the relevant data
	Input input;
	std::cin >> input;
	std::cout << dijkstra(input) << std::endl;
}
