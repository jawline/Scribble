/*
 * FunctionReference.hpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#ifndef FUNCTIONREFERENCE_HPP_
#define FUNCTIONREFERENCE_HPP_
#include <Pointers/SmartPointer.hpp>
#include <Statement/Statement.hpp>
#include "Function.hpp"
#include <string>

class FunctionReference {
private:
	std::string name_;
	std::string fnNamespace_;
	std::string resolveIssue_;
	std::vector<SafeStatement> fnArgs_;
	SmartPointer<Function> func_;

public:
	FunctionReference(std::string fnNamespace, std::string name,
			std::vector<SafeStatement> fnArgs, SmartPointer<Function> func);
	virtual ~FunctionReference();

	std::string const& getName();
	std::string const& getNamespace();
	std::string const& getResolveIssue();
	std::string getDebugName();
	std::vector<SafeStatement> const& getArgs();
	void setResolveIssue(std::string issue);
	SmartPointer<Function> getFunction();
	void setFunction(SmartPointer<Function> func);
};

#endif /* FUNCTIONREFERENCE_HPP_ */
