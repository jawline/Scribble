/*
 * BoolStatement.hpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#ifndef BOOLSTATEMENT_HPP_
#define BOOLSTATEMENT_HPP_
#include "Statement.hpp"

namespace ScribbleCore {

/**
 * Returns a boolean value.
 */

class BoolStatement: public Statement {
private:

	/**
	 * The value to generate.
	 */

	bool value_;

public:

	/**
	 * Create a Bool statement
	 * @param value The value to set the boolean to.
	 */

	BoolStatement(int lineNo, std::string sym, bool value);
	virtual ~BoolStatement();

	/**
	 * Returns a boolean
	 * @return Boolean
	 */
	TypeReference type();

	void checkTree(Type* functionType);
	virtual int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif /* BOOLSTATEMENT_HPP_ */
