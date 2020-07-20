#include <array>
#include <cassert>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>

/* solution explained in README.txt */

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

// the mapped-to type of the DP table
struct Value {
	Value() : length(1e9) {}
	int length;
	// these are needed for the solution backtracking at the end
	char last_theorem;
	char proof_index;
};

std::array<Value, 1 << 20> dp;
Output bottom_up_forward(const Input &input) {

	dp[0].length = 0;

	std::pair<int, int> best{1e9, 0};

	// loop over all subsets
	// When we get to S, all subsets of S have already been processed
	for(int mask = 0; mask < 1 << input.n; ++mask) {
		// when no value set, skip
		// this results in a major speed improvement over the backward dp
		if(dp[mask].length == 1e9) continue;

		// when the root theorem is included, update best answer
		if(mask & 1) { best = std::min(best, {dp[mask].length, mask}); }

		// loop over unproven (theorem, proof) pairs; update when proof is subset of mask
		for(int i = 0; i < input.n; ++i) {
			if(mask & (1 << i)) continue;
			auto &theorem = input.theorems[i];
			for(size_t j = 0; j < theorem.size(); ++j) {
				auto &proof = theorem[j];
				if((proof.dependencies_mask | mask) == mask) {
					int new_mask   = mask | (1 << i);
					int new_length = dp[mask].length + proof.length;
					if(new_length < dp[new_mask].length) {
						dp[new_mask].length       = new_length;
						dp[new_mask].last_theorem = i;
						dp[new_mask].proof_index  = j;
					}
				}
			}
		}
	}

	// use the extra information to do backtracking to obtain the final solution
	Output output(input.n);
	output.length = best.first;
	auto mask     = best.second;
	while(mask) {
		auto &val                              = dp[mask];
		output.proof_indices[val.last_theorem] = val.proof_index;
		mask ^= 1 << val.last_theorem;
	}

	return output;
}

int main() {

	// Read the relevant data
	Input input;
	std::cin >> input;

	Output output = bottom_up_forward(input);

	assert(output.length < 1e9);
	std::cout << output;
}
