#include "createState.h"


string createState::clientDeviceImsi()
{
	int mcc = 250;
	int mnc = rand() % 11 + 10;
	int id1 = rand() % 90000 + 10000, id2 = rand() % 90000 + 10000;

	string imsi = to_string(mcc) + to_string(mnc) + to_string(id1)+ to_string(id2);

	return imsi;
}


string createState::clientDeviceImei(const int countImei, const bool flag)
{
	if (flag == true) 
	{
		vectorImei.clear();

		for (int i = 0; i < countImei; i++)
		{
			int temp1 = rand() % 90000 + 10000, temp2 = rand() % 90000 + 10000, temp3 = rand() % 90000 + 10000;
			string imei = to_string(temp1)+ to_string(temp2)+to_string(temp3);
			vectorImei.push_back(imei);
		}
	}

	return vectorImei[(rand() % countImei + 1)-1];
}

string createState::clientDeviceIp(const int countIp, const bool flag)
{
	
	if (flag == true)
	{
		ipV.clear();

		for (int i = 0; i < 4*countIp; i++)
		{
			int octet1 = rand() % 255 + 0;
			int octet2 = rand() % 255 + 0;
			int octet3 = rand() % 255 + 0;
			int octet4 = rand() % 255 + 0;

			string ip = to_string(octet1) + "." + to_string(octet2) + "." + to_string(octet3) + "." + to_string(octet4);
			ipV.push_back(ip);
		}
		
	}

	return ipV[rand() % (4 * countIp)+0];
}

string createState::clientDeviceOs(const int i)
{
	return OS[i];
}

double createState::commissionAmount(const double amount, const string type)
{
	for (int i = 0; i < typeTr.size(); i++)
	{
		if (type == typeTr[i])
		{
			if (i == 0 || i == 1 || i == 2) return (amount / 100)*2;
			else return 0;
		}
	}
}


double createState::accountLimit(string type, long int balance)
{
	if (type == getTypeTr(3) || type == getTypeTr(4)) return balance;

	double temp = (tanh(balance / 20000))+0.01;
	return temp*balance;
}

string createState::regularTransaction()
{
	int temp=rand() % 100 + 1;
	if (temp > 70) return "true";
	else return "false";
}

string createState::documentSaveTimestamp()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	string temp= to_string(st.wYear) +"."+ to_string(st.wMonth) + "." + to_string(st.wDayOfWeek) +" "+ to_string(st.wHour) +":"+ to_string(st.wMinute) + ":" + to_string(st.wSecond)+ ":" + to_string(st.wMilliseconds);
	return temp;
}

long int createState::transactionAmount(long int balance, const double limit)
{
	int tempLimit = (int)ceil(limit);
	if (balance > limit) return rand() % tempLimit + 1;
	else if(balance <= limit) return rand() % balance + 1;
}


string createState::paymentReceiver(const string type)
{
	int temp1, temp2, temp3, temp4;

	if (type == "SERVICE-PAYMENT") temp1 = 8, temp2 = rand() % 27 + 900, temp3 = rand() % 900 + 100, temp4 = rand() % 9000 + 1000;
	else temp1 = rand() % 88889 + 11111, temp2 = rand() % 88889 + 11111, temp3 = rand() % 88889 + 11111, temp4 = rand() % 88889 + 11111;

	string receiver = to_string(temp1) + to_string(temp2) + to_string(temp3) + to_string(temp4);
	return receiver;
}

string createState::sessionId()
{
	string sessionI = "";
	for (int i = 0; i < 20; i++)
	{
		int f = rand() % 2 + 0;
		if (f == 0) sessionI += char('a' + rand() % ('z' - 'a'));
		else if(f == 1) sessionI += char('A' + rand() % ('Z' - 'A'));
		else sessionI += to_string(rand() % 9 + 0);
	}
	return sessionI;
}


string createState::documentNumber()
{
	int temp1 = rand() % 88889 + 11111, temp2 = rand() % 88889 + 11111;
	return to_string(temp1) + to_string(temp2);
}

string createState::clientDeviceMac()
{
	int temp1 = rand() % 0xff + 0, temp2 = rand() % 0xff + 0, temp3 = rand() % 0xff + 0, temp4 = rand() % 0xff + 0, temp5 = rand() % 0xff + 0, temp6 = rand() % 0xff + 0;
	string mac=to_string(temp1) + ':' + to_string(temp2) + ':' + to_string(temp3) + ':'+ to_string(temp4) + ':'+ to_string(temp5) + ':'+ to_string(temp6);
	return mac;
}

string createState::sourceAccount() 
{
	int temp1 = rand() % 88889 + 11111, temp2 = rand() % 88889 + 11111, temp3 = rand() % 88889 + 11111;
	string SourceAcc = to_string(temp1) + to_string(temp2) + to_string(temp3);
	return SourceAcc;
}


string  createState::grayBank(const string type, const string regular)
{

	if ((type == "TRANSFER-BETWEEN-ACCOUNTS" || "TRANSFER-TO-THE-BUDGET") || regular=="true") return "false";
	else
	{
		int temp = rand() % 101 + 0;
		if (temp >= 90) return "true";
		else return "false";
	}
	

}

string createState::anomalTransfer(const double trAmount, const double limit)
{
	if (trAmount > 0.95*limit) return "true";
	else return "false";
}

string createState::NewPayee(const string type, const string regular)
{
	if ((type == "TRANSFER-BETWEEN-ACCOUNTS") || (type == "TRANSFER-TO-THE-BUDGET") || (regular == "true")) return "false";
	else
	{
		int temp = rand() % 101 + 0;
		if (temp >= 90) return "true";
		else return "false";
	}
}

int createState::serviceCode(const string type)
{

	if (type == "TRANSFER-TO-THE-BUDGET") return 0;
	else if (type == "TRANSFER-BETWEEN-ACCOUNTS") return 1;
	else if (type == "TRANSFER-IS-ACCOUNT" || type == "TRANSFER-IS-CARD") return 2;
	else  return rand() % 8 + 3;

}

string createState::nameService(const int serviceCode)
{
	if (serviceCode == 0) return nameSer[7];
	else if (serviceCode == 1)return nameSer[4];
	else if (serviceCode == 2) return nameSer[rand() % 6 + 0];
	else return nameSer[6];
}
string createState::nameTransaction(const int serviceCode)
{
	if (serviceCode == 0) return nameTr[2];
	else if (serviceCode == 1)return nameTr[0];
	else if (serviceCode == 2) return nameTr[rand() % 3 + 0];
	else return nameTr[rand() % 3 + 0];
}

string createState::getTypeTr(const int i)
{
	return typeTr[i];
}

string createState::getOs(const int i)
{
	return OS[i];
}

