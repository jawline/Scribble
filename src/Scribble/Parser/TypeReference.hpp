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

struct TypeReferenceCore {

	TypeReferenceCore(std::string name, Type* type);
	TypeReferenceCore(std::string ns, std::string name, Type* type);

	std::string typeNamespace;
	std::string name;
	Type* type;


};

typedef SmartPointer<TypeReferenceCore> TypeReference;

TypeReference makeTypeReference(Type* type);

}

#endif /* TYPEREFERENCE_HPP_ */
