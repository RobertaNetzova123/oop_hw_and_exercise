/*#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include<sstream>
#include <cstdlib>
using namespace std;

class Exception {};
class ListOfArrays {

    class ArrayNode {

        public:

        int* data_;
        int size_;
        ArrayNode* prev_;
        ArrayNode* next_;

        ArrayNode(int* data, int size)
            : data_(data), size_(size), next_(0), prev_(0) {}

        ~ArrayNode() {
            delete [] data_;
        }

    };

    ArrayNode* head_;
    int size_;

    public:

    class Iterator {

        friend class ListOfArrays;

        ListOfArrays& list_;
        ArrayNode* current_;

        public:

        Iterator(ListOfArrays& list, ArrayNode* current)
            : list_(list), current_(current) {}

        bool operator==(const Iterator& other)  {
		return &list_ == &other.list_ && current_ == other.current_;		
	}

        bool operator!=(const Iterator& other)  {
		return ! operator==(other);
	}

        Iterator& operator++() {
		current_ = current_ -> next_;
		return *this;
	}

        Iterator operator++(int) {
		Iterator prev(list_, current_);
		current_ = current_ -> next_;
		return prev;
	}

       int& operator[](const int& index) {
		if (index > size()) {
				throw Exception();	
		} 
		return current_ -> data_[index];
	}

        int size() {
		return current_ -> size_;
	}

        void show() {
		
		for (int i = 0; i < size(); i++) {
			if (i > 0) cout << " ";
			cout << current_ -> data_[i];
		}
	}
        
        double average() {
		return (double)sum() / size();
	}
        double median() {
		ordered(true);
		if (size() %2 !=0) {
			return (double)current_ -> data_[size()/2];	
		}
		return (double)(current_ -> data_[size()/2] + current_ -> data_[size()/2 - 1])/2;	
	}
        
        int sum() {
		int sum = 0;
		for (int i = 0;i < size(); i++) {
			sum += current_ -> data_[i];
		}
		return sum;
	}

        Iterator& ordered(bool ascending = true) {
		 int temp = 0;
		if (!ascending) {
			for(int i=0;i<size();i++) {
				 for(int j=0;j<size()- (i +1);j++) {
					 if(current_ -> data_[j] < current_ -> data_[j+1]) {
			 			temp = current_ -> data_[j];
			 			current_ -> data_[j] = current_ -> data_[j+1];
			 			current_ -> data_[j+1]= temp;
			 		}
	 			}
	 		}
			return *this;
		}
		 for(int i=0;i<size() ;i++) {
			 for(int j=0;j< size()- (i +1);j++) {
				 if(current_ -> data_[j] > current_ -> data_[j+1]) {
		 			temp = current_ -> data_[j];
		 			current_ -> data_[j] = current_ -> data_[j+1];
		 			current_ -> data_[j+1]=temp;
		 		}
 			}
 		}
		return *this;
	}
    };


    ListOfArrays()
            : size_(0), head_(new ArrayNode(0, 0)) {
        head_->next_ = head_;
        head_->prev_ = head_;
    }
	
   // ~ListOfArrays() ;


  ListOfArrays(const ListOfArrays& other) 
	: size_(other.size_) {
		ListOfArrays  new_arr;
		ArrayNode* arr_node= other.head_->next_;
		for(;arr_node != other.head_;) {
			new_arr.push(arr_node-> data_,0,arr_node->size_);
			arr_node = arr_node -> next_;
				
		}
		this -> head_ = new_arr.head_;
		this -> size_ = new_arr.size_;
   }

  ListOfArrays& operator=(const ListOfArrays& other) {
	head_ = other.head_;
	size_ = other.size_;
	return *this;
  }

    int size() {
	return size_;
    }

void push(int array[], int position, int length) {
		int* arr = new int[length];
		int  k = 0;
		for(int i = position; i < length + position; i++, k++) {
			arr[k] = array[i];
		}
		ArrayNode* node = new ArrayNode(arr, length);
		head_ -> prev_ -> next_ = node;
		node -> prev_ = head_ -> prev_;
		head_ -> prev_ = node;
		node -> next_ = head_;
		size_++;
		
	}

    void averages(double averages[]) {
		int i = 0;
		for (Iterator it = begin();it !=end();++i, ++it) {
			averages[i] = it.average();
		}
		for (int k = 0; k < i; k++) {
			cout << averages[k] << " ";		
		}
		cout << endl;
    }

    void medians(double medians[]) {
		int i = 0;
		for (Iterator it = begin();it !=end();++i, ++it) {
			medians[i] = it.median();
		}

    		for (int k = 0; k < i; k++) {
			cout << medians[k] << " ";		
		}
		cout << endl;
    }
  
    void sizes(int sizes[]) {
   		int i = 0;
		for (Iterator it = begin();it !=end();++i, ++it) {
			sizes[i] = it.size();
		}

		for (int k = 0; k < i; k++) {
			cout << sizes[k] << " ";		
		}
		cout << endl;
    }
 
    void sums(int sums[]) {
		int i = 0;
		for (Iterator it = begin();it !=end();++i, ++it) {
			sums[i] = it.sum();
		}
		
		for (int k = 0; k < i; k++) {
			cout << sums[k] << " ";		
		}
		cout << endl;
    }

    Iterator begin() {
		return Iterator (*this, head_ -> next_);
	}

    Iterator end() {
		return Iterator (*this, head_);
	}

   /* ListOfArrays& ordered(bool ascending = true) {
		for (Iterator it = begin(); it != end(); ++it) {
			it.ordered(ascending);
		}

	/*	if (ascending) {
			for (Iterator it = begin(); it != end(); it++) {
				for (Iterator it2 = ++it; it2 != end(); it2++) {
					int min_size = 0;
					if (it.size() < it2.size()) min_size = it.size();
					else min_size = it2.size(); 
					cout << "size" << min_size<< endl; 
					for (int m = 0; m < min_size; m++) {
						if (it.current_->data_[m] > it2.current_->data_[m]) {
							ArrayNode* copy = new ArrayNode(0,0);
							copy -> next_ = it2.current_ -> next_;
							copy -> next_->prev_ = copy;
							copy -> prev_ = it2.current_ -> next_;
							copy -> prev_ -> next_ = copy;

							it2.current_ -> next_ = it.current_ -> next_;
							it2.current_ -> next_->prev_ = it2.current_;
							head_ -> next_ =  it2.current_;
							it2.current_ -> prev_ = head_;

							it.current_ -> next_ = copy -> next_;
							it.current_ -> next_ -> prev_ = it.current_;
							it.current_ -> prev_ = copy -> next_;
							it.current_ -> prev_ -> next_ = it.current_;
							cout << "b" << endl;
							delete []copy;
							break;
						}
					//break;
					}	cout << "a" << endl;	 break;						
				}
			}		
		}*/
		
    //}
//works
    ListOfArrays& operator*=(const int& coef) {
		for (Iterator it = begin(); it != end(); ++it) {
			for (int i = 0; i < it.size(); i++) {
					it[i] *= coef;
			}
		}
		return *this;
    }
//works
    ListOfArrays& operator+=(const int& value) {
		for (Iterator it = begin(); it != end(); ++it) {
			for (int i = 0; i < it.size(); i++) {
				it[i] += value;
			}
		}
	return *this;
    }
//works
    void show() {
		for (Iterator it = begin(); it!= end(); it++) {
			//cout << "rety";
			if (it!=begin()) cout << " ";
			it.show();
			if(it.current_ -> next_ != end().current_) 
				cout << ";";
		}
			cout << endl;
    }
};

int main() {
	string input;
	cout << "> ";
	getline(cin, input);
    	stringstream in(input);
	string arr;
	int m = 0;
	ListOfArrays l1;
	//int current_arr[100];
	while(getline(in, input,';')) {
		int current_arr[100];
		stringstream list(input);
			for(m=0;getline(list, arr,' ');m++) {
			istringstream number(arr);
			int value;
			number >> value;

			if(!number.fail()) {current_arr[m] = value;} else m--;

		} l1.push(current_arr,0,m);
	}
	string commands;
	cout << "> ";
	getline (cin, commands);
	while (commands != "quit") {
	stringstream new_command(commands);	
	while (getline (new_command, commands, '.')) {
		string word;
		istringstream is(commands);
		is >> word;
		if (word == "show") {l1.show();}
		
		if (word == "size") {
			cout << l1.size() << endl;
		}
		if (word == "averages") {
			double average[l1.size()];
			l1.averages(average);
		}
		if (word == "medians") {
			double median[l1.size()];
			l1.medians(median);
		}
		if (word == "sums") {
			int sum[l1.size()];
			l1.sums(sum);
		}
		if (word == "sizes") {
			int size[l1.size()];
			l1.sizes(size);
		}
		if (word.substr(0,3)=="mul") {
			
			int num = atoi(word.substr(4).c_str());
			l1 *= num;
		}
		if (word.substr(0,3)=="add") {
			
			int num = atoi(word.substr(4).c_str());
			l1 += num;
		}
		bool state = false;
		if (word == "begin") {
			ListOfArrays::Iterator it = l1.begin();
			while (getline (new_command, commands, '.')) {
				string word;
				istringstream is(commands);
				is >> word;
				
				if (word == "quit") {
					state = true;
					break;
				}
			        if(word == "show"){
                            		 it.show();
					 cout << endl;
                            	}
				if (word == "next") {
					it++;
					if (it == l1.end()) {
						cout <<"ERROR: End of iteration"<< endl;
						return 1;
					}
				}
				if(word == "size") {
                            		cout << it.size()<< endl;
				}
				if(word == "average") {
                            		cout <<it.average()<< endl;
                        	}
				if(word == "median") {
                            		cout <<it.median()<< endl;
				}
                        	if(word == "sum") {
                            		cout <<it.sum()<< endl;
				}
			}
		}
	if (state) return 2;
	}

	cout << "> ";
	getline (cin, commands);
    }
    return 0;
}
