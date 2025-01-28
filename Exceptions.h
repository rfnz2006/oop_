#pragma once

#include <exception>

class MyException : public std::exception
{
public:
	virtual const char* GetErrorText()const = 0;
	~MyException() {}
};

class AbilityAbsence : public MyException
{
public:
	virtual const char* GetErrorText()const override { return "No abilities!"; }
};

class IllegalShipPlacement : public MyException
{
public:
	virtual const char* GetErrorText()const override { return "Cannot place a ship close to or at an intersection with another ship!"; }
};

class OutOfBoundaries : public MyException
{
public:
	virtual const char* GetErrorText()const override { return "An attack beyond the boundaries of the field!"; }
};

class EmptyField : public MyException
{
public:
	virtual const char* GetErrorText()const override { return "Null Field height or width!"; }
};

class InvalidBombing : public MyException
{
public:
	virtual const char* GetErrorText()const override { return "Cannot make bombing!"; }
};

class OutOfShipSize : public MyException
{
public:
	virtual const char* GetErrorText()const override { return "Index out of ship size!"; }
};

class InternalError : public MyException
{
public:
	virtual const char* GetErrorText()const override { return "Something went wrong!"; }
};
