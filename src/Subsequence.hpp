/*
 * Subsequence.hpp
 *
 *  Created on: 08-Jul-2017
 *      Author: sreram
 *
 *  copyright (c) 2017 K Sreram, All rights reserved.
 *
 */

#ifndef SUBSEQUENCE_HPP_
#define SUBSEQUENCE_HPP_

#include "Subsequence.h"

#include <assert.h>
#include <algorithm>
#include <deque>


template <typename ArrayEleType>
void Subsequence <ArrayEleType>::highest_exponent (uint64_t& n, uint8_t& count) {
	while (n) {
		n = n >> 1;
		count++;
	}
}


template <typename ArrayEleType>
bool Subsequence <ArrayEleType>::check_overflow_prod(uint64_t n1, uint64_t n2, uint8_t bits) {

	uint8_t countN1 = 0, countN2 = 0;
	highest_exponent (n1, countN1);
	highest_exponent (n2, countN2);

	if (countN1 + countN2 > bits) return true;

	return false;
}


template <typename ArrayEleType>
uint64_t Subsequence <ArrayEleType>::combination_nCr (uint64_t n, uint64_t r) {

	assert (n > 0 && r <= n && "Error, The basic conditions for nCr has be violated");

	return factorial (n) / (factorial(n - r)*factorial(r));
}



template <typename ArrayEleType>
uint64_t Subsequence <ArrayEleType>::compute_2pow_n (uint64_t n) {
	assert (n <= 64 && "Error, Overflow: the maximum size unsigned long long has been exceeded");

	return 0x1 << n;
}



template <typename ArrayEleType>
uint64_t Subsequence <ArrayEleType>::factorial(uint64_t n) {

	uint64_t result = 1;

	for (uint64_t i = 2; i <= n; i++ ) {
		result *= i;
	}

	return result;
}


template <typename ArrayEleType>
bool Subsequence <ArrayEleType>::prod_subsequence_condition (const ArrayType_t& parray) {

	ArrayEleType_t prod = 1;
	for (uint64_t i = 0; i < parray.size(); i++) {
		if (check_overflow_prod (prod, parray[i], sizeof(ArrayEleType_t)*8 ))
			return false; // condition violates on overflow
		prod *= parray[i];

		if (prod >= K_val)
			return false;
	}

	return true;
}



template <typename ArrayEleType>
uint64_t Subsequence <ArrayEleType>::
operation_counter (Condition condition, const ArrayType_t& parray,
		bool& exitFlag, std::set <ArrayType_t>&hashTable) {

	if (parray.size() == 0) {
		exitFlag = true;
		return 0;
	}

	if (parray.size() == 1) { // it is assumed that elements with greater values
							  // are already sampled. So this current "left-over"
		exitFlag = true;	  // value is obviously not greater than or equal to
		return 1;		      // K
	}

	if (condition (parray) == true) {
		exitFlag = false;
		return 1;
	} else {
		exitFlag = false;
		return 0;
	}
}

template <typename ArrayEleType>
void Subsequence <ArrayEleType>::sort_array_subseq_prod() {
	std::sort(sortedArray.begin(), sortedArray.end() );
	for (uint64_t i = 0; i < sortedArray.size(); i++) {
		if (sortedArray[i] > this->K_val) {

			std::vector <ArrayEleType> temp(sortedArray.begin(), sortedArray.begin() + i + 1);
			sortedArray = temp;
			break;
		}
	}
}



template <typename ArrayEleType>
uint64_t Subsequence <ArrayEleType>::subsequence_prod_problem () {
	return recursive_combination_counter (prod_subsequence_condition );
}

template <typename ArrayEleType>
uint64_t Subsequence <ArrayEleType>::recursive_combination_counter (Condition condition) {
	resultCount = recursive_combination (condition, operation_counter);
	return resultCount;
}


template <typename ArrayEleType>
uint64_t Subsequence <ArrayEleType>::subsequence_prod_problem_optimized() {

	uint64_t result = 0;

	if (sortedArray.size() == 0) {
		return 0;
	}

	ArrayEleType_t prod = 1;
	std::deque <Subsequence <ArrayEleType> > splitup;
	for (uint64_t i = 0, j = 0; i < sortedArray.size(); i++) {
		if (check_overflow_prod(prod, sortedArray[i], sizeof(ArrayEleType_t)*8) ) {
			splitup.resize(splitup.size() + 1); // increment size
			std::vector <ArrayEleType_t> temp (sortedArray.begin() + j, sortedArray.begin()+i);
			splitup[splitup.size() - 1].initialize (temp, sort);
		}
	}

	if (splitup.size() == 0) {
		result += recursive_combination (sortedArray, prod_subsequence_condition, operation_counter);
	} else {
		for (uint64_t i = 0; i < splitup.size(); i++) {
			splitup[i].subsequence_prod_problem();
			result += splitup[i].get_result_count();
		}
	}
}


template <typename ArrayEleType>
uint64_t Subsequence <ArrayEleType>::recursive_combination (const ArrayType_t& parray,
		Condition condition, PerformOperation operation) {

	bool exitFlag = false;

	uint64_t counter = 0;
	if (checkList.find(parray) != checkList.end())
		return 0;

	counter += operation (condition, parray, exitFlag, this->checkList);
	checkList.insert(parray);

	if (exitFlag) { // base case
		return counter;
	}

	for (uint64_t i = 0; i < parray.size(); i++) {
		ArrayType_t newArg;

		newArg.resize(parray.size() - 1);

		for (uint64_t j = 0; j <parray.size(); j++) {
			if(j < i) {
				newArg [j] = parray[j];
			} else if (j > i) {
				newArg [j-1] = parray[j];
			}
		}

		counter += recursive_combination (newArg, condition, operation );

	}

	return counter;
}


#endif /* SUBSEQUENCE_HPP_ */
