/*
 * ScriptedFunction.hpp
 *
 *  Created on: 9 Mar 2013
 *      Author: blake
 */

#ifndef SCRIPTEDFUNCTION_HPP_
#define SCRIPTEDFUNCTION_HPP_
#include <API/Function.hpp>
#include <Scribble/Statement/Statement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Value/Variable.hpp>
#include <Scribble/Parser/TypeReference.hpp>
#include <SASM/Parser.hpp>

namespace ScribbleCore {

class ScriptedFunction: public Function {
private:
	TypeReference fType_;SmartPointer<Variable> templateReturn_;
	std::vector<SmartPointer<Statement>> statements_;
	std::vector<SmartPointer<Variable>> variableTemplates_;
	std::vector<SmartPointer<Variable>> arguments_;

public:

	ScriptedFunction(std::string name, int version, std::string nameSpace, TypeReference functionType,
			SmartPointer<Variable> templateReturn,
			std::vector<SmartPointer<Statement>> statements,
			std::vector<SmartPointer<Variable>> variableTemplates,
			std::vector<SmartPointer<Variable>> variables);

	virtual ~ScriptedFunction();

	Type* getType();

	const unsigned int numArgs();
	Type* argType(unsigned int arg);
	void check();

	int debugCode(std::stringstream& gen);

	SmartPointer<VM::VMFunc> generateScriptedFunc() {

		std::stringstream code;

		debugCode(code);
		code << "load 0 $" << VM::vmReturnResultRegister << "\n";
		code << "ret\n";

		VM::InstructionSet instructions = SimpleASM::Parser::parse(
				code.str().c_str());

		return SmartPointer<VM::VMFunc>( new VM::VMFunc(getName(), instructions) );
	}

	bool isNativeFunction() {
		return false;
	}
};

}

#endif /* SCRIPTEDFUNCTION_HPP_ */
