/*
 * TypeReference.cpp
 *
 *  Created on: 26 Mar 2014
 *      Author: blake
 */

#include "TypeReference.hpp"

namespace ScribbleCore {

TypeReference makeTypeReference(Type* type) {
	return TypeReference(new TypeReferenceCore(type->getTypeName(), type));
}

}

