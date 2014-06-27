//implement a recursive find count

#include <iostream>

using namespace std;

struct Node {
	int age;
	Node* next;
};

// declare the list header structure
struct List {
	int cnt;
	Node* head;
	Node* tail;
	List() {
		cnt = 0;
		head = NULL;
		tail = NULL;
	}
};


// add elt to the end of L
void append(List& L, int elt) {
	Node* newNode = new Node;
	newNode->age = elt;
	newNode->next = NULL;

	if (L.cnt == 0) {
		L.head = L.tail = newNode;
	}
	else {
		L.tail->next = newNode;
		L.tail = newNode;
	}
	L.cnt++;
}

int count(Node* L) {
	int result;
	
	if(L == NULL)
		return 0;
	
	if(L->age >= 50){
		result = 1;
	} else {
		result = 0;
	}
	
		
	return result + count(L->next);
}

int main(){
	List L;
	append(L, 0);
	append(L, 90);
	append(L, 00);
	
	int res = count(L.head);
	cout<<"result is: "<<res<<endl;
}