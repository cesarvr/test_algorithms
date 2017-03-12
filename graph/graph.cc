// AlgorithmPractice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template <typename Value>
class Node {
public:
	Node(Value _name) : name(_name) {};

	void addFriend(Node* node) {
		friends.push_back(node);
	}

	std::vector<Node*>& getFriends() {
		return friends;
	}
	
	bool isLeaf() {
		return friends.size() == 0;
	}

	Value& getValue() {
		return name;
	};

private:
	std::vector<Node*> friends;
	Value name;
};

template <typename Node, typename Collection>
bool hasBeenVisited(Node& candidate, Collection& collection) {
	for (Node node : collection)
		if (candidate->getValue().compare( node->getValue() ) == 0 )
			return true;

	return false;
}

template <typename Node>
int Heightz(Node* node) {
	std::vector<Node *> visited;

	std::function<int(Node*)>traverse = [&visited, &traverse](Node* node) {
		int size = 0;

		if (hasBeenVisited(node, visited)) return 0;

		auto friends = node->getFriends();
		size += friends.size();
		visited.push_back(node);

		for (auto _friend : friends)
			size += traverse(_friend);

		return size;
	};

	return traverse(node);
}

template <typename Node>
int Height(Node* node) {
	std::vector<Node *> visited;

	std::function<int(Node*)>findLeaf = 
		[&visited, &findLeaf](Node* node) {
	
		int path = 0; 
		if (hasBeenVisited(node, visited)) return 0;

		auto friends = node->getFriends();
		
		for (auto _friend : friends) {
			auto tmp = findLeaf(_friend);
			path = (path > tmp) ? path : tmp;
		}

		return 1 + path;
	};

	return findLeaf(node);
}



using sNode = Node<std::string>;


int main()
{
/*
     a -  z
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
	sNode z("Massiel");

	a.addFriend(&z);
	a.addFriend(&b);


	b.addFriend(&c);
	b.addFriend(&d);

	c.addFriend(&o);
	d.addFriend(&o);

	cout << "hello" << endl;
	cout << "The Height for A the graph is: " << Height(&a) << endl;
	cout << "The Height for C the graph is: " << Height(&c) << endl;
	cout << "The Height for Z the graph is: " << Height(&z) << endl;
	cout << "The Height for B the graph is: " << Height(&b) << endl;
	cin.ignore();
	return 0;
}
