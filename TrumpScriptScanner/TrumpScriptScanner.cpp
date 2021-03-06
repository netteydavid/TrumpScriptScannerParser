// TrumpScriptScanner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

#pragma region DFA States
//Declaration of methods representing DFA States
void Scanner();
void m();
void ma();
void mak();
void make();
void mo();
void mor();
void more();
void p();
void pr();
void pro();
void prog();
void progr();
void progra();
void program();
void programm();
void programmi();
void programmin();
void programming();
void pl();
void plu();
void plusDFA();
void g();
void gr();
void gre();
void grea();
void great();
void a();
void as();
void ag();
void aga();
void agai();
void again();
void am();
void ame();
void amer();
void ameri();
void americ();
void america();
void an();
void andDFA();
void i();
void is();
void ifDFA();
void e();
void el();
void els();
void elseDFA();
void n();
void nu();
void num();
void numb();
void numbe();
void number();
void no();
void notDFA();
void b();
void bo();
void boo();
void boolDFA();
void boole();
void boolea();
void boolean();
void o();
void orDFA();
void t();
void te();
void tel();
void tell();
void ti();
void tim();
void time();
void times();
void l();
void lo();
void lon();
void longDFA();
void li();
void lie();
void le();
void les();
void lessDFA();
void s();
void sa();
void say();
void f();
void fa();
void fac();
void fact();
void constDigit();
void c0();
void c1();
void cz1();
void cz2();
void cz3();
void cz4();
void cz5();
void cz6();
void cz7();
void c2t9();
void c0t91();
void c0t92();
void c0t93();
void c0t94();
void constFinal();
void Identifier();
void BuildString();
void AcceptString();
void SpecialSymb();
void Comment();
#pragma endregion

#pragma region Parser methods
void Parser();
int getLookahead();
void q0();
void q1();
void parserError();
#pragma endregion

#pragma region Token
//Class representing a token
class Token {

	string val;

	/*
	Keyword = 0, Identifier = 1, Constants = 2, Strings = 3,
	Special symbols = 4
	*/
	int type; 
public:
	//Default Constructor
	Token();
	//Overloaded Constructor
	Token(string value, int typing);
	//Overloaded == operator
	bool operator== (Token& comp);
	//Overloaded != operator
	bool operator!= (Token& comp);
	//Get value
	string getVal();
	//Get type
	int getType();
	//Prints token's info
	void print();
};

Token::Token() {
	val = "";
	type = -1;
}

Token::Token(string value, int typing) {
	val = value;
	type = typing;
}

bool Token::operator==(Token& comp) {
	return (comp.type == type && comp.val == val);
}

bool Token::operator!= (Token& comp) {
	return (comp.type != type || comp.val != val);
}

int Token::getType() {
	return type;
}

string Token::getVal() {
	return val;
}

void Token::print() {
	cout << "Token: " << val << " Type: ";
	switch (type)
	{
	case 0:
		cout << "Keyword" << endl;
		break;
	case 1:
		cout << "Identifier" << endl;
		break;
	case 2:
		cout << "Constant" << endl;
		break;
	case 3:
		cout << "String" << endl;
		break;
	case 4:
		cout << "Special Symbol" << endl;
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region Resources
//Symbol Table
Token symtab[100];

//Current empty index in table
int tableind = 0;

//Current character
char current;

//Current string
string tok;

//Stream for source file
ifstream src;

//Token created upon success
Token* token = NULL;

//Checks for special symbols
bool isSpecialSymb();

//PDA Stack
int stack[100];

//Top of the stack
int top;

//Is the lookahead consumed?
bool isConsumed;

//Lookahead
int lookahead;

//Line number
int line = 0;
#pragma endregion

/*
Depending on the type of error, errorHandler will output one of 
three rude remarks:
	0 = [id] error: This is a country where we speak English.
	1 = [const] error: I’m really rich, part of the beauty of me is I’m very rich.
	2 = Any other error: Trump doesn’t want to hear it.
*/
void ErrorHandler(int type) {
	switch (type) {
	case 0:
		cout << "This is a country where we speak English." << endl;
		break;
	case 1:
		cout << "I'm really rich, part of the beauty of me is I'm very rich." << endl;
		break;
	default:
		cout << "Trump doesn't want to hear it." << endl;
		break;
	}
}

/*
Populates symbol table with unique tokens of type identifier, constant, or string.
If token exists in symbol table, it is not added.
*/
void BookKeeper(Token item) {
	//Check if token is of correct type
	if (item.getType() != 1 && item.getType() != 2 && item.getType() != 3) {
		ErrorHandler(2);
		return;
	}

	//Is the current token in table?
	bool recorded = false;

	//Check if token exists in table
	for (int i = 0; i < tableind; i++) {
		if (symtab[i] == item) {
			recorded = true;
		}
	}

	//Insert if new token
	if (!recorded) {
		symtab[tableind] = item;
		tableind++;
	}
}

//Main program reads from source file
int main()
{
	//Prints source program
	string outStr;
	ifstream src1("sourcecode.txt");
	if (src1.is_open()) {
		cout << "Source Print Out: " << endl;
		while (getline(src1, outStr))
		{
			cout << outStr << endl;
		}

		cout << '\n' << endl;
		src1.close();
	}
	else
	{
		cout << "Unable to open file..." << endl;
	}

	Parser();

    return 0;
}



bool isSpecialSymb()
{
	return current == ',' || current == ';' || current == ':' || current == '!' || current == '?' ||
		current == '(' || current == ')';
}

#pragma region Scanner
void Scanner() {

	src.get(current);

	if (current == '\n') {
		++line;
	}

	if (isalpha(current)) {
		current = tolower(current);
		//To Keywords or Identifiers
		if (current == 'a') {
			tok += current;
			a();
		}
		else if (current == 'b') {
			tok += current;
			b();
		}
		else if (current == 'c') {
			tok += current;
			Identifier();
		}
		else if (current == 'd') {
			tok += current;
			Identifier();
		}
		else if (current == 'e') {
			tok += current;
			e();
		}
		else if (current == 'f') {
			tok += current;
			f();
		}
		else if (current == 'g') {
			tok += current;
			g();
		}
		else if (current == 'h') {
			tok += current;
			Identifier();
		}
		else if (current == 'i') {
			tok += current;
			i();
		}
		else if (current == 'j') {
			tok += current;
			Identifier();
		}
		else if (current == 'k') {
			tok += current;
			Identifier();
		}
		else if (current == 'l') {
			tok += current;
			l();
		}
		else if (current == 'm') {
			tok += current;
			m();
		}
		else if (current == 'n') {
			tok += current;
			n();
		}
		else if (current == 'o') {
			tok += current;
			o();
		}
		else if (current == 'p') {
			tok += current;
			p();
		}
		else if (current == 'q') {
			tok += current;
			Identifier();
		}
		else if (current == 'r') {
			tok += current;
			Identifier();
		}
		else if (current == 's') {
			tok += current;
			s();
		}
		else if (current == 't') {
			tok += current;
			t();
		}
		else if (current == 'u') {
			tok += current;
			Identifier();
		}
		else if (current == 'v') {
			tok += current;
			Identifier();
		}
		else if (current == 'w') {
			tok += current;
			Identifier();
		}
		else if (current == 'x') {
			tok += current;
			Identifier();
		}
		else if (current == 'y') {
			tok += current;
			Identifier();
		}
		else if (current == 'z') {
			tok += current;
			Identifier();
		}
	}
	//To Constants
	else if (isdigit(current)) {
		if (current == '1') {
			tok += current;
			c1();
		}
		else if (current != '0') {
			tok += current;
			constDigit();
		}
		else {
			c0();
		}
	}
	//To Strings
	else if (current == '"') {
		BuildString();
	}
	//To Special Symbols
	else if (isSpecialSymb()) {
		tok += current;
		SpecialSymb();
	}
	//To Self
	else if (iswspace(current)) {
		Scanner();
	}
	//To Comments
	else if (current == '#') {
		Comment();
	}
	else
	{
		ErrorHandler(2);
	}

}

#pragma region Keywords
void m() {
	current = src.peek();
	current = tolower(current);

	if (current == 'a') {
		current = src.get();
		tok += current;
		ma();
	}
	else if (current == 'o') {
		current = src.get();
		tok += current;
		mo();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void ma() {
	current = src.peek();
	current = tolower(current);

	if (current == 'k') {
		current = src.get();
		tok += current;
		mak();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void mak() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		make();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}
//Accepting State
void make() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}

}

void mo() {
	current = src.peek();
	current = tolower(current);

	if (current == 'r') {
		current = src.get();
		tok += current;
		mor();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void mor() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		more();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}
//Accepting State
void more() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void p() {
	current = src.peek();
	current = tolower(current);

	if (current == 'r') {
		current = src.get();
		tok += current;
		pr();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else if (current == 'l') {
		current = src.get();
		tok += current;
		pl();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void pr() {
	current = src.peek();
	current = tolower(current);

	if (current == 'o') {
		current = src.get();
		tok += current;
		pro();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void pro() {
	current = src.peek();
	current = tolower(current);

	if (current == 'g') {
		current = src.get();
		tok += current;
		prog();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void prog() {
	current = src.peek();
	current = tolower(current);

	if (current == 'r') {
		current = src.get();
		tok += current;
		progr();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void progr() {
	current = src.peek();
	current = tolower(current);

	if (current == 'a') {
		current = src.get();
		tok += current;
		progra();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void progra() {
	current = src.peek();
	current = tolower(current);

	if (current == 'm') {
		current = src.get();
		tok += current;
		program();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void program() {
	current = src.peek();
	current = tolower(current);

	if (current == 'm') {
		current = src.get();
		tok += current;
		programm();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void programm() {
	current = src.peek();
	current = tolower(current);

	if (current == 'i') {
		current = src.get();
		tok += current;
		programmi();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void programmi() {
	current = src.peek();
	current = tolower(current);

	if (current == 'n') {
		current = src.get();
		tok += current;
		programmin();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void programmin() {
	current = src.peek();
	current = tolower(current);

	if (current == 'g') {
		current = src.get();
		tok += current;
		programming();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void programming() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void pl() {
	current = src.peek();
	current = tolower(current);

	if (current == 'u') {
		current = src.get();
		tok += current;
		plu();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void plu() {
	current = src.peek();
	current = tolower(current);

	if (current == 's') {
		current = src.get();
		tok += current;
		plusDFA();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void plusDFA() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void g() {
	current = src.peek();
	current = tolower(current);

	if (current == 'r') {
		current = src.get();
		tok += current;
		gr();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void gr() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		gre();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void gre() {
	current = src.peek();
	current = tolower(current);

	if (current == 'a') {
		current = src.get();
		tok += current;
		grea();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void grea() {
	current = src.peek();
	current = tolower(current);

	if (current == 't') {
		current = src.get();
		tok += current;
		great();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}
//Accepting State
void great() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void a(){
	current = src.peek();
	current = tolower(current);

	if (current == 'g') {
		current = src.get();
		tok += current;
		ag();
	}
	else if (current == 'm') {
		current = src.get();
		tok += current;
		am();
	}
	else if (current == 's') {
		current = src.get();
		tok += current;
		as();
	}
	else if (current == 'n') {
		current = src.get();
		tok += current;
		an();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting state
void as() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void ag() {
	current = src.peek();
	current = tolower(current);

	if (current == 'a') {
		current = src.get();
		tok += current;
		aga();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void aga() {
	current = src.peek();
	current = tolower(current);

	if (current == 'i') {
		current = src.get();
		tok += current;
		agai();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void agai() {
	current = src.peek();
	current = tolower(current);

	if (current == 'n') {
		current = src.get();
		tok += current;
		again();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting state
void again() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void am() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		ame();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void ame() {
	current = src.peek();
	current = tolower(current);

	if (current == 'r') {
		current = src.get();
		tok += current;
		amer();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void amer() {
	current = src.peek();
	current = tolower(current);

	if (current == 'i') {
		current = src.get();
		tok += current;
		ameri();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void ameri() {
	current = src.peek();
	current = tolower(current);


	if (current == 'c') {
		current = src.get();
		tok += current;
		americ();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void americ() {
	current = src.peek();
	current = tolower(current);

	if (current == 'a') {
		current = src.get();
		tok += current;
		america();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void america() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void an() {
	current = src.peek();
	current = tolower(current);

	if (current == 'd') {
		current = src.get();
		tok += current;
		andDFA();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void andDFA() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void i() {
	current = src.peek();
	current = tolower(current);

	if (current == 's') {
		current = src.get();
		tok += current;
		is();
	}
	else if (current == 'f') {
		current = src.get();
		tok += current;
		ifDFA();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void is() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void ifDFA () {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void e() {
	current = src.peek();
	current = tolower(current);

	if (current == 'l') {
		current = src.get();
		tok += current;
		el();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void el() {
	current = src.peek();
	current = tolower(current);

	if (current == 's') {
		current = src.get();
		tok += current;
		els();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void els() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		elseDFA();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void elseDFA() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void n() {
	current = src.peek();
	current = tolower(current);

	if (current == 'u') {
		current = src.get();
		tok += current;
		nu();
	}
	else if (current == 'o') {
		current = src.get();
		tok += current;
		no();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void nu() {
	current = src.peek();
	current = tolower(current);

	if (current == 'm') {
		current = src.get();
		tok += current;
		num();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void num() {
	current = src.peek();
	current = tolower(current);

	if (current == 'b') {
		current = src.get();
		tok += current;
		numb();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void numb() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		numbe();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void numbe() {
	current = src.peek();
	current = tolower(current);

	if (current == 'r') {
		current = src.get();
		tok += current;
		number();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void number() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void no() {
	current = src.peek();
	current = tolower(current);

	if (current == 't') {
		current = src.get();
		tok += current;
		notDFA();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void notDFA() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void b() {
	current = src.peek();
	current = tolower(current);

	if (current == 'o') {
		current = src.get();
		tok += current;
		bo();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void bo() {
	current = src.peek();
	current = tolower(current);

	if (current == 'o') {
		current = src.get();
		tok += current;
		boo();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void boo() {
	current = src.peek();
	current = tolower(current);

	if (current == 'l') {
		current = src.get();
		tok += current;
		boolDFA();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void boolDFA() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		boole();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void boole() {
	current = src.peek();
	current = tolower(current);

	if (current == 'a') {
		current = src.get();
		tok += current;
		boolea();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void boolea() {
	current = src.peek();
	current = tolower(current);

	if (current == 'n') {
		current = src.get();
		tok += current;
		boolean();
	}
	else if (isalnum(current)) {

		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void boolean() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void o() {
	current = src.peek();
	current = tolower(current);

	if (current == 'r') {
		current = src.get();
		tok += current;
		orDFA();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void orDFA() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void t() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		te();
	}
	else if (current == 'i') {
		current = src.get();
		tok += current;
		ti();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void te() {
	current = src.peek();
	current = tolower(current);

	if (current == 'l') {
		current = src.get();
		tok += current;
		tel();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void tel() {
	current = src.peek();
	current = tolower(current);

	if (current == 'l') {
		current = src.get();
		tok += current;
		tell();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void tell() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void ti() {
	current = src.peek();
	current = tolower(current);

	if (current == 'm') {
		current = src.get();
		tok += current;
		tim();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void tim() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		time();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void time() {
	current = src.peek();
	current = tolower(current);

	if (current == 's') {
		current = src.get();
		tok += current;
		times();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void times() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void l() {
	current = src.peek();
	current = tolower(current);

	if (current == 'o') {
		current = src.get();
		tok += current;
		lo();
	}
	else if (current == 'i') {
		current = src.get();
		tok += current;
		li();
	}
	else if (current == 'e') {
		current = src.get();
		tok += current;
		le();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void lo() {
	current = src.peek();
	current = tolower(current);

	if (current == 'n') {
		current = src.get();
		tok += current;
		lon();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void lon() {
	current = src.peek();
	current = tolower(current);

	if (current == 'g') {
		current = src.get();
		tok += current;
		longDFA();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void longDFA() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void li() {
	current = src.peek();
	current = tolower(current);

	if (current == 'e') {
		current = src.get();
		tok += current;
		lie();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void lie() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void le() {
	current = src.peek();
	current = tolower(current);

	if (current == 's') {
		current = src.get();
		tok += current;
		les();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void les() {
	current = src.peek();
	current = tolower(current);

	if (current == 's') {
		current = src.get();
		tok += current;
		lessDFA();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void lessDFA() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void s() {
	current = src.peek();
	current = tolower(current);

	if (current == 'a') {
		current = src.get();
		tok += current;
		sa();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void sa() {
	current = src.peek();
	current = tolower(current);

	if (current == 'y') {
		current = src.get();
		tok += current;
		say();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void say() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void f() {
	current = src.peek();
	current = tolower(current);

	if (current == 'a') {
		current = src.get();
		tok += current;
		fa();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void fa() {
	current = src.peek();
	current = tolower(current);

	if (current == 'c') {
		current = src.get();
		tok += current;
		fac();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

void fac() {
	current = src.peek();
	current = tolower(current);

	if (current == 't') {
		current = src.get();
		tok += current;
		fact();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}

//Accepting State
void fact() {
	current = src.peek();
	current = tolower(current);

	if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 0);
		//token->print();
	}
	else if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(2);
	}
}
#pragma endregion

#pragma region Constants
void constDigit() {
	src.get(current);
	if (isdigit(current)){
		tok += current;
		c2t9();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void c0() {
	src.get(current);
	if (current == '0') {
		c0();
	}
	else if (isdigit(current)) {
		tok += current;
		if (current == '1') {
			c1();
		}
		else {
			constDigit();
		}
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void c1() {
	src.get(current);
	if (current == '0') {
		tok += current;
		cz1();
	}
	else if (isdigit(current)) {
		tok += current;
		c2t9();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void cz1() {
	src.get(current);
	if (current == '0') {
		tok += current;
		cz2();
	}
	else if (isdigit(current)) {
		tok += current;
		c0t91();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void cz2() {
	src.get(current);
	if (current == '0') {
		tok += current;
		cz3();
	}
	else if (isdigit(current)) {
		tok += current;
		c0t92();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void cz3() {
	src.get(current);
	if (current == '0') {
		tok += current;
		cz4();
	}
	else if (isdigit(current)) {
		tok += current;
		c0t93();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void cz4() {
	src.get(current);
	if (current == '0') {
		tok += current;
		cz5();
	}
	else if (isdigit(current)) {
		tok += current;
		c0t94();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void cz5() {
	src.get(current);
	if (current == '0') {
		tok += current;
		cz6();
	}
	else if (isdigit(current)) {
		tok += current;
		constFinal();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void cz6() {
	src.get(current);
	if (isdigit(current)) {
		tok += current;
		if (current == '0') {
			cz7();
		}
		else {
			constFinal();
		}
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void cz7() {
	src.get(current);
	if (isdigit(current)) {
		tok += current;
		constFinal();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void c2t9() {
	src.get(current);
	if (isdigit(current)) {
		tok += current;
		c0t91();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void c0t91() {
	src.get(current);
	if (isdigit(current)) {
		tok += current;
		c0t92();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void c0t92() {
	src.get(current);
	if (isdigit(current)) {
		tok += current;
		c0t93();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void c0t93() {
	src.get(current);
	if (isdigit(current)) {
		tok += current;
		c0t94();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

void c0t94() {
	src.get(current);
	if (isdigit(current)) {
		tok += current;
		constFinal();
	}
	else {
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}

//Accepting state
void constFinal() {
	current = src.peek();
	if (isdigit(current)) {
		current = src.get();
		tok += current;
		constFinal();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 2);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(1);
	}
}
#pragma endregion

#pragma region Identifiers
//Accepting state
void Identifier() {
	current = src.peek();
	if (isalnum(current)) {
		current = src.get();
		tok += current;
		Identifier();
	}
	else if (iswspace(current) || isSpecialSymb() || current == EOF) {
		token = new Token(tok, 1);
		//token->print();
		BookKeeper(*token);
	}
	else {
		current = src.get();
		tok += current;
		token = new Token(tok, -1);
		//token->print();
		ErrorHandler(0);
	}
}
#pragma endregion

#pragma region Strings
void BuildString() {
	src.get(current);
	if (current != '"') {
		tok += current;
		BuildString();
	}
	else
	{
		AcceptString();
	}
}

//Accepting state
void AcceptString() {
	token = new Token(tok, 3);
	//token->print();
	BookKeeper(*token);
}
#pragma endregion

#pragma region Special Symbols
//Accepting state
void SpecialSymb() {
	token = new Token(tok, 4);
	//token->print();
}
#pragma endregion

#pragma region Comments
void Comment() {
	src.get(current);
	if (current != '\n') {
		Comment();
	}
	else
	{
		Scanner();
	}
}
#pragma endregion


#pragma endregion

#pragma region Parser
void Parser() {

	//Initialize pda stack
	top = 0;
	stack[top] = 0;
	for (int i = 1; i < 100; i++) {
		stack[i] = -1;
	}

	//Set isConsumed
	isConsumed = false;

	//Push start symbol onto stack
	cout << "Begin Parsing:" << endl;
	cout << "Z0 (0)" << "\t\t" << "-" << "\t\t" << "Push <Trump>\n" << endl;
	++top;
	stack[top] = 34;
	

	//Begin scanning
	src.open("sourcecode.txt");
	if (src.is_open()) {
		while (current != EOF) {
			tok = "";
			if (token != NULL) {
				delete token;
				token = NULL;
			}

			Scanner();
			lookahead = getLookahead();
			isConsumed = false;

			while (!isConsumed) {
				q0();
				cout << endl;
			}
			
		}
		q0();
		cout << '\n' << endl;
		src.close();
	}
}

int getLookahead() {
	if (token != NULL) {
		switch (token->getType()) {
		case 0:
			if (token->getVal() == "make") {
				return 4;
			}
			else if (token->getVal() == "programming") {
				return 5;
			}
			else if (token->getVal() == "great") {
				return 6;
			}
			else if (token->getVal() == "again") {
				return 7;
			}
			else if (token->getVal() == "america") {
				return 8;
			}
			else if (token->getVal() == "is") {
				return 9;
			}
			else if (token->getVal() == "else") {
				return 10;
			}
			else if (token->getVal() == "number") {
				return 11;
			}
			else if (token->getVal() == "boolean") {
				return 12;
			}
			else if (token->getVal() == "if") {
				return 13;
			}
			else if (token->getVal() == "as") {
				return 14;
			}
			else if (token->getVal() == "long") {
				return 15;
			}
			else if (token->getVal() == "tell") {
				return 16;
			}
			else if (token->getVal() == "say") {
				return 17;
			}
			else if (token->getVal() == "fact") {
				return 18;
			}
			else if (token->getVal() == "lie") {
				return 19;
			}
			else if (token->getVal() == "not") {
				return 20;
			}
			else if (token->getVal() == "and") {
				return 21;
			}
			else if (token->getVal() == "or") {
				return 22;
			}
			else if (token->getVal() == "less") {
				return 23;
			}
			else if (token->getVal() == "more") {
				return 24;
			}
			else if (token->getVal() == "plus") {
				return 25;
			}
			else if (token->getVal() == "times") {
				return 26;
			}
			else {
				parserError();
				return -1;
			}
			break;
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			if (token->getVal() == ",") {
				return 27;
			}
			else if (token->getVal() == ";") {
				return 28;
			}
			else if (token->getVal() == ":") {
				return 29;
			}
			else if (token->getVal() == "!") {
				return 30;
			}
			else if (token->getVal() == "?") {
				return 31;
			}
			else if (token->getVal() == "(") {
				return 32;
			}
			else if (token->getVal() == ")") {
				return 33;
			}
			else {
				parserError();
				return -1;
			}
			break;
		default:
			parserError();
			return -1;
		}
	}
	else {
		cout << "Error on line " << line << ": Token Null." << endl;
		return -2;
	}
}

void q0() {
	string look = "";

	if (token->getType() == 1) {
		look = "[ID]";
	}
	else if (token->getType() == 2) {
		look = "[Constant]";
	}
	else if (token->getType() == 3) {
		look = "[String]";
	}
	else {
		look = token->getVal();
	}

	switch (stack[top])
	{
	case 0:
		q1();
		break;
	case 1:
		if (stack[top] == lookahead) {
			cout << "[ID] (" << stack[top] << ")" << "\t\t" << "[ID] (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 2:
		if (stack[top] == lookahead) {
			cout << "[Constant] (" << stack[top] << ")" << "\t\t" << "[Constant] (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 3:
		if (stack[top] == lookahead) {
			cout << "[String] (" << stack[top] << ")" << "\t\t" << "[String] (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 4:
		if (stack[top] == lookahead) {
			cout << "make (" << stack[top] << ")" << "\t\t" << "make (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 5:
		if (stack[top] == lookahead) {
			cout << "programming (" << stack[top] << ")" << "\t\t" << "programming (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 6:
		if (stack[top] == lookahead) {
			cout << "great (" << stack[top] << ")" << "\t\t" << "great (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 7:
		if (stack[top] == lookahead) {
			cout << "again (" << stack[top] << ")" << "\t\t" << "again (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 8:
		if (stack[top] == lookahead) {
			cout << "america (" << stack[top] << ")" << "\t\t" << "america (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 9:
		if (stack[top] == lookahead) {
			cout << "is (" << stack[top] << ")" << "\t\t" << "is (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 10:
		if (stack[top] == lookahead) {
			cout << "else (" << stack[top] << ")" << "\t\t" << "else (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 11:
		if (stack[top] == lookahead) {
			cout << "number (" << stack[top] << ")" << "\t\t" << "number (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 12:
		if (stack[top] == lookahead) {
			cout << "boolean (" << stack[top] << ")" << "\t\t" << "boolean (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 13:
		if (stack[top] == lookahead) {
			cout << "if (" << stack[top] << ")" << "\t\t" << "if (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 14:
		if (stack[top] == lookahead) {
			cout << "as (" << stack[top] << ")" << "\t\t" << "as (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 15:
		if (stack[top] == lookahead) {
			cout << "long (" << stack[top] << ")" << "\t\t" << "long (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 16:
		if (stack[top] == lookahead) {
			cout << "tell (" << stack[top] << ")" << "\t\t" << "tell (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 17:
		if (stack[top] == lookahead) {
			cout << "say (" << stack[top] << ")" << "\t\t" << "say (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 18:
		if (stack[top] == lookahead) {
			cout << "fact (" << stack[top] << ")" << "\t\t" << "fact (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 19:
		if (stack[top] == lookahead) {
			cout << "lie (" << stack[top] << ")" << "\t\t" << "lie (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 20:
		if (stack[top] == lookahead) {
			cout << "not (" << stack[top] << ")" << "\t\t" << "not (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 21:
		if (stack[top] == lookahead) {
			cout << "and (" << stack[top] << ")" << "\t\t" << "and (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 22:
		if (stack[top] == lookahead) {
			cout << "or (" << stack[top] << ")" << "\t\t" << "or (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 23:
		if (stack[top] == lookahead) {
			cout << "less (" << stack[top] << ")" << "\t\t" << "less (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 24:
		if (stack[top] == lookahead) {
			cout << "more (" << stack[top] << ")" << "\t\t" << "more (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 25:
		if (stack[top] == lookahead) {
			cout << "plus (" << stack[top] << ")" << "\t\t" << "plus (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 26:
		if (stack[top] == lookahead) {
			cout << "times (" << stack[top] << ")" << "\t\t" << "times (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 27:
		if (stack[top] == lookahead) {
			cout << ", (" << stack[top] << ")" << "\t\t" << ", (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 28:
		if (stack[top] == lookahead) {
			cout << "; (" << stack[top] << ")" << "\t\t" << "; (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 29:
		if (stack[top] == lookahead) {
			cout << ": (" << stack[top] << ")" << "\t\t" << ": (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 30:
		if (stack[top] == lookahead) {
			cout << "! (" << stack[top] << ")" << "\t\t" << "! (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 31:
		if (stack[top] == lookahead) {
			cout << "? (" << stack[top] << ")" << "\t\t" << "? (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 32:
		if (stack[top] == lookahead) {
			cout << "( (" << stack[top] << ")" << "\t\t" << "( (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 33:
		if (stack[top] == lookahead) {
			cout << ")" << "\t\t" << " (" << stack[top] << ")" << "\t\t" << ") (" << stack[top] << ")" << "\t\t" << "Matching" << endl;
			stack[top] = -1;
			--top;
			isConsumed = true;
		}
		else {
			parserError();
		}
		break;
	case 34:
		if (lookahead == 4) {
			cout << "<Trump> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << stack[top] << ")" << "\t\t" << "Use Rule 1" << endl;
			stack[top] = 36;
			++top;
			stack[top] = 37;
			++top;
			stack[top] = 35;
		}
		else {
			parserError();
		}
		break;
	case 35:
		if (lookahead == 4) {
			cout << "<first> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 2" << endl;
			stack[top] = 7;
			++top;
			stack[top] = 6;
			++top;
			stack[top] = 5;
			++top;
			stack[top] = 4;
		}
		else {
			parserError();
		}
		break;
	case 36:
		if (lookahead == 8) {
			cout << "<last> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 3" << endl;
			stack[top] = 6;
			++top;
			stack[top] = 9;
			++top;
			stack[top] = 8;
		}
		else {
			parserError();
		}
		break;
	case 37:
		if (lookahead == 4 || lookahead == 1 || lookahead == 13 || lookahead == 14 || lookahead == 16 || lookahead == 17) {
			cout << "<stmts> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 4" << endl;
			stack[top] = 38;
			++top;
			stack[top] = 28;
			++top;
			stack[top] = 39;
		}
		else {
			parserError();
		}
		break;
	case 38:
		if (lookahead == 4 || lookahead == 1 || lookahead == 13 || lookahead == 14 || lookahead == 16 || lookahead == 17) {
			cout << "<more-stmts> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 5" << endl;
			stack[top] = 38;
			++top;
			stack[top] = 28;
			++top;
			stack[top] = 39;
		}
		else if (lookahead == 8 || lookahead == 30) {
			cout << "<more-stmts> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 6" << endl;
			stack[top] = -1;
			--top;
		}
		else {
			parserError();
		}
		break;
	case 39:
		if (lookahead == 4) {
			cout << "<stmt> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 7" << endl;
			stack[top] = 40;
		}
		else if (lookahead == 1) {
			cout << "<stmt> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 8" << endl;
			stack[top] = 42;
		}
		else if (lookahead == 13) {
			cout << "<stmt> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 9" << endl;
			stack[top] = 43;
		}
		else if (lookahead == 14) {
			cout << "<stmt> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 10" << endl;
			stack[top] = 44;
		}
		else if (lookahead == 16 || lookahead == 17) {
			cout << "<stmt> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 11" << endl;
			stack[top] = 45;
		}
		else {
			parserError();
		}
		break;
	case 40:
		if (lookahead == 4) {
			cout << "<decl> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 12" << endl;
			stack[top] = 41;
			++top;
			stack[top] = 46;
			++top;
			stack[top] = 4;
		}
		else {
			parserError();
		}
		break;
	case 41:
		if (lookahead == 11) {
			cout << "<type> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 13" << endl;
			stack[top] = 11;
		}
		else if (lookahead == 12) {
			cout << "<type> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 14" << endl;
			stack[top] = 12;
		}
		else {
			parserError();
		}
		break;
	case 42:
		if (lookahead == 1) {
			cout << "<asmt> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 15" << endl;
			stack[top] = 48;
			++top;
			stack[top] = 9;
			++top;
			stack[top] = 1;
		}
		else {
			parserError();
		}
		break;
	case 43:
		if (lookahead == 13) {
			cout << "<cond> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 16" << endl;
			stack[top] = 30;
			++top;
			stack[top] = 37;
			++top;
			stack[top] = 29;
			++top;
			stack[top] = 10;
			++top;
			stack[top] = 30;
			++top;
			stack[top] = 37;
			++top;
			stack[top] = 29;
			++top;
			stack[top] = 28;
			++top;
			stack[top] = 49;
			++top;
			stack[top] = 27;
			++top;
			stack[top] = 13;
		}
		else {
			parserError();
		}
		break;
	case 44:
		if (lookahead == 14) {
			cout << "<loop> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 17" << endl;
			stack[top] = 30;
			++top;
			stack[top] = 37;
			++top;
			stack[top] = 29;
			++top;
			stack[top] = 28;
			++top;
			stack[top] = 49;
			++top;
			stack[top] = 27;
			++top;
			stack[top] = 14;
			++top;
			stack[top] = 15;
			++top;
			stack[top] = 14;
		}
		else {
			parserError();
		}
		break;
	case 45:
		if (lookahead == 16) {
			cout << "<output> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 18" << endl;
			stack[top] = 46;
			++top;
			stack[top] = 16;
		}
		else if (lookahead == 17) {
			cout << "<output> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 19" << endl;
			stack[top] = 3;
			++top;
			stack[top] = 17;
		}
		else {
			parserError();
		}
		break;
	case 46:
		if (lookahead == 1) {
			cout << "<ids> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 20" << endl;
			stack[top] = 47;
			++top;
			stack[top] = 1;
		}
		else {
			parserError();
		}
		break;
	case 47:
		if (lookahead == 1) {
			cout << "<more-ids> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 21" << endl;
			stack[top] = 47;
			++top;
			stack[top] = 1;
		}
		else if (lookahead == 11 || lookahead == 12 || lookahead == 28) {
			cout << "<more-ids> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 22" << endl;
			stack[top] = -1;
			--top;
		}
		else {
			parserError();
		}
		break;
	case 48:
		if (lookahead == 18 || lookahead == 19 || lookahead == 20 || lookahead == 23 || lookahead == 9 || lookahead == 24) {
			cout << "<expr> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 23" << endl;
			stack[top] = 49;
		}
		else if (lookahead == 1 || lookahead == 2 || lookahead == 32) {
			cout << "<expr> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 24" << endl;
			stack[top] = 52;
		}
		else {
			parserError();
		}
		break;
	case 49:
		if (lookahead == 18){
			cout << "<bool> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 25" << endl;
			stack[top] = 50;
			++top;
			stack[top] = 18;
		}
		else if (lookahead == 19) {
			cout << "<bool> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 26" << endl;
			stack[top] = 50;
			++top;
			stack[top] = 19;
		}
		else if (lookahead == 20) {
			cout << "<bool> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 27" << endl;
			stack[top] = 49;
			++top;
			stack[top] = 20;
		}
		else if (lookahead == 23 || lookahead == 9 || lookahead == 24) {
			cout << "<bool> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 28" << endl;
			stack[top] = 31;
			++top;
			stack[top] = 52;
			++top;
			stack[top] = 52;
			++top;
			stack[top] = 51;
		}
		else {
			parserError();
		}
		break;
	case 50:
		if (lookahead == 21) {
			cout << "<bool-tail> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 29" << endl;
			stack[top] = 49;
			++top;
			stack[top] = 21;
		}
		else if (lookahead == 22) {
			cout << "<bool-tail> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 30" << endl;
			stack[top] = 49;
			++top;
			stack[top] = 22;
		}
		else if (lookahead == 28) {
			cout << "<bool-tail> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 31" << endl;
			stack[top] = -1;
			--top;
		}
		else {
			parserError();
		}
		break;
	case 51:
		if (lookahead == 23) {
			cout << "<test> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 32" << endl;
			stack[top] = 23;
		}
		else if (lookahead == 9) {
			cout << "<test> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 33" << endl;
			stack[top] = 9;
		}
		else if (lookahead == 24) {
			cout << "<test> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 34" << endl;
			stack[top] = 24;
		}
		else {
			parserError();
		}
		break;
	case 52:
		if (lookahead == 1) {
			cout << "<arith> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 35" << endl;
			stack[top] = 53;
			++top;
			stack[top] = 1;
		}
		else if (lookahead == 2) {
			cout << "<arith> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 36" << endl;
			stack[top] = 53;
			++top;
			stack[top] = 2;
		}
		else if (lookahead == 32) {
			cout << "<arith> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 37" << endl;
			stack[top] = 53;
			++top;
			stack[top] = 33;
			++top;
			stack[top] = 52;
			++top;
			stack[top] = 32;
		}
		else {
			parserError();
		}
		break;
	case 53:
		if (lookahead == 25) {
			cout << "<arith> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 38" << endl;
			stack[top] = 52;
			++top;
			stack[top] = 25;
		}
		else if (lookahead == 26) {
			cout << "<arith> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 39" << endl;
			stack[top] = 52;
			++top;
			stack[top] = 26;
		}
		else if (lookahead == 28 || lookahead == 1 || lookahead == 2 || lookahead == 32 || lookahead == 31 || lookahead == 33) {
			cout << "<arith> (" << stack[top] << ")" << "\t\t" << "" << look << " (" << lookahead << ")" << "\t\t" << "Use Rule 40" << endl;
			stack[top] = -1;
			--top;
		}
		else {
			parserError();
		}
		break;
	default:
		parserError();
		break;
	}
}

void q1() {
	cout << "Z0 (" << stack[top] << ")" << "\t\t" << "- (" << stack[top] << ")" << "\t\t" << "Accept\n" << endl;
	isConsumed = true;
	//Print Symbol Table
	cout << "Symbol Table: " << endl;
	for (int i = 0; i < tableind; i++) {
		symtab[i].print();
	}
}

void parserError()
{
	ErrorHandler(2);
	cout << "Error on line " << line << endl;
	isConsumed = true;
}
#pragma endregion

