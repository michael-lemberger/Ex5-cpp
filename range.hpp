#pragma once
namespace itertools{

	template<typename T>
	class range{

	private:

		T first, last;		

	public:
		range<T>(const T _first, const T _last)
			: first(_first), last(_last) {}

		range<T> (const range& other)
			: first(other.first), last(other.last) {}

		class const_iterator {

			private:
				T it;

			public:
				const_iterator(T member)
					: it(member) {
				}

				const_iterator(const const_iterator &other)
					: it(other.it) {
				}

				const T operator*() const {
					return it;
				}

				// ++i;
				const_iterator& operator++() {
					++it;
					return *this;
				}

				// i++;
				const const_iterator operator++(int) {
					iterator tmpIt(*this);
					operator++();
					return tmpIt;
				}

				bool operator==(const const_iterator& other) const {
					if(it == other.it)
						return true;
					return false;
				}

				bool operator!=(const const_iterator& other) const {
					if(it != other.it)
						return true;
					return false;
				}

				template <typename U>
				friend std::ostream& operator <<(std::ostream& os, const const_iterator& it);

		};  // END OF CLASS ITERATOR

		const_iterator begin() const {
			return range<T>::const_iterator(first);
		}
			
		const_iterator end() const {
			return range<T>::const_iterator(last);
		}

	};   // END OF CLASS RANGE

	template <typename U>
	ostream& operator <<(ostream& os, const typename range<U>::const_iterator& it) {
		return os << (*it);
	}
}
