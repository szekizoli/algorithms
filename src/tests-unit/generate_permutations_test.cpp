#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "gtest/gtest.h"


#include "permutations.h"

namespace PermutationsTest
{
	using namespace szekizoli::algorithms;

	TEST(permutationTest, emptyPermutation)
	{
		lexicographic_permutation<int>::iterator it{ std::vector<int>{} };
		std::vector<int> empty{};
		EXPECT_EQ(empty, *it) << "Template value not 42";
	}

	TEST(permutationTest, beginEndPermutation)
	{
		lexicographic_permutation<int> perm{ std::vector<int>{} };
		std::vector<int> empty{};
		for (const auto& t : perm) {
			EXPECT_EQ(empty, t) << "Value not {}";
		}
	}

	TEST(permutationTest, singletonPermutation)
	{
		lexicographic_permutation<int>::iterator it{ std::vector<int>{1} };
		std::vector<int> singleton{ 1 };
		EXPECT_EQ(singleton, *it) << "Singleton value not {1}";
	}

	void print(std::vector<int> v) {
		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}

	TEST(permutationTest, pairPermutation)
	{
		lexicographic_permutation<int>::iterator it{ std::vector<int>{1, 2} };
		std::vector<int> pair_0{ 1, 2 };
		EXPECT_EQ(pair_0, *it) << "Permutation not expected.";
		std::vector<int> pair_1{ 2, 1 };
		++it;
		EXPECT_EQ(pair_1, *it) << "Permutation not expected.";
	}

	TEST(permutationTest, foreachPermutation)
	{
		lexicographic_permutation<int> perm{ std::vector<int>{1, 2, 3, 4} };
		std::vector<std::vector<int>> expected{
			{ 1, 2, 3, 4 },{ 1, 2, 4, 3 },{ 1, 3, 2, 4 },{ 1, 3, 4, 2 },{ 1, 4, 2, 3 },{ 1, 4, 3, 2 },
			{ 2, 1, 3, 4 },{ 2, 1, 4, 3 },{ 2, 3, 1, 4 },{ 2, 3, 4, 1 },{ 2, 4, 1, 3 },{ 2, 4, 3, 1 },
			{ 3, 1, 2, 4 },{ 3, 1, 4, 2 },{ 3, 2, 1, 4 },{ 3, 2, 4, 1 },{ 3, 4, 1, 2 },{ 3, 4, 2, 1 },
			{ 4, 1, 2, 3 },{ 4, 1, 3, 2 },{ 4, 2, 1, 3 },{ 4, 2, 3, 1 },{ 4, 3, 1, 2 },{ 4, 3, 2, 1 }
		};
		size_t i = 0;
		for (const auto&v : perm) {
			EXPECT_EQ(expected[i], v) << "Permutation not expected." << i;
			++i;
		}
	}
}