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

	std::string const& getName() {
		return name_;
	}

	std::string const& getNamespace() {
		return fnNamespace_;
	}

	std::string const& getResolveIssue() {
		return resolveIssue_;
	}

	std::string getDebugName() {
		if (getNamespace().size() > 0) {
			return getNamespace() + "." + getName();
		} else {
			return getName();
		}
	}

	std::vector<SafeStatement> const& getArgs() {
		return fnArgs_;
	}

	void setResolveIssue(std::string issue) {
		resolveIssue_ = issue;
	}

	SmartPointer<Function> getFunction() {
		return func_;
	}

	void setFunction(SmartPointer<Function> func) {
		func_ = func;
	}
};

#endif /* FUNCTIONREFERENCE_HPP_ */
