#include "SasmException.hpp"

SasmException::SasmException(std::string error) {
    error_ = error;
}

SasmException::~SasmException() throw () {
}
