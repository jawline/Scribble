/*
 * JumpTypes.hpp
 *
 *  Created on: 15 Jun 2013
 *      Author: blake
 */

#ifndef JUMPTYPES_HPP_
#define JUMPTYPES_HPP_

namespace VM {

enum JumpType {
    DirectRelative = 0, DirectExact, RegisterRelative, RegisterExact
};

}

#endif /* JUMPTYPES_HPP_ */
