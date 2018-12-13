#pragma once
#include<stdlib.h>
#include<string>
#include<vector>
#include <time.h>
#include <stdio.h> 
#include <windows.h>

using namespace std;
class createState
{
public:
    long int accountBalance() { return rand() % 100000 + 1; }
	double accountLimit(string type, long int balance);
	double commissionAmount(const double amount, const string type);
	long int transactionAmount(long int balance, const double limit);
	string sourceAccount();
	string anomalTransfer(const double trAmount, const double limit);
	string typeTransaction(const int i) { return typeTr[i]; }

	string regularTransaction();
	string grayBank(const string type, const string regular);
	string NewPayee(const string type, const string regular);
	string sessionId();
	string documentSaveTimestamp();

	string clientDeviceImsi();
	string clientDeviceImei(const int countImei, const bool flag);
	string clientDeviceIp(const int countIp, const bool flag);
	string clientDeviceOs(const int i);
	int clientDeviceId(const int i){return i;}
	string clientDeviceMac();


	int clientDboId(const int i){ return (i + 1) + i * 2; }
	string paymentReceiver(const string type);
	int serviceCode(const string type);
	string documentNumber();
	string nameTransaction(const int serviceCode);
	string nameService(const int serviceCode);
	

	//////////////////////////////
	string getTypeTr(const int i);
	string getOs(const int i);
	string getNameTr(const int i) { return nameTr[i]; }
	string getNameSer(const int i) { return nameSer[i]; }
	/////////////////////////////

private:
	vector<string> vectorImei;
	vector<string> OS = { "IOS", "Android", "Windows", "Linux", "MacOS" };
	vector<string> typeTr = {"TRANSFER-IS-ACCOUNT", "TRANSFER-IS-CARD","SERVICE-PAYMENT", "TRANSFER-TO-THE-BUDGET","TRANSFER-BETWEEN-ACCOUNTS"};
	vector<string> nameTr = {"nan", "other", "personal_data"};
	vector<string> nameSer= { "LLC", "IE", "phone", "PE", "internal","internalBank", "service", "SE" };
	vector<string> ipV;

};

