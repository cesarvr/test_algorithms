#include <iostream>
#include <vector>
#include <string>

using namespace std; 

template <typename Collection, typename Values>
void Swap(Collection& list, Values origin, Values dest){

   auto tmp  = list[origin]; 
   list[origin] = list[dest]; 
   list[dest] = tmp;
}

//sorting algorithms 
template <typename Collection>
void SelectionSort(Collection& list){
  auto len = list.size();

  for(auto p1 = 0; p1<len; p1++){
    auto candidate = p1; 
    for(auto p2 = p1+1; p2<len; p2++){

      if(list[p2] < list[candidate])
        candidate = p2;  

      Swap(list, candidate, p1);      
    }    
  }
}


//base sort class
template <typename Collection, typename SortAlgorithm>
class Sort {
	
public: 
	Sort(Collection list, SortAlgorithm& sortAlgorithm): list(list), sortAlgorithm(sortAlgorithm){
	}	

  void sort(){
    sortAlgorithm(list);
  }

	void show(){
		cout << "# ";
		for(auto element: list)
			cout << element << " ";
		cout << "#" << endl;
	}

private: 
	Collection list; 	
  SortAlgorithm& sortAlgorithm;
};

vector<char> tokenizer(string& message){
	auto len = message.size();
  cout << "ret..." << len << endl;
	vector<char> ret;	

	for(int x=0; x<len; x++)
		ret.push_back(message[x]);

  cout << "ret..." << len << endl;
	return ret;
};



int main(){
  cout << "sorting" << endl;
	string msg = "SORTEXAMPLE";
	auto list = tokenizer(msg);

	Sort<decltype(list), decltype(SelectionSort<vector<char>>)> insertSort(list, SelectionSort);
  	
	insertSort.show();
  
  cout << "sorting.." << endl;   

  insertSort.sort();

	insertSort.show();

	return 0;
}
