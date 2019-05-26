#pragma once
#import "range.hpp"

namespace itertools{

	template <typename I, typename J>
	ostream& operator <<(ostream& os, const pair<I,J> myPair) {
		return os << myPair.first << "," << myPair.second;
	}	

	template<typename T1, typename T2>
	class zip{

	private:
		T1 first;
		T2 second;
		

	public:
		zip<T1,T2>(const T1 iter1, const T2 iter2)
			: first(iter1),
			second(iter2) {}

		class const_iterator {

			private:
				typename T1::const_iterator it1Begin;
				typename T1::const_iterator it1End;
				typename T2::const_iterator it2Begin;
				typename T2::const_iterator it2End;

			public:
				const_iterator(typename T1::const_iterator tIt, typename T1::const_iterator tIit1End, typename T2::const_iterator sIt, typename T2::const_iterator sIit1End):
					it1Begin(tIt), it1End(tIit1End),
					it2Begin(sIt), it2End(sIit1End)
				 { }

				const auto operator*() const {
					return pair(*it1Begin, *it2Begin);
				}

				// ++i;
				const_iterator& operator++() {
					++it1Begin;
					++it2Begin;
					return *this;
				}

				// i++;
				const const_iterator operator++(int) {
					iterator It(*this);
					operator++();
					return It;
				}

				bool operator==(const const_iterator& other) const {
					if(it1Begin == other.it1Begin)
						if(it2Begin == other.it2Begin)
							return  true;
					return false;
				}

				bool operator!=(const const_iterator& rhs) const {
					if(*this==rhs)
						return false;
					return true;
				}


				template <typename I, typename J>
				friend std::ostream& operator <<(std::ostream& os, const typename zip<I,J>::const_iterator& it);

		};  // END OF CLASS const_iterator
		
		typename zip<T1,T2>::const_iterator begin() const {
			return zip<T1,T2>::const_iterator(first.begin(), first.end(), second.begin(), second.end());
		}
			
		typename zip<T1,T2>::const_iterator end() const {
			return zip<T1,T2>::const_iterator(first.end(), first.end(), second.end(), second.end());
		}

	};   // END OF CLASS zip

	template <typename I, typename J>
	ostream& operator <<(ostream& os, const typename zip<I,J>::const_iterator& it) {
		return os << (*it);
	}
}
