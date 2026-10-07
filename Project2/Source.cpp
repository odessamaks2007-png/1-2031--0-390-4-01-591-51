#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Notes
{
	Card* arr;
	int size;
public:
	Notes() : arr(nullptr), size(0) {}
	~Notes()
	{
		delete[] arr;
	}
	void Add(const Card& c)
	{
		Card* temp = new Card[size + 1];
		for (int i = 0; i < size; ++i)
		{
			temp[i] = arr[i];
		}
		temp[size] = c;
		delete[] arr;
		arr = temp;
		size++;
	}
	void ShowAll()
	{
		for (int i = 0; i < size; ++i)
		{
			arr[i].Output();
		}
	}
	void SaveToFile(const string& filename)
	{
		ofstream out(filename);
		if (out.is_open())
		{
			out << size << endl;
			for (int i = 0; i < size; ++i)
			{
				out << arr[i].Name << ' ' << arr[i].Boss << ' ' << arr[i].telNumber << ' ' << arr[i].Adress << ' ' << arr[i].Ispolnitel << endl;
			}
			out.close();
		}
	}
	void LoadFromFile(const string& filename)
	{
		ifstream in(filename);
		if (in.is_open())
		{
			int n;
			in >> n;
			delete[] arr;
			size = 0;
			arr = new Card[n];
			for (int i = 0; i < n; ++i)
			{
				Card c;
				in >> c.Name >> c.Boss >> c.telNumber >> c.Adress >> c.Ispolnitel;
				Add(c);
			}
			in.close();
		}
	}
};

bool isFileEmpty(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		return false; // Или выбросить исключение, если файл не открылся
	}

	file.seekg(0, std::ios::end);
	std::streampos size = file.tellg();

	return size == 0;
}

class Card
{
	int Name;
	int Boss;
	int telNumber;
	int Adress;
	int Ispolnitel;
public:
	void INput()
	{
		cout << "Name of firm..." << endl;
		cin >> Name;
		cout << "Manager..." << endl;
		cin >> Boss;
		cout << "Phone number..." << endl;
		cin >> telNumber;
		cout << "Adress of firm..." << endl;
		cin >> Adress;
		cout << "Contractor..." << endl;
		cin >> Ispolnitel;
	}
	void Output()
	{
		cout << " | " << Name << " | " << Boss << " | " << telNumber << " | " << Adress << " | " << Ispolnitel << endl;
	}
	friend class Notes;
};
int main()
{
	Notes notes;

	Card c;

	c.INput();

	notes.Add(c);

	cout << "\nAll cards:\n";
	notes.ShowAll();

	notes.SaveToFile("cards.txt");

	cout << "\nLoading from file:\n";

	Notes notes2;
	notes2.LoadFromFile("cards.txt");
	notes2.ShowAll();

	return 0;
}
