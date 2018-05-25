#ifndef Range_H__
#define Range_H__

#include <iostream>
#include <string>
#include <ostream>

class Range;

class RangeIterator {
    friend Range;
	public:
		RangeIterator(int ptr_) { ptr = ptr_; };
		int operator*() {return ptr;}
		const int operator*() const {return ptr;} 

		bool operator==(const RangeIterator &other) const {return ptr==other.ptr;}
		bool operator!=(const RangeIterator &other) const {return ptr!=other.ptr;}

		RangeIterator operator++();
		RangeIterator operator--();

		RangeIterator operator++(int);
		RangeIterator operator--(int);
	
	private:
		int ptr;
};

class Range {
	public:
		friend RangeIterator;
		typedef RangeIterator iterator;
		Range(const int a, const int b) { first = a; last = b; }

		iterator begin() { return iterator(first); }
		iterator end() { return iterator(last+1); }
	
	private:
		int first, last;
};

RangeIterator RangeIterator::operator++() {
	ptr++;
	return *this;
}

RangeIterator RangeIterator::operator--() {
	ptr--;
	return *this;
}

RangeIterator RangeIterator::operator++(int) {
    RangeIterator oldIt = *this;
	ptr++;
	return oldIt;
}

RangeIterator RangeIterator::operator--(int) {
	RangeIterator oldIt = *this;
	ptr--;
	return oldIt;
}

#endif