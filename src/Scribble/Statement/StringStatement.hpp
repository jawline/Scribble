#ifndef _STR_STATEMENT_DEF_H_
#define _STR_STATEMENT_DEF_H_
#include "Statement.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

class StringStatement: public Statement {
  private:
    std::string stringValue_;

  public:
    StringStatement(int lineNo, std::string sym, std::string stringValue);

    TypeReference type() {
        return makeTypeReference(getTypeManager().getType(StringType));
    }

    void checkTree(Type* functionType);
    int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif //_STR_STATEMENT_DEF_H_
