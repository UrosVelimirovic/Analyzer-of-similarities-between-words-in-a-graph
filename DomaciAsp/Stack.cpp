#include "Graf.h"

void Stack::PUSH(ElemHeadRow* elem) {
	ElemSt* novi = new ElemSt;
	novi->data = elem;
	novi->next = top;
	top = novi;
}

ElemHeadRow* Stack::POP() {
	if (top != nullptr) {
		ElemHeadRow* ForReturn = top->data;
		ElemSt* temp = top;
		top = top->next;
		free(temp);
		return ForReturn;
	}
	else {
		cout << "STACK EMPTY!";
		return nullptr;
	}
}
bool Stack::SEMPTY() {
	return top == nullptr;
}
void Stack::WriteStack() {
	ElemSt* temp = top;
	while (temp)
	{
		cout << temp->data->KnotName << " ";
		temp = temp->next;
	}
	cout << endl;
}
Stack::~Stack(){
	while (top != nullptr) {
		ElemSt* temp = top;
		top = top->next;
		free(temp);
	}
}
