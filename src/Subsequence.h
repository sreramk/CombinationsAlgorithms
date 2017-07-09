/*
 * Subsequence.h
 *
 *  Created on: 07-Jul-2017
 *      Author: sreram
 *
 *	copyright (c) 2017 K Sreram, all rights reserved.
 *
 */

#ifndef SUBSEQUENCE_H_
#define SUBSEQUENCE_H_

#include <vector>
#include <stdint.h>
#include <set>

template <typename ArrayEleType>
class Subsequence {
public:


	typedef ArrayEleType ArrayEleType_t;
	typedef std::vector<ArrayEleType_t> ArrayType_t;
	typedef bool (*Condition) (const ArrayType_t& parray);
	typedef uint64_t (*PerformOperation) (Condition condition, const ArrayType_t& parray,
			bool& exitFlag, std::set <ArrayType_t>&hashTable);

private:

	ArrayType_t rawArray;
	ArrayType_t sortedArray;

	uint64_t resultCount;

	static uint64_t K_val;

	std::set <ArrayType_t> checkList;

	bool sort;

	void sort_array_subseq_prod();

public:

	Subsequence (const ArrayType_t& prawArray, bool psort = false) :
											rawArray (prawArray), resultCount (0), sort(psort) {
		sortedArray = rawArray;

		if (sort) {
			sort_array_subseq_prod ();
		}

	}


	Subsequence () :resultCount (0), sort (false){}

	void initialize (const ArrayType_t& prawArray, bool psort = false) {
		resultCount = 0;
		rawArray = prawArray;
		sort  = psort;
		if (sort) {
				sort_array_subseq_prod ();
		}
	}

	static void get_K_val (uint64_t pK_Val) {
		K_val = pK_Val;
	}


	std::set <ArrayType_t>& hash_table() {
		return checkList;
	}

	uint64_t get_result_count () {
		return resultCount;
	}

	static inline void highest_exponent (uint64_t& n, uint8_t& count);

	static bool check_overflow_prod (uint64_t n1, uint64_t n2, uint8_t bits);

	static uint64_t factorial (uint64_t n);

	static uint64_t combination_nCr (uint64_t n, uint64_t r);

	static uint64_t compute_2pow_n (uint64_t n);


	uint64_t recursive_combination (Condition condition, PerformOperation operation) {
		return recursive_combination (sortedArray, condition, operation);
	}

	uint64_t recursive_combination ( const ArrayType_t& parray,
			Condition condition, PerformOperation operation);


	static uint64_t operation_counter (Condition condition, const ArrayType_t& parray,
			bool& exitFlag, std::set <ArrayType_t>&hashTable);

	uint64_t recursive_combination_counter (Condition condition);

	static bool prod_subsequence_condition (const ArrayType_t& parray);

	uint64_t subsequence_prod_problem ();
	uint64_t subsequence_prod_problem_optimized();
};


template <typename ArrayEleType>
uint64_t Subsequence <ArrayEleType>::K_val = 0;



#include "Subsequence.hpp"


#endif /* SUBSEQUENCE_H_ */
