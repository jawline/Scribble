#include "IntStatement.hpp"
#include <sstream>

namespace ScribbleCore {

IntStatement::IntStatement(int lineNo, std::string sym, int intValue) :
    Statement(lineNo, sym) {
    intValue_ = intValue;
}

void IntStatement::checkTree(Type* functionType) {

}

int IntStatement::generateCode(int resultRegister,
                               std::stringstream& generated) {

    if (resultRegister != -1) {
        generated << "load " << intValue_ << " $" << resultRegister << "\n";
    }

    return 1;
}

}
