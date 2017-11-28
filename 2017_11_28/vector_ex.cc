#include <iostream>
using namespace std;

class Exception {};
class Vector {
	int capacity_;
	int size_;
	int* buffer_;
public:


	Vector(int capacity = 2)
	: capacity_(capacity),
	  size_(0),
	  buffer_(new int[capacity])
	{}

	~Vector() {
		delete [] buffer_;
	}

	int size() const {
		return size_;
	}

	bool empty() const {
		return size() == 0;
	}

	int& operator[](int n) {
		if (!empty()) {
			if (n < size()) {
				return buffer_[n];
			} 
		}		
		throw Exception();
	}

	const int& operator[](int n) const {
		if (!empty()) {
			if (n < size()) {
				return buffer_[n];
			} 
		}		
		throw Exception();
	}
	
	void clear() {
		 size_ = 0 ; 
	}

	int capacity() const {
		if (capacity_ < size_) {
			throw Exception();
		}
		return capacity_;
	}

	int& front() {
		if(!empty())
			return buffer_[0];
		throw Exception();			
	}

	const int& front() const {
		if(!empty())
			return buffer_[0];
		throw Exception();
	}

	int& back() {
		if(!empty())
			return buffer_[size_ - 1];
		throw Exception();	
	}
	
	const int& back() const {
		if(!empty())
			return buffer_[size_ - 1];
		throw Exception();
	}

	void push_back(const int& value) {
		if (size_ == capacity_) {
			capacity_ *= 2;
			int* temp = buffer_;
			buffer_ = new int[capacity_];

			for (int i = 0; i < size_; i++ ) {
				buffer_[i] = temp[i];
			}
			cout << "resized" << endl;
		}
		buffer_[size_++] = value;
		cout << "pushed" << endl;		 
	}

	void pop_back() {
		if (empty()) {
			throw Exception();
		}
		cout << "popped" << endl;
		size_ --;
	}
	void  print() {
		if(empty()) throw Exception();
		for (int i = 0; i < size_; i++ ) {
			cout << buffer_[i] << endl;
		}
	}
// kopirasht konstruktor
	Vector(const Vector& other) : 
	capacity_(other.capacity_), 
	size_(other.size_), 
	buffer_(new int[capacity_]) {
		for (int i = 0; i < size_; i++) {
			buffer_[i] = other.buffer_[i];
		}
	}
// za prisvoiavane

	Vector& operator=(const Vector& other) {
		if (this != &other) {
			delete [] buffer_;
			size_ = other.size_;
			capacity_ = other.capacity_;
			buffer_ = new int [capacity_];
			for (int  i = 0; i < size_; i ++) {
				buffer_[i] = other.buffer_[i];
			}
		}
		return *this;
	}
	
	
};

int main () {
	Vector v1;
	v1.push_back(5);
	v1.push_back(3);
	v1.push_back(8);
	v1.print();
	cout <<"[0] operator: " << v1[0] << endl;
	v1.clear();
	try {	
		cout << v1[5];
		v1.print();

	} catch (Exception ex) {
		cout << "the vector is empty" << endl;
	}
	cout << "...................." << endl;
	v1.push_back(5);
	v1.push_back(3);
	v1.push_back(8);
	cout << "front " << v1.front() << endl;
	v1.pop_back();
	cout << "back " << v1.back() << endl;
	v1.print();
	Vector v2 = v1;
	v2.push_back(100);
	cout << "v2" << endl;
	v2.print();
	Vector v3;
	v3 = v2;
	//v3.push_back(100);
	cout << "v3" <<  endl;
	v3.print();
return 0;
}
