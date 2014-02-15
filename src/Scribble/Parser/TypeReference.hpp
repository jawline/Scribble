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

struct TypeReferenceCore {

	TypeReferenceCore(std::string name, Type* type) {
		this->typeNamespace = "";
		this->name = name;
		this->type = type;
	}

	TypeReferenceCore(std::string ns, std::string name, Type* type) {
		this->typeNamespace = ns;
		this->name = name;
		this->type = type;
	}

	std::string typeNamespace;
	std::string name;
	Type* type;


};

typedef SmartPointer<TypeReferenceCore> TypeReference;

}

#endif /* TYPEREFERENCE_HPP_ */
