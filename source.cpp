#include"bo.h"
#include "createState.h"
#include<iostream>
#include<ctime>
#include<stdlib.h>
#include <fstream>
#include "gnuPlot.h"
#include <codecvt>
using namespace std;

int main() 
{	
	srand(time(NULL));
	
	int countUsers = 100;
	vector<int>countDeviceV;

	for (int i = 0; i < countUsers; i++)
	{
		int tempCountTr=rand() % 11 + 10;
		vector<int>idDev;
		createState cS;

		
		int countDevice = rand()%4 + 1;
		int countIp = rand() % 5 + 1;

		bool flagImei = true;
		bool flagIp = true;

		//device
		vector <int> tempDeviceId;
		vector <string> tempDeviceImei;
		vector <string> tempDeviceImsi;
		vector <string> tempDeviceMac;
		vector <string> tempDeviceOs;

		//sourceAccount
		string tempSourceA = cS.sourceAccount();

		for (int j = 0; j < tempCountTr; j++)
		{
			transaction t;
			
			int idDevice = rand() % countDevice + 0;
			
			
			int idTr = rand() % 5 + 0;

			t.id = i;
			string tempType=t.type = cS.typeTransaction(idTr);

			double tempAcBalance = t.accountBalance = cS.accountBalance();
			double tempAcLimit=t.accountLimit = cS.accountLimit(tempType, tempAcBalance);

				
			bool flagDevice = true;
			if (j == 0)
			{
				t.clientDevice.id = cS.clientDeviceId(idDevice);
				t.clientDevice.imei = cS.clientDeviceImei(countDevice, flagImei);
				t.clientDevice.imsi = cS.clientDeviceImsi();
				t.clientDevice.mac = cS.clientDeviceMac();
				t.clientDevice.os = cS.clientDeviceOs(idDevice);
			}
			else 
			{
				for (int g = 0; g < tempDeviceId.size(); g++)
				{
					if (idDevice == tempDeviceId[g]) 
					{
						t.clientDevice.id = tempDeviceId[g];
						t.clientDevice.imei = tempDeviceImei[g];
						t.clientDevice.imsi = tempDeviceImsi[g];
						t.clientDevice.mac = tempDeviceMac[g];
						t.clientDevice.os = tempDeviceOs[g];
						flagDevice = false;
						break;
					}
				}
				if (flagDevice == true)
				{
					t.clientDevice.id = cS.clientDeviceId(idDevice);
					t.clientDevice.imei = cS.clientDeviceImei(countDevice, flagImei);
					t.clientDevice.imsi = cS.clientDeviceImsi();
					t.clientDevice.mac = cS.clientDeviceMac();
					t.clientDevice.os = cS.clientDeviceOs(idDevice);
				}
			}
		
			/////////////////////////////////
			tempDeviceId.push_back(t.clientDevice.id);
			tempDeviceImei.push_back(t.clientDevice.imei);
			tempDeviceImsi.push_back(t.clientDevice.imsi);
			tempDeviceMac.push_back(t.clientDevice.mac);
			tempDeviceOs.push_back(t.clientDevice.os);
			/////////////////////////////////

			t.clientDevice.ip = cS.clientDeviceIp(countIp,flagIp);

			double tempTrAmount=t.transactionAmount = cS.transactionAmount(tempAcBalance,tempAcLimit);
			t.commissionAmount = cS.commissionAmount(tempTrAmount, tempType);


			t.dboId = cS.clientDboId(i);;
			t.documentNumber = cS.documentNumber();
			t.documentSaveTimestamp = cS.documentSaveTimestamp();
			
			t.paymentReceiver = cS.paymentReceiver(tempType);

			string tempRegular=t.feature.regular = cS.regularTransaction();

			int tempserviceCode=t.additionalFields.serviceCode = cS.serviceCode(tempType);
			t.additionalFields.nameService = cS.nameService(tempserviceCode);
			t.additionalFields.nameTransaction = cS.nameTransaction(tempserviceCode);

			//sessionId
			bool flagSessionId = rand() % 2;

			if (flagSessionId==true || j==0)
			{
				t.sessionId = cS.sessionId();
			}
			else t.sessionId = Data[i + j - 1].sessionId;
			
			t.sourceAccount = tempSourceA;
			t.feature.gray = cS.grayBank(tempType, tempRegular);
			t.feature.anomalTransfer = cS.anomalTransfer(tempTrAmount, tempAcLimit);
			t.feature.NewPayee = cS.NewPayee(tempType, tempRegular);

			t.label = 0;
					
			Data.push_back(t);

			
			flagImei = false;
			flagIp = false;

			//Sleep(rand()%51+1);
		}
	}

	ofstream out("C:/transaction/test1.csv");
	out << "time,"<<"IDclient," << "sourceAccount," << "DBOID," << "documentNumber," << "sessionId," <<"type,"<<"accountBalance,"<<"accountLimit,"<<
		"transactionAmount,"<<"commissionAmount," << "paymentReceiver," << "IDDevice," << "IMEI," <<
		"IMSI," << "IP," << "MAC," << "OS," <<"anomalTransfer," << "NewPayee," <<"regular,"<<"gray,"
		<<"serviceCode,"<<"nameTransaction,"<<"nameService," <<"Class"<<endl;

	for (int i = 0; i < Data.size(); i++)
	{
		
		out << Data[i].documentSaveTimestamp << ",";

		out << Data[i].id << ",";
		out << Data[i].sourceAccount << ",";
		out << Data[i].dboId << ",";

		out << Data[i].documentNumber << ",";
		out << Data[i].sessionId << ",";

		out << Data[i].type << ",";

		out << Data[i].accountBalance << ",";
		out << Data[i].accountLimit << ",";
		out << Data[i].transactionAmount << ",";
		out << Data[i].commissionAmount << ",";
		out << Data[i].paymentReceiver << ",";
		
		out << Data[i].clientDevice.id<< ",";
		out << Data[i].clientDevice.imei << ",";
		out << Data[i].clientDevice.imsi << ",";
		out << Data[i].clientDevice.ip << ",";
		out << Data[i].clientDevice.mac << ",";
		out << Data[i].clientDevice.os << ",";
		
		out << Data[i].feature.anomalTransfer << ",";
		out << Data[i].feature.NewPayee << ",";
		out << Data[i].feature.regular << ",";
		out << Data[i].feature.gray << ",";

		out << Data[i].additionalFields.serviceCode << ",";
		out << Data[i].additionalFields.nameTransaction << ",";
		out << Data[i].additionalFields.nameService << ",";
		out << Data[i].label << endl;
	}
	out.close();


	
	vector<int>tempIV;
	int countFrodTr = 20;

	for (int i = 0; i < countFrodTr; i++)
	{
		createState cS;

        skip: int randI = rand() % (Data.size() + 1) + 0;
		if (i == 0 && ((Data[randI].type == "TRANSFER-TO-THE-BUDGET") || (Data[randI].type == "TRANSFER-BETWEEN-ACCOUNTS"))) goto skip;

		for (int j = 0; j < tempIV.size(); j++)
		{
			if ((tempIV[j] == randI) || (Data[randI].type == "TRANSFER-TO-THE-BUDGET") || (Data[randI].type == "TRANSFER-BETWEEN-ACCOUNTS")) goto skip;
		}

		tempIV.push_back(randI);

		int tenpRand1 = rand() % 100 + 0, tenpRand2 = rand() % 100 + 0, tenpRand3 = rand() % 100 + 0;
		
		if(tenpRand1 > 10) Data[randI].feature.gray = "true";	
		else Data[randI].feature.gray = "false";

		if (tenpRand2 > 10) Data[randI].feature.NewPayee = "true";
		else Data[randI].feature.NewPayee = "false";

		if (tenpRand3 > 10) Data[randI].feature.anomalTransfer = "true";
		else Data[randI].feature.anomalTransfer = "false";
		
		Data[randI].feature.regular = "false";


		Data[randI].sessionId= cS.sessionId();

		Data[randI].clientDevice.imei = cS.clientDeviceImei(1, true);
		Data[randI].clientDevice.ip = cS.clientDeviceIp(1, true);
		Data[randI].clientDevice.imsi = cS.clientDeviceImsi();
		Data[randI].clientDevice.mac = cS.clientDeviceMac();
		Data[randI].clientDevice.os = cS.clientDeviceOs(rand() % 5 + 0);

		if(rand()%2==1) Data[randI].additionalFields.nameService = cS.getNameSer(2);
		else Data[randI].additionalFields.nameService = cS.getNameSer(3);

		if (rand() % 2 == 1) Data[randI].additionalFields.nameTransaction = cS.getNameTr(0);
		else Data[randI].additionalFields.nameTransaction = cS.getNameTr(1);

		double tempAccountLimit = Data[randI].accountLimit;
		double tempAccountBalance = Data[randI].accountBalance;
		double tempTransactionAmount;

		if (Data[randI].feature.anomalTransfer == "true") 
		{
			if (tempAccountLimit > tempAccountBalance) tempTransactionAmount = Data[randI].transactionAmount = tempAccountBalance * 0.99;
			else tempTransactionAmount = Data[randI].transactionAmount = tempAccountLimit * 0.99;

			string tempType = Data[randI].type;
			Data[randI].commissionAmount = cS.commissionAmount(tempTransactionAmount, tempType);
		}

		Data[randI].label = 1;
	}

	ofstream outFrod("C:/transaction/FROD.csv");
	outFrod << "Âðåìÿ," << "IDclient," << "sourceAccount," << "DBOID," << "documentNumber," << "sessionId," << "type," << "accountBalance," << "accountLimit," <<
		"transactionAmount," << "commissionAmount," << "paymentReceiver," << "IDDevice," << "IMEI," <<
		"IMSI," << "IP," << "MAC," << "OS," << "anomalTransfer," << "NewPayee," << "regular," << "gray,"
		<< "serviceCode," << "nameTransaction," << "nameService," << "Class" << endl;

	for (int k = 0; k < countFrodTr; k++)
	{
		int i = tempIV[k];
		outFrod << Data[i].documentSaveTimestamp << ",";

		outFrod << Data[i].id << ",";
		outFrod << Data[i].sourceAccount << ",";
		out << Data[i].dboId << ",";

		outFrod << Data[i].documentNumber << ",";
		outFrod << Data[i].sessionId << ",";

		outFrod << Data[i].type << ",";

		outFrod << Data[i].accountBalance << ",";
		outFrod << Data[i].accountLimit << ",";
		outFrod << Data[i].transactionAmount << ",";
		outFrod << Data[i].commissionAmount << ",";
		outFrod << Data[i].paymentReceiver << ",";

		outFrod << Data[i].clientDevice.id << ",";
		outFrod << Data[i].clientDevice.imei << ",";
		outFrod << Data[i].clientDevice.imsi << ",";
		outFrod << Data[i].clientDevice.ip << ",";
		outFrod << Data[i].clientDevice.mac << ",";
		outFrod << Data[i].clientDevice.os << ",";

		outFrod << Data[i].feature.anomalTransfer << ",";
		outFrod << Data[i].feature.NewPayee << ",";
		outFrod << Data[i].feature.regular << ",";
		outFrod << Data[i].feature.gray << ",";

		outFrod << Data[i].additionalFields.serviceCode << ",";
		outFrod << Data[i].additionalFields.nameTransaction << ",";
		outFrod << Data[i].additionalFields.nameService << ",";
		outFrod << Data[i].label << endl;
	}
	outFrod.close();


	
	createState cS;
	ofstream outPlot("C:/transaction/pltType.txt");
	int j0 = 0, j1 = 0, j2 = 0, j3 = 0, j4 = 0;

	for (int i = 0; i < Data.size(); i++)
	{
		if (Data[i].type == cS.getTypeTr(0)) 	j0++;
		if (Data[i].type == cS.getTypeTr(1)) 	j1++;
		if (Data[i].type == cS.getTypeTr(2)) 	j2++;
		if (Data[i].type == cS.getTypeTr(3)) 	j3++;
		if (Data[i].type == cS.getTypeTr(4)) 	j4++;
	}

	outPlot << cS.getTypeTr(0) << " " << (double)j0 / Data.size() << endl;
	outPlot << cS.getTypeTr(1) << " " << (double)j1 / Data.size() << endl;
	outPlot << cS.getTypeTr(2) << " " << (double)j2 / Data.size() << endl;
	outPlot << cS.getTypeTr(3) << " " << (double)j3 / Data.size() << endl;
	outPlot << cS.getTypeTr(4) << " " << (double)j4 / Data.size() << endl;
	outPlot.close();


	gnuPlot gnu1;
	gnu1.command("set style data histograms");
	gnu1.command("set grid");
	gnu1.command("set style fill solid border - 1");
	gnu1.command("set boxwidth 0.6");
	gnu1.command("set xtic font 'Times-Roman, 14'");
	gnu1.command("set xtic rotate by - 10 scale 0");
	gnu1.command("set bmargin 3");
	gnu1.command("unset key");
	gnu1.command("set title 'Îòíîøåíèå òèïîâ òðàíçàêöèé' font 'Times-Roman, 18'");
	gnu1.command("plot 'C:/transaction/pltType.txt' using 2:xtic(1) lc rgbcolor 'blue'");

														
	int frod = 0, legal = 0;
	for (int i = 0; i < Data.size(); i++) 
	{
		if (Data[i].label == 0) legal++;
		else frod++;
	}

	ofstream outFL("C:/transaction/pltFrodLegal.txt");
	outFL << "FROD" << " " << (double)frod / Data.size() << endl;
	outFL << "LEGAL" << " " << (double)legal / Data.size() << endl;
	outFL.close();

	gnuPlot gnu2;
	gnu2.command("set style data histograms");
	gnu2.command("set grid");
	gnu2.command("set style fill solid border - 1");
	gnu2.command("set boxwidth 0.6");
	gnu2.command("set xtic font 'Times-Roman, 14'");
	gnu2.command("set xtic rotate by - 10 scale 0");
	gnu2.command("set bmargin 3");
	gnu2.command("unset key");
	gnu2.command("set title 'Îòíîøåíèå êîëè÷åñòâà íîðìàëüíûõ òðàíçàêöèé ê ôðîäîâûì' font 'Times-Roman, 18'");
	gnu2.command("plot 'C:/transaction/FrodLegal.txt' using 2:xtic(1) lc rgbcolor 'blue'");

	system("PAUSE");
	return 0;
}
