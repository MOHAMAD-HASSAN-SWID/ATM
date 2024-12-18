
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct castomar 
{
	string accont_number;
	string pin_cod;
	string name;
	string phone_number;
	string balenc;
};

vector <string> file_to_data(string name_file)
{
	string line;
	vector <string> data_castomar;
	fstream red_file;
	red_file.open(name_file, ios::in);
	if (red_file.is_open())
	{
		while (getline(red_file, line))
		{
			data_castomar.push_back(line);
		}
		red_file.close();
	}
	return data_castomar;
}

vector <string> data_one_line_to_data_lins(string data, string space = "*//*")
{
	vector <string> data_lins;

	int l = 0, r;
	while ((r = data.find(space, l)) != data.npos)
	{
		data_lins.push_back(data.substr(l, r - l));
		l = r + 4;
	}
	
	data_lins.push_back(data.substr(l, r - l));
	
	return data_lins;
}

castomar data_to_struct_information_castomar(vector <string> data_lins)
{
	castomar recall;
	recall.accont_number = data_lins[0];
	recall.pin_cod = data_lins[1];
	recall.name = data_lins[2];
	recall.phone_number = data_lins[3];
	recall.balenc = data_lins[4];

	return recall;
}

vector <castomar> data_to_information_castomar(vector <string> data)
{
	vector <string> data_lins;
	vector <castomar> information_castomar;
	for (int i = 0; i < data.size(); i++)
	{
		data_lins = data_one_line_to_data_lins(data[i]);
		information_castomar.push_back(data_to_struct_information_castomar(data_lins));
	}

	return information_castomar;
}

vector <string> information_to_data_castomar(vector <castomar> information , string space = "*//*")
{
	string line;
	vector <string> data_castomar;
	for (int i = 0; i < information.size(); i++)
	{
		line += information[i].accont_number + space + information[i].pin_cod + space + information[i].name
			+ space + information[i].phone_number + space + information[i].balenc;
		data_castomar.push_back(line);
	}
	return data_castomar;
}

void data_castomars_to_file(string name , vector <string> data_castomar)
{
	fstream write;
	write.open(name, ios::out);
	if (write.is_open())
	{
		while (data_castomar.size() != 0)
		{
			write << data_castomar.back() << endl;
			data_castomar.pop_back();
		}
		write.close();
	}
}

int search_information_castomar(vector <castomar> information_castomar , string search)
{
	for (int i = 0; i < information_castomar.size(); i++)
	{
		if (search == information_castomar[i].accont_number)
			return i;
	}
	return -1;
}

int login( vector <castomar> information_castomar)
{
	system("cls");
	string accont_number , pin_code;
	cout << "***************************\n\tlogin\n***************************\n";
	cout << "\t enter accont number : ";
	cin >> accont_number;

	int i = search_information_castomar(information_castomar, accont_number);

	if (i != -1)
	{
		cout << "\tenter your pin cod : ";
		cin >> accont_number;
		if (accont_number == information_castomar[i].pin_cod)
			return i;
	}
	return -1;
}

void opration_balnce(int baln , castomar & information)
{
	long long  information_balanc = stoi(information.balenc);
		
	information_balanc += baln;

	information.balenc = to_string(information_balanc);
}

void Quick_whithdraw(castomar& information)
{
	system("cls");
	int start_quick;
	int balnc[] = { 20,50,100,200,500,1000,1500,2000 };
	cout << "********************************\n"
		<< "\t quick whithdraw \n"
		<< "********************************\n";

	cout << "\t [1] 20 ";
	cout << "\t [2] 50 \n";
	cout << "\t [3] 100 ";
	cout << "\t [4] 200 \n";
	cout << "\t [5] 500 ";
	cout << "\t [6] 1000 \n";
	cout << "\t [7] 1500 ";
	cout << "\t [8] 2000 \n";

	cout << "************************************\n"
		<< "enter number : ";
	cin >> start_quick;
	if (cin.fail())
	{
		cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "you should input just number...\n";
		system("pause > 0");
		return;
	}
	opration_balnce(balnc[start_quick -1], information);
}

void normal_whithdraw(castomar& information, bool ne = 0)
{
	system("cls");
	int  baln;
	
	cout << "enter your whithdraw : ";
	cin >> baln;
	if (cin.fail())
	{
		cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "you should input just number...\n";
		system("pause > 0");
		return;
	}
	if (ne)
		baln *= -1;

	while (stoi(information.balenc) + baln < 0)
	{
		cout << "you can not do this opration..";
		cin >> baln;
		
		if (cin.fail())
		{
			cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "you should input just number...\n";
			system("pause > 0");
			return;
		}

		if (ne)
			baln *= -1;
	}
	opration_balnce(baln, information);
}

void show_information(castomar &information)
{
	system("cls");
	cout << "\t------------- inforamtion --------------\n"
		<< "\tAccont number : " << information.accont_number << "\n"
		<< "\tpin code : " << information.pin_cod << "\n"
		<< "\tname : " << information.name << "\n"
		<< "\tphone number : " << information.phone_number << "\n"
		<< "\tbalnc : " << information.balenc << "\n"
		<< "\t----------------------------------------\n";

}

void testcase(int start, castomar &information)
{
	if (start == 1)
		Quick_whithdraw(information);
	else if (start == 2)
		normal_whithdraw(information);
	else if (start == 3)
		normal_whithdraw(information, 1);
	else if (start == 4)
		show_information(information);

}

void menue(int & start , castomar &information)
{
	system("cls");
	cout << "==========================================\n"
		<< "\t\tATM menue\n"
		<< "==========================================\n";
	cout << "\t [1] Quick withdraw\n";
	cout << "\t [2] normal withdraw\n";
	cout << "\t [3] dipsort\n";
	cout << "\t [4] check balnce\n";
	cout << "\t [5] logout\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "enter number...";
	
	cin >> start;
	if (cin.fail())
	{
		cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "you should input just number...\n";
		system("pause > 0");
		start = 6;
	}
	testcase(start, information);

}

int main()
{
	vector <string> data_castomar = file_to_data("hassan.txt");

	vector <castomar> information_castomar = data_to_information_castomar(data_castomar);
	
	do
	{
		int start = 0;
		int i = login(information_castomar);
		while (i == -1)
		{
			cout << "\n\n\ttry agine this user dont find....\n\t enter any key...";
			system("pause > 0");
			i = login(information_castomar);
		}
		
		while (start < 5)
		{
			menue(start , information_castomar[i]);
			cout << "\t enter any key...";
			system("pause > 0");
		} 

		data_castomar = information_to_data_castomar(information_castomar);
		data_castomars_to_file("hassan.txt" , data_castomar);
	} while (1);
	 


	cout << "\t enter any key...";
	system("pause > 0");
}

