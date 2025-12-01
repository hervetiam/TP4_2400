#include "Invoker.h"

Invoker::Invoker() {}

Invoker::~Invoker() {
    for (auto cmd : m_cmdDone) delete cmd;
    for (auto cmd : m_cmdUndone) delete cmd;
}

void Invoker::execute(CommandeAbs* cmd)
{
    m_cmdDone.push_back(cmd);
    m_cmdUndone.clear();
    cmd->execute();
}

void Invoker::undo()
{
    if (m_cmdDone.empty()) return;

    CommandeAbs* cmd = m_cmdDone.back();
    m_cmdDone.pop_back();
    cmd->cancel();
    m_cmdUndone.push_back(cmd);
}

void Invoker::redo()
{
    if (m_cmdUndone.empty()) return;

    CommandeAbs* cmd = m_cmdUndone.back();
    m_cmdUndone.pop_back();
    m_cmdDone.push_back(cmd);
    cmd->execute();
}
