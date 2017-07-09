/*
 * main.cpp
 *
 *  Created on: 08-Jul-2017
 *      Author: sreram
 *
 * copyright (c) 2017 K Sreram, All rights reserved.
 *
 */


#include "Subsequence.h"

#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ctime>

int main () {

    srand(time(NULL));

	Subsequence <uint64_t>::ArrayType_t arr;

	uint64_t size = std::rand() % 30 + 1;

	arr.resize(size);

	for (uint64_t i = 0; i < size; i++) {
		arr [i] = std::rand()% 1000;
	}


	uint64_t k = std::rand();

	Subsequence <uint64_t>::get_K_val(k);
	Subsequence <uint64_t> seq (arr, true), seq2 (arr, true);



	std::cout << "K = " << k << "\n";

	for (uint64_t i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << "\n";
	}

	std::cout.flush();


	/*const clock_t begin_time2 = clock();
	std::cout << "\nsolution = " << seq2.subsequence_prod_problem_optimized();
	std::cout << "\ntime elapsed for solution 2:" << float( clock () - begin_time2 ) /  CLOCKS_PER_SEC << "s";
	std::cout.flush();*/



	const clock_t begin_time = clock();
	std::cout << "\nsolution = " << seq.subsequence_prod_problem();
	std::cout << "\ntime elapsed for solution 1:" << float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s";
	std::cout.flush();




	return 0;
}




