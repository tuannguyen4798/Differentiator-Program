#ifndef Laboratory2_group15_H
#define Laboratory2_group15_H    //header file

using namespace std;

class Diff // class  definition Differentiation
{
protected:
	int *type;
public:   // all public function of class
	Diff() {};  ////the default constructor to initialize a polynomial equal to 0
	~Diff() { delete[] type; };
	string myDiff_;
	void Split(string mystr);
	virtual void Errorcheck(string term[], int size) {};
	virtual void UpdateCoef_Value(string str[], int type[], int size) { ; }
};
class term : public Diff
{
protected:
	int *coef;
	int *value;
	int *type;
	int size_;
	int *ErrorID;

	int coef_list;
	int value_list;
	int type_list;
	int Error_list;

	term *next;
	term *head;
	term *curr;
public:
	term() : Diff() {}
	~term();
	/*GET AND SET VALUES SECTION*/
	int getCoef() { return coef_list; }
	void setCoef(int myCoef) { coef_list = myCoef; }
	int getValue() { return value_list; }
	void setValue(int myValue) { value_list = myValue; }
	int getType() { return type_list; }
	void setType(int myType) { type_list = myType; }
	void UpdateCoef_Value(string str[], int type[], int size);
	
	/*ERROR HANDLING*/
	void Errorcheck(string term[], int size);
	void Errorshow(int ID);
	
	/*CALCULATION*/
	bool Calculate();								//Calculate the result base on coef_list, value_list and type return the flag if error happen
	virtual void differentiate_() {};
	
	/*LINK LIST SECTION*/
	void List(int coef[], int value[], int type[]);
	void getData(int myCoef, int myValue, int myType, int ErrorID) { coef_list = myCoef, value_list = myValue, type_list = myType; Error_list = ErrorID; }
	void Head(int myCoef, int myValue, int myType, int ErrorID);
	void addEnd(int myCoef, int myValue, int myType, int ErrorID);
	void printList();
};
/*SUB CLASSES OF TERM*/
class Polynomial : public term {
	public: Polynomial() : term() {};
			~Polynomial() {};
};

class power : public Polynomial
{
public: power() : Polynomial() {};
		~power() {};
		void differentiate_();
};
class linear : public Polynomial
{
public: linear() : Polynomial() {};
		~linear() {};
		void differentiate_();
};
class constant :public Polynomial
{
public: constant() : Polynomial() {};
		~constant() {};
		void differentiate_();
};

class Trigonometric : public term {
	
public: Trigonometric() : term() {};
		~Trigonometric() {};
};


class Sinusoidal :public Trigonometric
{
	public: Sinusoidal() : Trigonometric() {};
			~Sinusoidal() {};
			void differentiate_();
};
class Cosinusoidal :public Trigonometric
{
	public: Cosinusoidal() : Trigonometric() {};
			~Cosinusoidal() {};
			void differentiate_();
};

class Exponential : public term
{
	public: Exponential() : term() {};
			~Exponential() {};
		void differentiate_();
};

class Logarithmic : public term {
	public: Logarithmic() : term() {};
			~Logarithmic() {};
};

class Base_10 : public Logarithmic
{
	public: Base_10() : Logarithmic() {};
			~Base_10() {};
		void differentiate_();
};
class Base_e : public Logarithmic
{
	public: Base_e() : Logarithmic() {};
			~Base_e() {};
		void differentiate_();
};
#endif