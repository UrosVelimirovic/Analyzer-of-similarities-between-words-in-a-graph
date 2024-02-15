#ifndef _GRAF_H_
#define _GRAF_H_

#include <iostream>
#include <fstream>
using namespace std;

//Cvorovi na koje pointuju head cvorovi
struct ElemKnot {
	string Name;
	double Weight;
	ElemKnot* next;
	int index;
};
//Cvorovo pocetni
struct ElemHeadRow {
	string KnotName;
	ElemKnot* last;
	ElemKnot* next;
	int index;
};

struct ElemDjk {
	string KnotName;
	double Weight;
	string TKnot;
	bool Visited;
};
struct Pair {
	ElemDjk* Knots;
	int Size;
};
class Graf {
	int NOK;
	int NOB;
	int CNOK;
	int CNOB;
	ElemHeadRow* HeadRow;

public:
	Graf(int NK, int NB) : NOK(NK), NOB(NB) { 
		HeadRow = nullptr;
		CNOK = CNOB = 0;
	}

	void addKnot(const string);
	void rmvKnot(const string);
	void addBranch(const string, const string, const double);
	void rmvBranch(const string, const string);
	Pair INVDijkstra1(const string) const;
	void writeMostSimilar(const int, const string);
	void writeShortestSequence(const string, const string);
	void StronglyConnected(const string);
	friend ostream& operator<<(ostream&, const Graf&);

	~Graf();
};
	
struct ElemSt {
	ElemHeadRow* data;
	ElemSt* next;
};
class Stack {
	ElemSt* top;
private:
	friend class Graf;
	Stack() { top = nullptr; }
	void PUSH(ElemHeadRow*);
	ElemHeadRow* POP();
	bool SEMPTY();
	void WriteStack();
	~Stack();
};
#endif
