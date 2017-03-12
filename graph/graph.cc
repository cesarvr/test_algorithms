#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

template <typename Value>
class Node {
public:
	Node(Value _name): name(_name){}; 
	
	void addFriend(Node node){
		friends.push_back(node);
	}
	
	std::vector<Node>& getFriends(){
		return friends;
	}

	Value& getValue(){ 
		return name; 
	}; 

private:
	std::vector<Node> friends;		
	Value name;
};

template <typename Node, typename Collection>
bool hasBeenVisited(Node& candidate, Collection& collection){
	for(Node node: collection)
		if(candidate.getValue() == node.getValue())
			return true;
		
	return false;
}

template <typename Node>
	int Height(Node& node){
		std::vector<Node> visited; 

		std::function<int(Node&)>traverse = [&visited, &traverse](Node& node){
			int size = 0; 

			if(hasBeenVisited(node, visited)) return 0;
			
			auto friends = node.getFriends();		
			size += friends.size();
			visited.push_back(node); 	

			for(auto _friend: friends) 
				size += traverse(_friend);

			return size;
		};

		return traverse(node);	
	}

using sNode = Node<std::string>;


int main()
{
		/*
				a
				|
				b
			 / \ 
			c   d
			 \ /
        o
		*/

		sNode a("Cesar"); 

		sNode b("Jessica"); 

		sNode c("Stefy"); 
		sNode d("Virginia"); 
		
		sNode o("Pepe"); 

		a.addFriend(b);
		b.addFriend(c);
		b.addFriend(d);
		
		c.addFriend(o);
		d.addFriend(o);

		auto height = Height(a);

		cout << "hello" << endl;
		cout << "The Height of the graph is: " << height << endl;
    return 0;
}
