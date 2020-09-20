#pragma once
class Command
{
public:
	Command(void);
	~Command(void);
	virtual void perform() = 0;
	virtual void rollback() = 0;
};

