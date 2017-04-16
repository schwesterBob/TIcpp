#ifndef TLOCATION_H_
#define TLOCATION_H_

#include <string>

using namespace std;

class TLocation {

private:
	string section;
	string rack;
public:
	TLocation();
	TLocation(string, string);
	void print();
	string getSection();
	string getRack();
	~TLocation();
};

#endif /* TLOCATION_H_ */
