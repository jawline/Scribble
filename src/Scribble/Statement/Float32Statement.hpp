/*
 * FloatStatement.hpp
 *
 *  Created on: 16 Nov 2013
 *      Author: blake
 */

#ifndef FLOATSTATEMENT_HPP_
#define FLOATSTATEMENT_HPP_
#include "Statement.hpp"
#include <types.h>

class Float32Statement: public Statement {
private:
	float32_t val_;

public:
	Float32Statement(int lineNo, std::string sym, float32_t val);
	virtual ~Float32Statement();

	Value* execute(std::vector<Value*> const& variables);
	Type* type();
	void checkTree(Type* functionType);
};

#endif /* FLOATSTATEMENT_HPP_ */
