#ifndef _SHA3_DEF_H_
#define _SHA3_DEF_H_
#include <string>
#include "keccak.h"

#define sha3_hash keccak

std::string sha3_text(std::string input, unsigned int outputLength);

#endif //_SHA3_DEF_H_
