#include "pch.h"
#include <iostream>
#include "string.h"
#include "sstream"
#include "Laboratory2_group15.h"

//***********************************************************
/*STRING ANALYSING FUNTIONs*/
//***********************************************************


void Diff::Split(string mystr) //This will split, create and save to dynamic array
{
	int size = 0;
	int n = mystr.length();
	string *smallstring;
	if (mystr[0] != '+' && mystr[0] != '-')
	{
		mystr.insert(0, "+");
		n++;
	}
	for (int i = 0; i < mystr.length(); i++) {
		if (mystr[i] == '+' || mystr[i] == '-')
		{
			size++;
			i != 0 ? mystr[i - 1] == '(' ? size-- : size = size : size = size;
		}
	}
	smallstring = new string[size];
	type = new int[size];
	for (int i = 1; i < n; i++)
	{
		if (((mystr[i] == '+') || (mystr[i] == '-') || i == 0) && mystr[i - 1] != '(')
		{
			mystr.insert(i, " ");
			n++;
			i++;
		}
	}
	stringstream temp(mystr);
	for (int i = 0; i < size; i++)
	{
		getline(temp, smallstring[i], ' ');
	}
	//Insert 1* to the front of the variable x if nothing found in front of x
	for (int i = 0; i < size; i++)
	{
		
		for (int j = 1; j <= smallstring[i].length(); j++)
		{
			if (!isdigit(smallstring[i][1]))
			{
				smallstring[i].insert(1, "1*");
				j += 2;
			}
			if ((smallstring[i][j] == 'x' || smallstring[i][j] == 'X') && smallstring[i][j - 1] != '*' && !isdigit(smallstring[i][j - 1]))
			{
				smallstring[i].insert(j, "1*");
				j += 2;
			}
		}
	}
	Errorcheck(smallstring, size);
	
	for (int i = 0; i < size; i++)				// Define the type of function
	{
		//cout << smallstring[i] << endl;
		if (isdigit(smallstring[i][1])) type[i] = 0;
		if (smallstring[i].find("*x") != string::npos) type[i] = 1;
		if (smallstring[i].find("*x^") != string::npos) type[i] = 2;
		if (smallstring[i].find("*e^(") != string::npos) type[i] = 3;
		if (smallstring[i].find("log10(") != string::npos) type[i] = 4;
		if (smallstring[i].find("loge") != string::npos) type[i] = 5;
		if (smallstring[i].find("sin(") != string::npos) type[i] = 6;
		if (smallstring[i].find("cos(") != string::npos) type[i] = 7;
	}
	UpdateCoef_Value(smallstring, type, size);
}
void term::UpdateCoef_Value(string str[], int type[], int size)
{
	size_ = size;
	coef = new int[size];
	value = new int[size];
	for (int i = 0; i < size; i++)
	{
		istringstream iss(str[i]);
		char c[10] = {};
		switch (type[i])
		{
		case 1:
		{
			iss >> coef[i];
			value[i] = 1;
			break;
		}
		case 2:
		{
			iss >> coef[i] >> c[1] >> c[2] >> c[3] >> c[4] >> value[i];
			break;
		}
		case 3:
		{
			iss >> coef[i] >> c[1] >> c[2] >> c[3] >> c[4] >> value[i];
			break;
		}
		case 4:
		{
			iss >> coef[i] >> c[1] >> c[2] >> c[3] >> c[4] >> c[5] >> c[6] >> c[7] >> value[i];
			break;
		}
		case 5:
		{
			iss >> coef[i] >> c[1] >> c[2] >> c[3] >> c[4] >> c[5] >> c[6] >> value[i];
			break;
		}
		case 6:
		{
			iss >> coef[i] >> c[1] >> c[2] >> c[3] >> c[4] >> c[5] >> value[i];
			break;
		}
		case 7:
		{
			iss >> coef[i] >> c[1] >> c[2] >> c[3] >> c[4] >> c[5] >> value[i];
			break;
		}
		default:
			iss >> coef[i];
			value[i] = 1;
		}
	}
	List(coef, value, type);
}



//***********************************************************
/*ERROR HANDLING & DESCONTRUCTOR*/
//***********************************************************

void term::Errorcheck(string term[], int size)
{
	string *str;
	ErrorID = new int[size];		//create array of ErrorID
	str = new string[size];
	bool Log10;
	for (int i = 0; i < size; i++)
	{
		ErrorID[i] = 0;
		str[i] = term[i];
		int len = str[i].length();
		for (int j = 0; j <= len; j++)
		{
			bool minus = false;
			if (str[i][0] == '-')    //delete first sign
			{
				str[i].erase(0, 1);
				len = str[i].length();
				minus = true;
			}
			if (str[i][0] == '+')
			{
				str[i].erase(0, 1);
				len = str[i].length();
			}

		}
	}

	for (int i = 0; i < size; i++)
	{
		str[i].find("log10") != string::npos ? Log10 = true : Log10 = false;	//To eliminate condition which logn with n is integer entered
		int len = str[i].length();
		int count = 0;
		for (int j = 0; j <= len; j++)
		{

			if (isdigit(str[i][j]))
			{
				for (int k = j; isdigit(str[i][k]); k++)
				{
					count++;
				}
				str[i].replace(j, count, "a");
				len = str[i].length();
				count = 0;
			}
		}
		
		if (str[i] != "a*x"
			&& (str[i] != "a*x^(a)" && str[i] != "a*x^(-a)")
			&& (str[i] != "a*e^(a*x)" && str[i] != "a*e^(-a*x)")
			&& (str[i] != "a*loga(a*x)" || Log10 == false)
			&& (str[i] != "a*loge(a*x)" && str[i] != "a*logE(a*x)")
			&& (str[i] != "a*sin(a*x)"  && str[i] != "a*sin(-a*x)")
			&& (str[i] != "a*cos(a*x)" && str[i] != "a*cos(-a*x)")
			&& str[i] != "a")
		{
			ErrorID[i] = 1;
			if ((str[i] == "a*loga(-a*x)" && Log10 == true) || str[i] == "a*loge(-a*x)")ErrorID[i] = 2;
		}
	}
}

void term::Errorshow(int ID)
{
	if (ID == 1)  cout << "Invalid Input ,please try again" << endl;
	if (ID == 2)  cout << " Loge and Log10 invalid, please try again" << endl;
}

term::~term()
{
	term *next = new term();
	curr = head;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	delete[] coef;
	delete[] value;
	delete[] type;
}


//***********************************************************
/*CALCULATION*/
//***********************************************************

bool term::Calculate()
{
	bool ErrorDetected = false;
	curr = head;
	while (curr != NULL)
	{
		if (curr->Error_list != 0) ErrorDetected = true;
		if (ErrorDetected == true)  Errorshow(curr->Error_list);  break;;
		curr = curr->next;
		
	}
	curr = head;
	while (curr != NULL && ErrorDetected != true)
	{
		curr->differentiate_();
		curr = curr->next;
	}
	return !ErrorDetected;
}


void power::differentiate_()
{
	coef_list = getCoef() * getValue();
	value_list = getValue() - 1;
}

void linear::differentiate_()
{
	coef_list = getCoef();
	value_list = 0;
}

void constant::differentiate_()
{
	coef_list = 0;
	value_list = 0;
}

void Sinusoidal::differentiate_()
{
	coef_list = getCoef()*getValue();
	value_list = getValue();
	setType(7);
}

void Cosinusoidal::differentiate_()
{
	coef_list = -getCoef()*getValue();
	value_list = getValue();
	setType(6);
}

void Exponential::differentiate_()
{
	coef_list = getCoef()*getValue();
	value_list = getValue();
}

void Base_10::differentiate_()
{
	coef_list = getCoef();
	value_list = 1;
}

void Base_e::differentiate_()
{
	coef_list = getCoef();
	value_list = 1;
}
//***********************************************************
/*LINK LIST FUNCTIONS*/
//***********************************************************
void term::Head(int myCoef, int myValue, int myType, int ErrorID)
{
	switch (myType)
	{
	case 1:
	{
		term *newterm = new linear();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		head = newterm;
		head->next = NULL;
		curr = head;
		break;
	}
	case 2:
	{
		term *newterm = new power();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		head = newterm;
		head->next = NULL;
		curr = head;
		break;
	}
	case 3:
	{
		term *newterm = new Exponential();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		head = newterm;
		head->next = NULL;
		curr = head;
		break;
	}
	case 4:
	{
		term *newterm = new Base_10();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		head = newterm;
		head->next = NULL;
		curr = head;
		break;
	}
	case 5:
	{
		term *newterm = new Base_e();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		head = newterm;
		head->next = NULL;
		curr = head;
		break;
	}
	case 6:
	{
		term *newterm = new Sinusoidal();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		head = newterm;
		head->next = NULL;
		curr = head;
		break;
	}
	case 7:
	{
		term *newterm = new Cosinusoidal();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		head = newterm;
		head->next = NULL;
		curr = head;
		break;
	}
	case 0:
	{
		term *newterm = new constant();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		head = newterm;
		head->next = NULL;
		curr = head;
		break;
	}
	default:
		break;
	}
}

void term::addEnd(int myCoef, int myValue, int myType, int ErrorID)
{
	switch (myType)
	{
	case 1:
	{
		term *newterm = new linear();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		newterm->next = NULL;
		curr = head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newterm;
		/*cout << "node is linear" << endl;*/
		break;
	}
	case 2:
	{
		term *newterm = new power();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		newterm->next = NULL;
		curr = head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newterm;
	/*	cout << "node is power" << endl;*/
		break;
	}
	case 3:
	{
		term *newterm = new Exponential();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		newterm->next = NULL;
		curr = head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newterm;
		/*cout << "node is exp" << endl;*/
		break;
	}
	case 4:
	{
		term *newterm = new Base_10();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		newterm->next = NULL;
		curr = head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newterm;
		/*cout << "node is base_10" << endl;*/
		break;
	}
	case 5:
	{
		term *newterm = new Base_e();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		newterm->next = NULL;
		curr = head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newterm;
		//cout << "node is base_e" << endl;
		break;
	}
	case 6:
	{
		term *newterm = new Sinusoidal();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		newterm->next = NULL;
		curr = head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newterm;
	/*	cout << "node is sin" << endl;*/
		break;
	}
	case 7:
	{
		term *newterm = new Cosinusoidal();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		newterm->next = NULL;
		curr = head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newterm;
		/*cout << "node is cos" << endl;*/
		break;
	}
	case 0:
	{
		term *newterm = new constant();
		newterm->getData(myCoef, myValue, myType, ErrorID);
		newterm->next = NULL;
		curr = head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newterm;
		/*cout << "node is const" << endl;*/
		break;
	}
	default:
		break;
	}
}

void term::List(int coef[], int value[], int type[])

{
	Head(coef[0], value[0], type[0], ErrorID[0]);
	for (int i = 1; i < size_; i++)
	{
		addEnd(coef[i], value[i], type[i], ErrorID[i]);
	}
}

void term::printList()
{
	curr = head;
	if (curr == NULL) cout << "There is no result" << endl;
	else
	{
		while (curr != NULL)
		{
			if (curr->getCoef() >= 0)
			{
				cout << "+";
			}
			switch (curr->type_list)
			{
			case 0:
			{
				cout << curr->getCoef();
				break;
			}
			case 1:
			{
				cout << curr->getCoef();
				break;
			}
			case 2:
			{
				cout << curr->getCoef() << "*x^" << curr->getValue();
				break;
			}
			case 3:
			{
				if (curr->getValue() == 1)
					cout << curr->getCoef() << "*e^x";
				else cout << curr->getCoef() << "*e^(x*" << curr->getValue() << ")";

				break;
			}
			case 4:
			{
				cout << curr->getCoef() << "/(x*ln(10))";
				break;
			}
			case 5:
			{
				cout << curr->getCoef() << "/x";
				break;
			}

			case 6:
			{
				cout << curr->getCoef() << "*sin(" << curr->getValue() << "*x)";
				break;
			}
			case 7:
				cout << curr->getCoef() << "*cos(" << curr->getValue() << "*x)";
				break;
			default:
				cout << "" << endl;
			}
			curr = curr->next;
		}
	}
}

