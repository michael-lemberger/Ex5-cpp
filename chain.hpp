#pragma once
#import "range.hpp"

namespace itertools{

	template<typename T1, typename T2>
	class chain{

	private:
		T1 first;
		T2 second;
		

	public:

		chain<T1,T2>(const T1 iter1, const T2 iter2): first(iter1),second(iter2) {}

		class const_iterator {

			private:
				typename T1::const_iterator it1Begin;
				typename T1::const_iterator it1End;
				typename T2::const_iterator it2Begin;
				typename T2::const_iterator it2End;

			public:
				const_iterator(const typename T1::const_iterator &iter1Begin, const typename T1::const_iterator &iter1End, const typename T2::const_iterator &iter2Begin, const typename T2::const_iterator &iter2End):
					it1Begin(iter1Begin), it1End(iter1End),it2Begin(iter2Begin),it2End(iter2End){ }

				const_iterator(const const_iterator &other): //copy contructor
					it1Begin(other.it1Begin), it1End(other.it1End),
					it2Begin(other.it2Begin),it2End(other.it2End){ }

				const auto operator*() const {
					if (it1Begin != it1End)
						return *it1Begin;
					else return *it2Begin;
				}

				// ++i;
				const_iterator& operator++(){
					if(it1Begin != it1End)
						++it1Begin;
					else
						++it2Begin;
					return *this;	
				}

				// i++;
				const const_iterator operator++(int){
					iterator It(*this);
					operator++();
					return It;
				}

				bool operator==(const const_iterator& other) const {
					if(it1Begin == other.it1Begin) 
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
				friend std::ostream& operator <<(std::ostream& os, const typename chain<I,J>::iterator& it);

		};  // END OF CLASS ITERATOR
		
		typename chain<T1,T2>::const_iterator begin() const {
			return chain<T1,T2>::const_iterator(first.begin(), first.end(), second.begin(), second.end());
		}
			
		typename chain<T1,T2>::const_iterator end() const {
			return chain<T1,T2>::const_iterator(first.end(), first.end(), second.end(), second.end());
		}

	};   // END OF CLASS chain

	template <typename I, typename J>
	ostream& operator <<(ostream& os, const typename chain<I,J>::const_iterator& it) {
		return os << (*it);
	}
}
