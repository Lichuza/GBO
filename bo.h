#pragma once
#include <string>
#include<vector>
using namespace std;
struct transaction
{
	int id;

	string type;
	int dboId;
	string documentSaveTimestamp;
	string documentNumber;
	double accountBalance;
	int commissionAmount;
	double transactionAmount;
	double accountLimit;	
	string sessionId;

	
	string sourceAccount;
	string paymentReceiver;

	struct clientDevice 
	{
		int id;
		string ip;
		string mac;
		string imei;
		string imsi;
		string os;
	} clientDevice;
			
	struct additionalFields 
	{
		int serviceCode;
		string nameTransaction;
		string nameService;
	}additionalFields;

	struct feature
	{
		string regular;
		string gray;
		string anomalTransfer;
		string NewPayee;
	}feature;

	int label;
};

vector<transaction> Data;