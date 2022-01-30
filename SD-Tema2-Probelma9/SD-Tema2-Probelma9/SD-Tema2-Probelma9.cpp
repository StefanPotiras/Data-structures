//complexitatea este O(nlogn)
#include <iostream>
#include<fstream>
#include <queue> 
struct coordonate {
	int x, y;
	void afisare()
	{
		std::cout << x << " " << y;
	}

};
struct NOD {
	coordonate info;
	NOD* next;
};
struct NOD2 {
	coordonate info;
	NOD2* next;
};
struct stiva
{
	NOD2* varf;
	stiva()
	{
		varf = nullptr;
	}
	void PUSH(coordonate val)
	{
		NOD2* newNod = new NOD2;
		newNod->info = val;
		newNod->next = varf;
		varf = newNod;
	}
	void pop()
	{
		NOD2* newNOd;
		if (varf == NULL)
		{
			std::cout << "Stiva este goala!";

		}
		else
		{
			newNOd = varf;
			varf = varf->next;
			delete newNOd;
		}
	}
	coordonate TOP()
	{
		NOD2* nodNou;
		nodNou = varf;
		return nodNou->info;
	}
	bool vid()
	{
		if (varf == nullptr)
			return 1;
		else
			return 0;
	}
};
struct coada {
	NOD* varf;
	NOD* sfarsit;
	coada()
	{
		sfarsit = nullptr;
		varf = nullptr;
	}
	NOD* newNode(coordonate data) {
		if (data.x != NULL && data.y != NULL)
		{
			NOD* nodNou = new NOD();
			nodNou->info = data;
			nodNou->next = NULL;
			return nodNou;
		}
	}
	void PUSH(coordonate x)
	{
		NOD* c = newNode(x);
		if (sfarsit != NULL)
		{
			sfarsit->next = c;
		}
		sfarsit = c;
		if (varf == NULL)
			varf = c;

	}
	void POP()
	{
		NOD* c;
		if (varf == NULL)
			std::cout << "Coada nu mai are elemente!";
		else
		{
			c = varf;
			varf = varf->next;
			delete c;
		}
	}
	void afiseazaCoadaVa()
	{
		NOD* c;
		c = varf;
		while (c)
		{
			std::cout << c->info.x << " " << c->info.y << std::endl;
			c = c->next;
		}
	}
	int VID()
	{
		if (!varf)
			return 1;
		else
			return 0;
	}
	coada maresteCoord()
	{
		coada rez;
		rez.varf->info.x = varf->info.x + 1;
		rez.varf->info.y = varf->info.y + 1;
		return rez;
	}

};
void red() {
	printf("\033[1;31m");
}

void reset() {
	printf("\033[0m");
}
int** alocareDinamica(int& randuri, int& coloane)
{
	std::ifstream fin("in.txt");
	fin >> randuri;
	fin >> coloane;
	randuri = randuri + 2;
	coloane = coloane + 2;
	int** matriceDinamica = new int* [randuri];
	for (int i = 0; i < randuri; i++)
	{
		matriceDinamica[i] = new int[coloane];
	}
	return matriceDinamica;
}
void citireMatrice(int** labirint, int randuri, int coloane)
{
	int x, y;
	std::ifstream fin("in.txt");
	fin >> x >> y;
	for (int i = 0; i < randuri - 2; i++)
	{
		for (int j = 0; j < coloane - 2; j++)
		{
			fin >> labirint[i][j];
		}
	}
}
void afisareMatrice(int** labirint, int randuri, int coloane)
{

	for (int i = 0; i < randuri - 2; i++)
	{
		for (int j = 0; j < coloane - 2; j++)
		{
			std::cout << labirint[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
void citirePozitieSoricel(int** matrice, coordonate& soricel)
{
	std::cout << "Introdu coordonatele soricelului!" << std::endl;
	std::cout << "X=";
	std::cin >> soricel.x;
	std::cout << "Y=";
	std::cin >> soricel.y;
	if (matrice[soricel.x][soricel.y] == -1)
	{
		std::cout << "Coordonatele introduse nu sunt corecte!";
		citirePozitieSoricel(matrice, soricel);
	}
}
void citirePozitieBranza(int** matrice, coordonate& branza)
{
	std::cout << "Introdu coordonatele branzei!" << std::endl;
	std::cout << "X=";
	std::cin >> branza.x;
	std::cout << "Y=";
	std::cin >> branza.y;
	if (matrice[branza.x][branza.y] == -1)
	{
		std::cout << "Coordonatele introduse nu sunt corecte!";
		citirePozitieSoricel(matrice, branza);
	}
}
void inconjoaraMatricea(int**& matrice, int& randuri, int& coloane)
{

	for (int i = 0; i < randuri - 1; i++)
	{
		for (int j = coloane - 2; j >= 0; j--)
		{
			matrice[i][j + 1] = matrice[i][j];
		}
	}
	for (int j = 0; j < coloane - 1; j++)
	{
		for (int i = randuri - 2; i >= 0; i--)
		{
			matrice[i + 1][j] = matrice[i][j];
		}
	}
	for (int i = 0; i < coloane; i++)
	{
		matrice[0][i] = matrice[randuri - 1][i] = -1;
	}
	for (int i = 0; i < randuri; i++)
	{
		matrice[i][0] = matrice[i][coloane - 1] = -1;
	}

}
void afisareMatriceBordata(int** labirint, int  randuri, int coloane)
{
	for (int i = 0; i < randuri; i++)
	{
		for (int j = 0; j < coloane; j++)
		{
			if (labirint[i][j] == -1)
				std::cout << labirint[i][j];
			else
				std::cout << " " << labirint[i][j];
		}
		std::cout << std::endl;
	}
}
void marcheazaDrumul(int**& labirint, coordonate pozitie, coada& parcurgere)
{
	int x[4] = { -1,0,1,0 }, y[4] = { 0,1,0,-1 };
	for (int i = 0; i < 4; i++)
	{
		coordonate temp;
		temp.x = pozitie.x + x[i];
		temp.y = pozitie.y + y[i];
		if (labirint[temp.x][temp.y] == 0)
		{
			labirint[temp.x][temp.y] = labirint[pozitie.x][pozitie.y] + 1;
			parcurgere.PUSH(temp);
		}
	}
}
void completareMatrice(int**& labirint, coordonate soricel, coordonate branza)
{
	
	coada parcurgere;
	parcurgere.PUSH(soricel);
	labirint[soricel.x][soricel.y] = 1;
	while (!parcurgere.VID() && labirint[branza.x][branza.y] == 0)
	{
		coordonate pozitie; 
		pozitie = parcurgere.varf->info;
		parcurgere.POP();
		marcheazaDrumul(labirint, pozitie, parcurgere);
	}
}
void aflareDrumOptim(int** labirint, coordonate branza, stiva& drum, int& nrElemente)
{
	int x[4] = { -1,0,1,0 }, y[4] = { 0,1,0,-1 };
	coordonate pozitie = branza;

	drum.PUSH(branza);
	while (labirint[pozitie.x][pozitie.y] > 1)
	{
		for (int i = 0; i < 4; i++)
		{
			coordonate temp;
			temp.x = pozitie.x + x[i];
			temp.y = pozitie.y + y[i];
			if (labirint[temp.x][temp.y] == labirint[pozitie.x][pozitie.y] - 1)
			{
				drum.PUSH(temp);
				pozitie = temp;
				nrElemente++;
				break;
			}
		}
	}
}
void formareVectorDrum(stiva drum, coordonate*& vector, int& nrElemente)
{
	int i = 0;
	vector = new coordonate[nrElemente];
	while (drum.vid() != 1)
	{
		vector[i] = drum.varf->info;
		i++;
		drum.pop();
	}
	for (int i = 0; i < nrElemente; i++)
	{
		vector[i].afisare();
		std::cout << std::endl;
	}
}
int verificaDrum(coordonate* vector, coordonate var, int nrElemente)
{
	int ok = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].x == var.x && vector[i].y == var.y)
		{
			ok = 1;
			break;
		}
	}
	return ok;
}
void afisareDrumMatrice(stiva drum, coordonate* vector, int nrElemente, int** labirint, int randuri, int coloane)
{
	coordonate var;
	for (int i = 0; i < randuri; i++)
	{
		for (int y = 0; y < coloane; y++)
		{
			var.x = i;
			var.y = y;
			if (labirint[i][y] == -1)
			{
				printf("|%d", labirint[i][y]);
			}
			else if (0 <= labirint[i][y] && labirint[i][y] < 10 && verificaDrum(vector, var, nrElemente) == 1)
			{
				red();
				printf("| %d", labirint[i][y]);
				reset();
			}
			else if (10 <= labirint[i][y] && verificaDrum(vector, var, nrElemente) == 1)
			{
				red();
				printf("|%d", labirint[i][y]);
				reset();
			}
			else if (0 <= labirint[i][y] && labirint[i][y] < 10 && verificaDrum(vector, var, nrElemente) != 1)
			{
				std::cout << "|" << " " << labirint[i][y];
			}
			else if (10 <= labirint[i][y] && verificaDrum(vector, var, nrElemente) != 1)
			{
				std::cout << "|" << labirint[i][y];
			}
		}
		std::cout << std::endl;

	}
}
int main()
{
	stiva drum;
	coordonate soricel, branza, * vector;
	int** matrice, randuri, coloane, nrElemente = 1;
	matrice = alocareDinamica(randuri, coloane);
	citireMatrice(matrice, randuri, coloane);
	afisareMatrice(matrice, randuri, coloane);
	citirePozitieSoricel(matrice, soricel);
	citirePozitieBranza(matrice, branza);
	soricel.afisare();
	branza.afisare();
	std::cout << std::endl;
	inconjoaraMatricea(matrice, randuri, coloane);
	afisareMatriceBordata(matrice, randuri, coloane);
	completareMatrice(matrice, soricel, branza);
	aflareDrumOptim(matrice, branza, drum, nrElemente);
	formareVectorDrum(drum, vector, nrElemente);
	afisareDrumMatrice(drum, vector, nrElemente, matrice, randuri, coloane);
}

