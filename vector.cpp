#include <iostream>

using namespace std;

#define MAX_N 50
#define MIN_N 1

bool prim(int x);
bool palindrom(int x);
int oglindit(int x);

int main()
{
	int n;

	cout << "n = ";
	cin >> n;

	if (n < MIN_N || n > MAX_N)
	{
		cout << "Eroare valoare N\n";
		return 1;
	}

	int a[n], i;

	for (i = 0; i < n; i++)
	{
		cout << "a[" << i << "] = ";
		cin >> a[i];
	}
	
	// verific daca toate elementele vectorului a sunt numere prime
	
	bool ok;
	
	for (ok = 1, i = 0; i < n && ok; i++)
	{
		if (!prim(a[i]))
		{
			ok = 0;
		}
	}

	if (ok)
	{
		cout << "Toate elementele vectorului a sunt numere prime.\n";
	}
	else
	{
		cout << "Nu toate elementele vectorului a sunt numere prime.\n";
	}

	// verificati daca exista in vectorul a un palindrom
	
	bool exista;
	
	for (exista = i = 0; i < n && !exista; i++)
	{
		if (palindrom(a[i]))
		{
			exista = 1;
		}
	}

	if (exista)
	{
		cout << "Exista palindrom\n";
	}
	else
	{
		cout << "Nu exista palindrom\n";
	}
	
	// eliminati din vector toate elementele impare
	
	int copie_a[n], copie_n = n;

	for (i = 0; i < n; i++)
	{
		copie_a[i] = a[i];	
	}

	int j;

	for (i = 0; i < n; i++)
	{
		if (a[i] % 2)
		{
			for (j = i; j < n-1; j++)
			{
				a[j] = a[j+1];
			}

			n--, i--;
		}
	}

	cout << "dupa eliminarea elementelor impare, a[] = ";

	for (i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}

	cout << "\n";

	n = copie_n;

	for (i = 0; i < n; i++)
	{
		a[i] = copie_a[i];
	}

	// determinati cea mai lunga secventa formata din elemente egale existenta in vector.
	// afisati lungimea secventei, pozitia de inceput si valoarea care se repeta.	
	
	int lg, lgmax, pozmax, vmax;

	lg = lgmax = 1;
	pozmax = 0;
	vmax = a[pozmax];

	for (i = 1; i < n; i++)
	{
		if (a[i-1] == a[i])
		{
			lg++;
		}
		else
		{
			if (lg > lgmax)
			{
				lgmax = lg;
				pozmax = i-lg;
				vmax = a[pozmax];
			}

			lg = 1;
		}
	}

	if (lg > lgmax)
	{
		lgmax = lg;
		pozmax = n-lg;
		vmax = a[pozmax];
	}

	cout << "Cea mai lunga secventa formata din elemente egale: vmax = " << vmax << ", lgmax = " << lgmax << ", pozmax = " << pozmax << "\n";

	// determinati un element din vector care se repete de cele mai multe ori
	
	int v[n], st, dr, mij, m;
	
	// creez un nou vector v[] care va retine elementele din a[] in ordine crescatoare
	// folosesc cautare binara pentru a determina pozitia lui a[i] in v[]

	v[0] = a[0], m = 1;

	for (i = 1; i < n; i++)
	{	
		st = -1, dr = m;

		while (dr-st > 1)
		{
			mij = st + (dr-st)/2;

			if (a[i] > v[mij])
			{
				st = mij;
			}
			else
			{
				dr = mij;
			}
		}

		m++;

		for (j = m; j > dr; j--)
		{
			v[j] = v[j-1];
		}

		v[dr] = a[i];
	}
	
	// in vectorul sortat crescator v[] caut secventa de lungime maxima
	// valoarea din secv. de lg. maxima reprezinta 
	// numarul care se repeta de cele mai multe ori in a[]

	lg = lgmax = 1;
	pozmax = 0;

	for (i = 1; i < n; i++)
	{
		if (v[i-1] == v[i])
		{
			lg++;
		}
		else
		{
			if (lg > lgmax)
			{
				lgmax = lg;
				pozmax = i-lg;
				vmax = v[pozmax];
			}

			lg = 1;
		}
	}

	if (lg > lgmax)
	{
		lgmax = lg;
		pozmax = n-lg;
		vmax = v[pozmax];
	}

	cout << "Elementul care se repeta de cele mai multe ori in vector este " << vmax << ". Acesta se repeta de " << lgmax << " ori.\n";
	
	return 0;
}

bool prim(int x)
{
	if (x < 2)
	{
		return false;
	}

	if (x == 2)
	{
		return true;
	}

	if (x % 2 == 0)
	{
		return false;
	}

	for (int d = 3; d*d <= x; d += 2)
	{
		if (x % d == 0)
		{
			return false;
		}
	}

	return true;
}

bool palindrom(int x)
{
	if (x == oglindit(x))
	{
		return true;
	}

	return false;
}

int oglindit(int x)
{
	int ogl = 0;

	while (x)
	{
		ogl = ogl*10 + x%10;

		x /= 10;
	}

	return ogl;
}
