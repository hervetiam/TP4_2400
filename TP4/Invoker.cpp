#include "Invoker.h"

Invoker::Invoker() {}

Invoker::~Invoker() {
	for (auto cmd : m_cmdDone) {
		delete cmd;
	}
	for (auto cmd : m_cmdUndone) {
		delete cmd;
	}
}
void Invoker::execute(CommandeAbs* cmd)
{

	cmd->execute();
	m_cmdDone.push_back(cmd);
	m_cmdUndone.clear();
}


void Invoker::undo()
	{
		if (m_cmdDone.empty())
		{
			return;
		}
		CommandeAbs* cmd = m_cmdDone.back();
		cmd->cancel();
		m_cmdUndone.push_back(cmd);
		m_cmdDone.pop_back();
}

void Invoker::redo()
	{
		if (m_cmdUndone.empty())
		{
			return;
		}

		CommandeAbs* cmd = m_cmdUndone.back();
		cmd->execute();

		m_cmdDone.push_back(cmd);
		m_cmdUndone.pop_back();
}
