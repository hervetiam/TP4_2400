class CommandeAbs
{
public: 
	CommandeAbs() = default; 
	virutal ~CommandeAbs() = default; 
	virtual void excecute() = 0; 
	virtual void redo() = 0;
	virtual void undo() = 0;

};