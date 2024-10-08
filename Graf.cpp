#include "Graf.h"


void Graf::addKnot(const string name1) {
	
	ElemHeadRow* temp = new ElemHeadRow[CNOK + 1];
	for (int i = 0; i < CNOK; i++)
		temp[i] = HeadRow[i];
	delete[] HeadRow;
	HeadRow = temp;
	HeadRow[CNOK].KnotName = name1;
	HeadRow[CNOK].next = nullptr;
	HeadRow[CNOK].index = CNOK;
	CNOK++;
}

void Graf::rmvKnot(const string name1) {
	bool KFound = false;
	int i = 0;
	while (i < CNOK && !KFound)
	{
		if (HeadRow[i].KnotName == name1)
			KFound = true;
		else i++;
	}
	if (KFound) {
		ElemKnot* privremeni = HeadRow[i].next;
		while (privremeni)
		{
			privremeni = privremeni->next;
			free(HeadRow[i].next);
			HeadRow[i].next = privremeni;
		}
		for (int a = i; a < CNOK - 1; a++) {
			HeadRow[a] = HeadRow[a + 1];
		}
		CNOK--;
	/*	ElemHeadRow* temp = new ElemHeadRow[CNOK];
		for (int i = 0; i < CNOK; i++)
			temp[i] = HeadRow[i];
		delete[] HeadRow;
		HeadRow = temp;
		*/
		for (int i = 0; i < CNOK; i++) {
			rmvBranch(HeadRow[i].KnotName, name1);
		}
	}
	else cout << "POGRESAN NAZIV CVORA" << endl;
}

void Graf::addBranch(const string K1, const string K2, const double W){
	bool KFound = false;
	int IKnot = -2;
	int K1Knot = 0;
	for(int i = 0; i< CNOK; i ++)
	{
		if (HeadRow[i].KnotName == K1 && !KFound) {
			KFound = true;
			K1Knot = i;
		}
		if (HeadRow[i].KnotName == K2) IKnot = i;
		if (KFound && IKnot != -2) break;
	}
	
	if (KFound && IKnot != -2) {
		ElemKnot* novi = new ElemKnot;
		novi->Name = K2;
		novi->Weight = W;
		novi->next = nullptr;
		HeadRow[K1Knot].last = (HeadRow[K1Knot].next == nullptr ? HeadRow[K1Knot].next : HeadRow[K1Knot].last->next) = novi;
		HeadRow[K1Knot].last->index = IKnot;
		CNOB++;
	}
	else cout << "POGRESAN NAZIV CVORA" << endl;
}

void Graf::rmvBranch(const string K1, const string K2) {
	bool HFound = false;
	int i = 0;
	for (i = 0; i < CNOK; i++)
	{
		if (HeadRow[i].KnotName == K1 && !HFound) {
			HFound = true;
			break;
		}
		
	}
	if (HFound) {
		ElemKnot* temp;
		ElemKnot* beftemp;
		beftemp = nullptr;
		temp = HeadRow[i].next;
		bool Kfound = false;
		while (temp && !Kfound)
		{
			if (temp->Name == K2)
			{
				if (!beftemp) {
					HeadRow[i].next = temp->next;
					free(temp);
				}
				else {
					beftemp->next = temp->next;
					free(temp);
				}
				Kfound = true;
				CNOB--;
			}
			else {
				beftemp = temp;
				temp = temp->next;
			}
		}
	}
	else cout << "POGRESAN NAZIV CVORA" << endl;	
}

ostream& operator<<(ostream& os, const Graf& graf1) {
	ElemKnot* privremeni = nullptr;
	for (int i = 0; i < graf1.CNOK; i++)
	{
		privremeni = graf1.HeadRow[i].next;
		os << graf1.HeadRow[i].KnotName;
		while (privremeni)
		{
			os << " -> ";
			os << privremeni->Name << "(" << privremeni->Weight << ")";
			privremeni = privremeni->next;
		}
		os << endl;
	}
	return os;
}

void Graf::writeMostSimilar(const int k, const string K1) {
	bool HFound = false;
	for (int i = 0; i < CNOK; i++)
	{
		if (HeadRow[i].KnotName == K1) {
			HFound = true;
			break;
		}
	}
	if (HFound) {
		Pair pair = INVDijkstra1(K1);
		int k1 = (k >= pair.Size-1) ? pair.Size-1 : k;
		for (int i = 1; i <= k1; i++)//Ispis
		{
			if (pair.Knots[i].Weight)
				cout << pair.Knots[i].KnotName << " ";
		}
		cout << endl;
		delete[] pair.Knots;
	}
	else cout << "POGRESAN NAZIV CVORA" << endl;
}

void Graf::writeShortestSequence(const string K1, const string K2) {
	bool HFound = false;
	bool H2Found = false;
	for (int i = 0; i < CNOK; i++)
	{
		if (HeadRow[i].KnotName == K1) HFound = true;
		if (HeadRow[i].KnotName == K2) H2Found = true;
		if (HFound && H2Found) break;
	}
	if (HFound && H2Found) {
		Pair pair = INVDijkstra1(K1);

		string* head = new string[pair.Size];
		string CS = K2; // current string

		ElemDjk* temp = nullptr;

		int i = 0;
		head[i] = CS;
		i++;
		while (CS != K1) {
			for (int i = 0; i < pair.Size; i++) {
				if (pair.Knots[i].KnotName == CS) {
					temp = &pair.Knots[i];
					break;
				}
			}
			if (temp == nullptr) {
				delete[]pair.Knots;
				delete[]head;
				return;
			}
			CS = temp->TKnot;
			head[i] = CS;
			i++;
		}

		//Ispis
		for (int j = i - 1; j >= 0; j--) {
			cout << head[j];
			if (j) {
				for (int a = 0; a < CNOK; a++) {
					if (HeadRow[a].KnotName == head[j]) {
						ElemKnot* temp = HeadRow[a].next;
						while (temp) {
							if (temp->Name == head[j - 1])
								cout << " -" << "(" << temp->Weight << ")" << "->";
							temp = temp->next;
						}
					}
				}
			}
			else cout << endl;
		}
		delete[]pair.Knots;
		delete[]head;
	}
	else cout << "POGRESAN NAZIV CVORA" << endl;
}
Pair Graf::INVDijkstra1(const string K1) const {
	ElemDjk* Knots = new ElemDjk[CNOK];
	int KS = 0; //Knot Select
	for (int i = 0; i < CNOK; i++) {
		Knots[i].KnotName = HeadRow[i].KnotName;
		if (Knots[i].KnotName == K1) {
			KS = i;
			Knots[i].Weight = 1;
			Knots[i].TKnot = K1;
		}
		else Knots[i].Weight = 0;
		Knots[i].Visited = false;
		Knots[i].TKnot = "NoName";
	}

	for (int i = 0; i < CNOK; i++)
	{
		if(i) //find Knot With largest current weight path
		{
			for (int j = 0; j < CNOK; j++) {
				if (!Knots[j].Visited ) {
					KS = j;
					break;
				}
			}
			for (int j = KS; j < CNOK; j++) {
				if (Knots[j].Weight > Knots[KS].Weight && !Knots[j].Visited) {
					KS = j;
				}
			}
			//if (!KS) break;
		}
	
		Knots[KS].Visited = true;
		ElemKnot* temp = HeadRow[KS].next;
		while (temp)
		{
			if (Knots[KS].Weight * temp->Weight > Knots[temp->index].Weight) {
				Knots[temp->index].Weight = Knots[KS].Weight * temp->Weight;
				Knots[temp->index].TKnot = Knots[KS].KnotName;
			}
			temp = temp->next;
		}
	}
	ElemDjk* Knots2= new ElemDjk[CNOK];//Knots with no zeros
	int i2 = 0;
	for (int i = 0; i < CNOK; i++){
		if (Knots[i].Weight != 0){
			Knots2[i2] = Knots[i];
			i2++;
		}
	}
	delete[] Knots;
	Knots = Knots2;
	//sorting Dijkstra
	for (int i = 0; i < i2; i++) {
		for (int j = i + 1; j < i2; j++) {
			if (Knots[i].Weight < Knots[j].Weight)
			{
				ElemDjk temp1 = Knots[j];
				Knots[j] = Knots[i];
				Knots[i] = temp1;
			}
		}
	}
	Pair pair;
	pair.Knots = Knots;
	pair.Size = i2;
	return pair;

}
void Graf::StronglyConnected(const string start) {
	bool* visitDFS = new bool[CNOK]{0};
	bool* visitKSRJ = new bool[CNOK] {0};
	Stack DFS;//Depth First Search
	Stack DFSHelp;
	Stack KSRJ;
	
	//DFS
	for (int i = 0; i < CNOK; i++){
		if (HeadRow[i].KnotName == start) {
			DFS.PUSH(&HeadRow[i]);
			break;
		}
	}
	if (DFS.SEMPTY()) {
		cout << "POGRESAN NAZIV CVORA" << endl;
		return;
	}
	ElemHeadRow* Current = nullptr;
	while (!DFS.SEMPTY()) {
		Current = DFS.POP();
		if (!visitDFS[Current->index]) {
			visitDFS[Current->index] = true;
			DFSHelp.PUSH(Current);
			ElemKnot* temp = Current->next;
			bool SATS = false;//Something Added To Stack
			while (temp)
			{
				if (!visitDFS[HeadRow[temp->index].index]) {
					DFS.PUSH(&HeadRow[temp->index]);
					SATS = true;
				}
				temp = temp->next;
			}
			if (!SATS) {
				bool CTNF = false;
				while (!CTNF) {
					KSRJ.PUSH(DFSHelp.POP());
					if (DFSHelp.SEMPTY()) break;
					temp = DFSHelp.top->data->next;
					while (temp)
					{
						if (!visitDFS[HeadRow[temp->index].index]) {
							CTNF = true;
						}
						temp = temp->next;
					}
				}
			}
		}
	}
	for (int i = 0; i < CNOK; i++)
		if (!visitDFS[i]) visitKSRJ[i] = true;

	//Transposing Graph
	Graf TG(this->NOK, this->NOB);
	for (int i = 0; i < CNOK; i++) {
		TG.addKnot(HeadRow[i].KnotName);
	}
	for (int i = 0; i < CNOK; i++) {
		ElemKnot* temp = HeadRow[i].next;
		while (temp)
		{
			TG.addBranch(temp->Name, HeadRow[i].KnotName, temp->Weight);
			temp = temp->next;
		}
	}
	//DFS through Transposed graph
	string* SC = new string[CNOK]; // Strongly Connected
	int SCCounter = 0;
	DFS.PUSH(&TG.HeadRow[KSRJ.POP()->index]);
	while (!DFS.SEMPTY())
	{
		Current = DFS.POP();
		if (!visitKSRJ[Current->index]) 
		{
			visitKSRJ[Current->index] = true;
			SC[SCCounter] = Current->KnotName;
			SCCounter++;
			ElemKnot* temp = Current->next;
			while (temp)
			{
				if (!visitKSRJ[TG.HeadRow[temp->index].index]) {
					DFS.PUSH(&TG.HeadRow[temp->index]);
				}
				temp = temp->next;
			}
		}
	}

	for (int i = 0; i < SCCounter; i++) {
		cout << SC[i] << " ";
	}
	delete[] SC;
	delete[] visitDFS;
	delete[] visitKSRJ;
}

Graf::~Graf() {
	ElemKnot* privremeni = nullptr;
	for (int i = 0; i < CNOK; i++)
	{
		privremeni = HeadRow[i].next;
		while (privremeni)
		{
			privremeni = privremeni->next;
			free(HeadRow[i].next);
			HeadRow[i].next = privremeni;
		}
	}
	delete[] HeadRow;
}