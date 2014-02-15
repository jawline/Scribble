#ifndef _VARIABLE_H_
#define _VARIABLE_H_
#include <Scribble/Parser/TypeReference.hpp>
#include <Pointers/SmartPointer.hpp>
#include <map>

namespace ScribbleCore {

/**
 * The variable class is used to store meta data about a
 * variable when it is defined in a package function ( It's type
 * and position in registers )
 */

class Variable {
private:
	TypeReference type_;
	int position_;

public:

	Variable(int position, TypeReference type);
	~Variable();

	Type* getType();
	void setType(Type* type);

	void setPosition(int pos);
	int getPosition();

};

}

#endif //_VARIABLE_H_
