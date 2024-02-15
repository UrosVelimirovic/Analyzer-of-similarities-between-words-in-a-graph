#include"Graf.h"
int main()
{

	string F;
	cout << "Unesite ime fajla sa ekstenzijom .txt" << endl;
	cin >> F;
	ifstream MyFile(F);
	if (!MyFile.is_open())
	{
		cout << "FAJL NIJE OTVOREN" << endl;
		return 0;
	}
	int NOK;
	int NOB;
	MyFile >> NOK;
	MyFile >> NOB;

	Graf A(NOK, NOB);

	string HelpingString;
	for (int i = 0; i < NOK; i++) {
		MyFile >> HelpingString;
		A.addKnot(HelpingString);
	}

	for (int i = 0; i < NOB; i++) {
		string K1, K2;
		double W;
		MyFile >> K1 >> K2 >> W;
		A.addBranch(K1, K2, W);
	}

	int select = -3;
	string K1;
	string K2;
	double W;
	int k;
	bool kraj = false;
	while (!kraj)
	{
		cout << "Izaberite zeljenu operaciju brojem: " << endl;
		cout << "1. Dodaj cvor u graf" << endl;
		cout << "2. Ukloni cvor iz grafa" << endl;
		cout << "3. Dodaj granu u graf" << endl;
		cout << "4. Ukloni granu iz grafa" << endl;
		cout << "5. Ispisi graf" << endl;
		cout << "6. Obrisi Graf iz memorije" << endl;
		cout << "7. Nadji k semanticki najslicnijih reci zadatoj reci" << endl;
		cout << "8. Ispis svih reci na najkracem putu od zadate jedne reci do zadate druge reci" << endl;
		cout << "9. Nalazenje svih reci koje su jako povezane sa zadatom recju" << endl;
		cout << "0. Zavrsi program" << endl;
		cin >> select;
		switch (select) {
		case 0: 
			kraj = true;
			break;
		case 1:
			cout << "Unesite ime cvora: " << endl;
			cin >> K1;
			A.addKnot(K1);
			break;
		case 2:
			cout << "Unesite ime cvora: " << endl;
			cin >> K1;
			A.rmvKnot(K1);
			break;
		case 3:
			cout << "Unesite ime Cvora 1:" << endl;
			cin >> K1;
			cout << "Unesite ime Cvora 2:" << endl;
			cin >> K2;
			cout << "Unesite tezinu grane:" << endl;
			cin >> W;
			A.addBranch(K1, K2, W);
			break;
		case 4:
			cout << "Unesite ime Cvora 1:" << endl;
			cin >> K1;
			cout << "Unesite ime Cvora 2:" << endl;
			cin >> K2;
			A.rmvBranch(K1, K2);
			break;
		case 5:
			cout << A << endl;
			break;
		case 6:
			return 0;
			break;
		case 7:
			cout << "Unesite k:" << endl;
			cin >> k;
			cout << "Unesite cvor:" << endl;
			cin >> K1;
			A.writeMostSimilar(k, K1);
			break;
		case 8:
			cout << "Unesite ime Cvora 1:" << endl;
			cin >> K1;
			cout << "Unesite ime Cvora 2:" << endl;
			cin >> K2;
			A.writeShortestSequence(K1, K2);
			break;
		case 9:
			cout << "Unesite ime cvora:" << endl;
			cin >> K1;
			A.StronglyConnected(K1);
			cout << endl;
			break;
		default:
			cout << "POGRESAN UNOS" << endl;
			break;
		}
		cout << endl;
	}
	return 0;
} 