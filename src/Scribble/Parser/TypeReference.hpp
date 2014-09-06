/*
 * TypeReference.hpp
 *
 *  Created on: 31 May 2013
 *      Author: blake
 */

#ifndef TYPEREFERENCE_HPP_
#define TYPEREFERENCE_HPP_
#include <Pointers/SmartPointer.hpp>
#include <string>
#include <Scribble/Value/Type.hpp>

namespace ScribbleCore {

//TODO: Make this a class, It's used to often not to be one

class TypeReferenceCore {
private:
	std::string typeNamespace_;
	std::string name_;
	Type* type_;

public:
	TypeReferenceCore(std::string name, Type* type);
	TypeReferenceCore(std::string ns, std::string name, Type* type);

	std::string getNamespace() const;
	std::string getName() const;
	Type* type() const;
	void setType(Type* type) {
		type_ = type;
	}

	void setNamespace(std::string const& ns) {
		typeNamespace_ = ns;
	}

};

typedef SmartPointer<TypeReferenceCore> TypeReference;

TypeReference makeTypeReference(Type* type);

}

#endif /* TYPEREFERENCE_HPP_ */
