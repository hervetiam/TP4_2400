#ifndef INVOKER_H
#define INVOKER_H
#include "commandeAbs.h"
#include <list>             

using namespace std;

class Invoker
{

private:
	list<CommandeAbs*> m_cmdDone;
	list<CommandeAbs*> m_cmdUndone;

public: 
	Invoker();
	virtual ~Invoker();
	void execute(CommandeAbs* cmd);
	void undo();
	void redo();
};

#endif