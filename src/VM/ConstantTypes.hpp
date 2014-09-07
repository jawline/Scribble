/*
 * ConstantTypes.hpp
 *
 *  Created on: 15 Jun 2013
 *      Author: blake
 */

#ifndef CONSTANTTYPES_HPP_
#define CONSTANTTYPES_HPP_

namespace VM {

/**
 * The different types which can be loaded by a constant
 */

enum ConstantType {

	CByte = 0, CShort, CInt, CLong, CFloat32, CDouble, CArray
};

}

#endif /* CONSTANTTYPES_HPP_ */
