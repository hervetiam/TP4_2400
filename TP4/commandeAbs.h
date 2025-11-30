#ifndef COMMANDEABS_H
#define COMMANDEABS_H

using namespace std;

class CommandeAbs
{
public: 
	CommandeAbs() = default; 
	virtual ~CommandeAbs() = default; 
	virtual void execute() = 0; 
	virtual void cancel() = 0;

};
#endif