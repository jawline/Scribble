/*
 * FloatStatement.cpp
 *
 *  Created on: 16 Nov 2013
 *      Author: blake
 */

#include "Float32Statement.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

Float32Statement::Float32Statement(int yylineno, std::string yysym,
		float32_t val) :
		Statement(yylineno, yysym), val_(val) {
	// TODO Auto-generated constructor stub

}

Float32Statement::~Float32Statement() {
	// TODO Auto-generated destructor stub
}

Type* Float32Statement::type() {
	return getFloat32Type();
}

void Float32Statement::checkTree(Type* functionType) {
}

int Float32Statement::generateCode(int resultRegister, std::stringstream& generated) {
	generated << "load " << val_ << "f $" << resultRegister << "\n";
	return 1;
}

}
