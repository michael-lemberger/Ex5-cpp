#pragma once
#import "range.hpp"
#include "zip.hpp"

namespace itertools{
	

	template<typename T1, typename T2>
	class product{

	private:
		T1 first;
		T2 second;

	public:

		product<T1,T2>(const T1 iter1, const T2 iter2)
			: first(iter1),
			second(iter2) {}

		class const_iterator {

			private:
				typename T1::const_iterator it1Begin;
				typename T1::const_iterator it2End;
				typename T2::const_iterator start;
				typename T2::const_iterator it2Begin;
				typename T2::const_iterator end;

				bool isDone() const {
					return (it2Begin == end || it1Begin == it2End);
				}

			public:
				const_iterator(typename T1::const_iterator iter1Begin, typename T1::const_iterator iter2End, typename T2::const_iterator start2, typename T2::const_iterator end2):
					it1Begin(iter1Begin), it2End(iter2End),
					start(start2), it2Begin(start2), end(end2)
				 { }

				const auto operator*() const {
					return pair(*it1Begin, *it2Begin);
				}

				// ++i;
				const_iterator& operator++() {
					++it2Begin;
					if (it2Begin != end)
						return *this;
					else{
						++it1Begin;
						if (it1Begin == it2End)
							return *this;
						else
							it2Begin = start;
					}	
					return *this;
				}

				// i++;
				const const_iterator operator++(int) {
					iterator It(*this);
					operator++();
					return It;
				}

				bool operator==(const const_iterator& other) const {
					if (it1Begin == other.it1Begin)
						if(it2Begin == other.it2Begin)
							return true;
					return false;
				}

				bool operator!=(const const_iterator& other) const {
					if(*this==other)
						return false;
					return true;
				}

				template <typename I, typename J>
				friend std::ostream& operator <<(std::ostream& os, const typename product<I,J>::const_iterator& it);

		};  // END OF CLASS const_iterator
		
		typename product<T1,T2>::const_iterator begin() const {
			return product<T1,T2>::const_iterator(first.begin(), first.end(), second.begin(), second.end());
		}
			
		typename product<T1,T2>::const_iterator end() const {
			return product<T1,T2>::const_iterator(first.end(), first.end(), second.end(), second.end());
		}

	};   // END OF CLASS product

	template <typename I, typename J>
	ostream& operator <<(ostream& os, const typename product<I,J>::const_iterator& it) {
		return os << (*it);
	}
}
