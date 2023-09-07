#pragma once
class expression
{
	enum class type {
		BOP,
		UOP,
		FUNC, //Not void
		CONDITIONAL
	};
};

class binaryOp : expression {

};

class unaryOp : expression {

};