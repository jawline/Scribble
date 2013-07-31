/*
 * VMEntry.hpp
 *
 *  Created on: Jul 22, 2013
 *      Author: blake
 */

#ifndef VMENTRY_HPP_
#define VMENTRY_HPP_
#include "VMEntryType.hpp"

namespace VM {

struct VMEntry {
	SP<VMEntryType> type;
	unsigned int sizeBytes;
	uint8_t* pointer;
	bool flagged;
};

}
;

#endif /* VMENTRY_HPP_ */
