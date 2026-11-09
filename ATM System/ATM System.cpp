# include<iostream>
# include<string>
# include<vector>
# include<fstream>
using namespace std;


const string ClientFileName = "Client.txt";

enum enChoiceFromMainMenueScreen { QuickWithdraw = 1, NormalWithdraw = 2, Deposite = 3, CheckBalance = 4, Logout = 5 };

enum enQuickWithdraw {
	TwentyWithdraw = 1, FiftyWithdraw = 2, OneHandredWithdraw = 3
	, TwoHanderedWithdraw = 4, FourHanderedWithdraw = 5, SixHanderedWithdraw = 6, EightHanderedWithdraw = 7
	, OneThousandWithdraw = 8, Exit = 9
};

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	int AccountBalance;
	bool MarkToDelete = false;

};

stClient CurrentClient;
vector <string> SeparatDataLineInVector(string S, string Seperater) {

	vector<string>Vstring;

	short pos = 0;
	string sWord = "";

	while ((pos = S.find(Seperater)) != string::npos) {

		sWord = S.substr(0, pos);

		if (sWord != "") {

			Vstring.push_back(sWord);
		}
		S.erase(0, pos + Seperater.length());
	}
	if (S != "") {

		Vstring.push_back(S);
	}
	return Vstring;

}
stClient PutDataLineInStruct(string Line) {

	vector <string> Vstring;
	stClient Client;

	Vstring = SeparatDataLineInVector(Line, "#//#");

	Client.AccountNumber = Vstring[0];
	Client.PinCode = Vstring[1];
	Client.Name = Vstring[2];
	Client.Phone = Vstring[3];
	Client.AccountBalance = stoi(Vstring[4]);

	return Client;

}
vector <stClient> LoadClientDataFromfile(string ClientFileName) {

	vector <stClient> VClient;

	fstream MyFile;

	MyFile.open(ClientFileName, ios::in);

	if (MyFile.is_open()) {

		string Line;
		stClient Client;

		while (getline(MyFile, Line)) {

			Client = PutDataLineInStruct(Line);

			VClient.push_back(Client);


		}
		MyFile.close();
	}

	return VClient;

}
string ConvertClientDataToStringLine(stClient Client, string Seprator = "#//#") {

	string S = "";

	S += Client.AccountNumber + Seprator;
	S += Client.PinCode + Seprator;
	S += Client.Name + Seprator;
	S += Client.Phone + Seprator;
	S += to_string(Client.AccountBalance);

	return S;

}

vector <stClient> RepatePutClientsDataLineInFileAfterDeleteOrUpdateClient(string ClientFileName, vector<stClient>& VClients) {

	fstream MyFile;

	MyFile.open(ClientFileName, ios::out);

	if (MyFile.is_open()) {

		for (stClient& S : VClients) {

			if (S.MarkToDelete == false) {

				string DataLine = ConvertClientDataToStringLine(S);
				MyFile << DataLine << endl;

			}
		}

		MyFile.close();

	}

	return VClients;

}


void PrintMainMenueScreen();

void PrintTheMenue() {

	cout << "==================================================\n";
	cout << "               ATM Main Menue Screen         \n";
	cout << "==================================================\n";
	cout << "       [1] Quick Withdraw.       \n";
	cout << "       [2] Normal Withdraw.      \n";
	cout << "       [3] Deposite.             \n";
	cout << "       [4] Check Balance.        \n";
	cout << "       [5] Logout.               \n";
	cout << "================================================\n";
}

enChoiceFromMainMenueScreen  ConvertChoiceToEnum(short ChoiceNumber) {

	return enChoiceFromMainMenueScreen(ChoiceNumber);
}

void ReturnToMainScreen() {

	cout << "\n\nPress any key to go back to main Menue....";
	system("pause>0");
	PrintMainMenueScreen();
}
void Login();

void IfTheClientchoiceLogout() {

	system("cls");
	Login();
}
void PrintWordCheckBalanceScreen() {

	cout << "=======================================\n";
	cout << "         Check Balance Screen\n";
	cout << "=======================================\n";

}

void IfTheClientchoiceCheckHisBalance() {

	PrintWordCheckBalanceScreen();

	vector<stClient> VClients = LoadClientDataFromfile(ClientFileName);
	for (stClient& C : VClients) {

		if (C.AccountNumber == CurrentClient.AccountNumber) {

			cout << " Your Balance is " << C.AccountBalance << endl;
		}
	}

}
void PrintWordDepositeScreen() {

	cout << "=======================================\n";
	cout << "            Deposite Screen\n";
	cout << "=======================================\n";

}
int ReadAmountToDeposite() {

	int Amount;
	do {

		cout << "\n\n Enter a positive Deposite amount ? ";
		cin >> Amount;


	} while (Amount < 1);

	return Amount;



}
bool DepositeOrWithdrawAmountFromBalanceClient(vector<stClient>VClients, int Amount) {

	char Answer = 'n';
	cout << "Are you sure you want to Perform this transAction? y/n ? ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y') {

		for (stClient& C : VClients) {


			if (C.AccountNumber == CurrentClient.AccountNumber) {

				C.AccountBalance += Amount;
				RepatePutClientsDataLineInFileAfterDeleteOrUpdateClient(ClientFileName, VClients);
				cout << "Done Successfuly, New Balance is " << C.AccountBalance;

				return true;
			}
		}

	}
	return false;
}

void IfTheClientchoiceDeposite() {

	PrintWordDepositeScreen();

	int Amount = ReadAmountToDeposite();
	vector<stClient>VClients = LoadClientDataFromfile(ClientFileName);

	DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount);
}
short ReadNumberAmountToWithdrawInQuickWithdraw() {

	short Choice;
	do {
		cout << "\n Chosse what to withdraw from [1] to [8] ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 9);

	return Choice;
}
enQuickWithdraw convertChoiceToWithdrawEnum(short Choice) {

	return enQuickWithdraw(Choice);
}

void PrintMainMenueScreen();
void ChoiceTheAmountThatwillWithdrawBYUseQuickWithdraw() {

	vector<stClient>VClients = LoadClientDataFromfile(ClientFileName);
	for (stClient& C : VClients) {


		if (C.AccountNumber == CurrentClient.AccountNumber) {
			cout << " Your Balance is : " << C.AccountBalance << endl;
		}
	}
	short Choice = ReadNumberAmountToWithdrawInQuickWithdraw();

	convertChoiceToWithdrawEnum(Choice);
	int Amount;
	switch (Choice) {

	case enQuickWithdraw::TwentyWithdraw:
	{
		Amount = 20;
		DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount * -1);
		ReturnToMainScreen();
	}

	case enQuickWithdraw::FiftyWithdraw:
	{

		Amount = 50;
		DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount * -1);
		ReturnToMainScreen();
	}

	case enQuickWithdraw::OneHandredWithdraw:
	{

		Amount = 100;
		DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount * -1);
		ReturnToMainScreen();
	}

	case enQuickWithdraw::TwoHanderedWithdraw:
	{
		Amount = 200;
		DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount * -1);
		ReturnToMainScreen();

	}

	case enQuickWithdraw::FourHanderedWithdraw:
	{

		Amount = 400;
		DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount * -1);
		ReturnToMainScreen();
	}

	case enQuickWithdraw::SixHanderedWithdraw:
	{

		Amount = 600;
		DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount * -1);
		ReturnToMainScreen();
	}

	case enQuickWithdraw::EightHanderedWithdraw:
	{

		Amount = 800;
		DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount * -1);
		ReturnToMainScreen();
	}
	case enQuickWithdraw::OneThousandWithdraw:
	{
		Amount = 1000;
		DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount * -1);
		ReturnToMainScreen();

	}

	case enQuickWithdraw::Exit:
	{

		PrintMainMenueScreen();

	}


	}


}

void PrintTheQuickWithdrawScreen() {

	cout << "=========================================\n";
	cout << "              Quick Withdraw\n";
	cout << "=========================================\n";
	cout << "         [1] 20            [2] 50  \n";
	cout << "         [3] 100           [4] 200 \n";
	cout << "         [5] 400           [6] 600 \n";
	cout << "         [7] 800           [8] 1000\n";
	cout << "         [9] Exit\n";
	cout << "=========================================\n";

}
void PrintWordNormalWithdraw() {

	cout << "================================\n";
	cout << "         Normal Withdraw\n";
	cout << "================================\n";

}
void IfTheClientchoiceQuickWithdraw() {

	PrintTheQuickWithdrawScreen();
	ChoiceTheAmountThatwillWithdrawBYUseQuickWithdraw();
}
int ReadAmountToNormalWithdraw() {

	int Amount;

	do {

		cout << "\n\n Enter an amount multiple of 5's And Postistion ? ";
		cin >> Amount;
	} while (Amount < 1 || Amount % 5 != 0);

	return Amount;
}
void IfTheClientChoiceNormalWithdraw() {

	PrintWordNormalWithdraw();

	int Amount = ReadAmountToNormalWithdraw();
	vector<stClient> VClients = LoadClientDataFromfile("Client.txt");
	for (stClient& C : VClients) {

		if (C.AccountNumber == CurrentClient.AccountNumber) {

			while (C.AccountBalance < Amount) {

				cout << "\n\nAccount extends the Balance, you can Withdraw just :" << C.AccountBalance << endl;
				cout << "Please enter Another Amount? ";
				cin >> Amount;


			}
			DepositeOrWithdrawAmountFromBalanceClient(VClients, Amount * -1);

		}


	}

}

void PrintMainMenueScreen() {

	system("cls");

	PrintTheMenue();


	short ChoiceNumber = 0;

	do {

		cout << "Choose what do you want to do? [1 to 5]? ";
		cin >> ChoiceNumber;
		cout << "\n\n";
		ConvertChoiceToEnum(ChoiceNumber);


		switch (ChoiceNumber) {

		case enChoiceFromMainMenueScreen::QuickWithdraw:
		{
			system("cls");
			IfTheClientchoiceQuickWithdraw();
			ReturnToMainScreen();
			break;
		}

		case enChoiceFromMainMenueScreen::NormalWithdraw:
		{
			system("cls");
			IfTheClientChoiceNormalWithdraw();
			ReturnToMainScreen();

			break;
		}

		case enChoiceFromMainMenueScreen::Deposite:
		{
			system("cls");
			IfTheClientchoiceDeposite();
			ReturnToMainScreen();

			break;

		}

		case enChoiceFromMainMenueScreen::CheckBalance:
		{
			system("cls");

			IfTheClientchoiceCheckHisBalance();
			ReturnToMainScreen();

			break;


		}

		case enChoiceFromMainMenueScreen::Logout:
		{
			IfTheClientchoiceLogout();

			break;
		}

		}

	} while (ChoiceNumber > 5 || ChoiceNumber < 1);
}

bool FindCientThatHaveSameAccountNumberAndSamePinCode(string AccountNumber, string PinCode, stClient& Client) {

	vector<stClient>VClients = LoadClientDataFromfile(ClientFileName);

	for (stClient& U : VClients) {

		if (U.AccountNumber == AccountNumber && U.PinCode == PinCode) {

			Client = U;
			return true;
		}

	}
	return false;
}
bool LoadClientInfo(string AccountNumber, string PinCode) {

	if (FindCientThatHaveSameAccountNumberAndSamePinCode(AccountNumber, PinCode, CurrentClient)) {

		return true;
	}
	else
		return false;
}

void PrintWordLoginScreen() {

	cout << "\n--------------------------------\n";
	cout << "          Login Screen        \n";
	cout << "--------------------------------\n";
}

void Login() {

	bool LoginFailed = false;

	string AccountNumber, PinCode;
	do {

		system("cls");
		PrintWordLoginScreen();

		if (LoginFailed) {

			cout << " Invlaid AccountNumber/PinCode\n";
		}
		cout << " Enter Account Number ? ";
		cin >> AccountNumber;

		cout << " Enter PInCode ? ";
		cin >> PinCode;
		LoginFailed = !LoadClientInfo(AccountNumber, PinCode);

	} while (LoginFailed);

	PrintMainMenueScreen();

}

int main() {

	Login();
}