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
#include <Value/Type.hpp>

struct TypeReferenceCore {

	TypeReferenceCore(std::string name, Type* type) {
		this->name = name;
		this->type = type;
	}

	std::string name;
	Type* type;


};

typedef SmartPointer<TypeReferenceCore> TypeReference;

#endif /* TYPEREFERENCE_HPP_ */
