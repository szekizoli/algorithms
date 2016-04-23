#pragma once

#include <iterator>
#include <vector>

namespace szekizoli {
	namespace algorithms {

		template<typename T>
		class lexicographic_permutation final {
		public:
			class lexicographic_permutation_iterator;

			typedef lexicographic_permutation_iterator iterator;
			typedef const lexicographic_permutation_iterator const_iterator;

			lexicographic_permutation(const std::vector<T>& v) : input(v) {}
			lexicographic_permutation(const lexicographic_permutation<T>& other) : input(other.input) {}
			iterator begin() {
				return lexicographic_permutation_iterator(input);
			}
			const_iterator begin() const {
				return lexicographic_permutation_iterator(input);
			}
			iterator end() {
				return lexicographic_permutation_iterator();
			}

		private:
			class lexicographic_permutation_iterator final
				: public std::iterator<std::forward_iterator_tag, std::vector<T>> {
			public:
				lexicographic_permutation_iterator(const std::vector<T>& v) : current(v), state(iteration_state::ongoing) {}
				lexicographic_permutation_iterator(const lexicographic_permutation_iterator& it)
					: current(it.current), state(it.state) {}
				lexicographic_permutation_iterator& operator++() { next(); return *this; }
				lexicographic_permutation_iterator operator++(int) {
					lexicographic_permutation_iterator tmp(*this);
					operator++();
					return tmp;
				}
				bool operator==(const lexicographic_permutation_iterator& rhs) const 
				{
					return rhs.state == state && (state == iteration_state::finished || current == rhs.current); 
				}
				bool operator!=(const lexicographic_permutation_iterator& rhs) const
				{ 
					return !(*this == rhs); 
				}
				std::vector<T>& operator*() { return current; }
				const std::vector<T>& operator*() const { return current; }
			
				lexicographic_permutation_iterator() : state(iteration_state::finished) {}
			private:
				enum iteration_state { ongoing, finished };
				iteration_state state;
				std::vector<T> current;
				size_t size()             const { return current.size(); }
				void   swap(size_t n, size_t k) { std::swap(current[n], current[k]); }
				T      at(size_t i)       const { return current.at(i); }
				void   next();
			};
		
			const std::vector<T> input;
		};

		// This is an implementation of the Lexicographic algorithm for permutations generation,
		// described in Knuth's "The Art of Computer Programming", Volume 4, Chapter 7, Section 7.2.1.2.
		template<typename T>
		void lexicographic_permutation<T>::lexicographic_permutation_iterator::next() 
		{
			if (size() < 2) {
				state = iteration_state::finished;
				return;
			}
			size_t j = size() - 2;
			while (!(at(j) < at(j + 1))) {
				if (j == 0) {
					state = iteration_state::finished;
					return;
				}
				--j;
			}

			size_t l = size() - 1;
			while (!(at(j) < at(l))) {
				--l;
			}

			swap(j, l);

			// sorting, currently reversed
			size_t k = j + 1;
			l = size() - 1;
			while (k < l) {
				swap(k++, l--);
			}
		}
	}
}