#pragma once
class statement
{
	enum class type {
		BLOCK,
		ITE, //If Then Else
		FOR,
		WHILE,
		DECLERATION,
		ASSIGNMENT,
		VOID_FUNC,
	};
};

