// Solution by Ragnar
// Proofs
// (n-1)! solution by checking all permutations of  theorems
// Permutations that only differ after the occurrence of theorem 1 are only checked once

#include <algorithm>
#include <array>
#include <iostream>
#include <istream>
#include <ostream>
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

// the mapped-to type of the DP table
struct Value {
	Value() : length(1e9) {}
	int length;
	// these are needed for the solution backtracking at the end
	char last_theorem;
	char proof_index;
};

int factorial(const Input &input) {
	int answer = 1e9;
	// loop over all subsets not containing 0
	for(int mask = 0; mask < 1 << input.n; mask += 2) {
		std::vector<int> list;
		for(int i = 0; i < input.n; ++i)
			if(mask & (1 << i)) list.push_back(i);

		// append first theorem to the end of list
		list.push_back(0);

		do {
			// test whether we can prove theorems in the order given by the list
			int done_mask = 0;
			int length    = 0;
			for(auto i : list) {
				auto &theorem   = input.theorems[i];
				int this_length = 1e9;
				for(auto proof : theorem)
					if((proof.dependencies_mask & done_mask) == proof.dependencies_mask)
						this_length = std::min(this_length, proof.length);
				length += this_length;
				if(this_length == 1e9) break;
				done_mask |= 1 << i;
			}
			answer = std::min(answer, length);
		} while(std::next_permutation(list.begin(), list.end() - 1));
		if(answer < 1e9) return answer;
	}

	return answer;
}

int main() {
	// Read the relevant data
	Input input;
	std::cin >> input;
	std::cout << factorial(input) << std::endl;
}
