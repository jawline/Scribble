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
	std::vector<SmartPointer<Statement>> statements_;
	std::vector<SmartPointer<Variable>> variableTemplates_;

public:

	ScriptedFunction(std::string name, int version, std::string nameSpace,
			std::vector<SmartPointer<Statement>> statements,
			std::vector<SmartPointer<Variable>> variableTemplates,FunctionSignature signature);

	virtual ~ScriptedFunction();

	void check() const;

	int debugCode(std::stringstream& gen);

	bool isNativeFunction() const;

	virtual APIValue execute(API::APIValue* values, VM::VirtualMachine* virt);
};

}

#endif /* SCRIPTEDFUNCTION_HPP_ */
