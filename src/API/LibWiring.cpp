#include "LibWiring.hpp"
#include <wiringPi.h>

bool isSetup = false;

APIValue Setup(API::APIValue* values, VM::VirtualMachine* virt) {

	if (!isSetup) {
		wiringPiSetup();
	}

	isSetup = true;
	return API::APIValue();
}

APIValue SetMode(API::APIValue* values, VM::VirtualMachine* virt) {

	int mode = values[1].getValueBoolean() ? OUTPUT : INPUT;
	printf("Setting mode to %i\n", mode);
	pinMode(values[0].getValue32(), mode);
    return API::APIValue();
}

APIValue Read(API::APIValue* values, VM::VirtualMachine* virt) {
	printf("Reading %i %i\n", values[0].getValue32(), digitalRead(values[0].getValue32()) == HIGH ? true : false);
    return API::APIValue::makeBoolean(digitalRead(values[0].getValue32()) == HIGH ? true : false);
}

APIValue Write(API::APIValue* values, VM::VirtualMachine* virt) {
	digitalWrite(values[0].getValue32(), values[1].getValueBoolean() ? HIGH : LOW);
    return API::APIValue();
}

void generateLibWiringPackage(
    std::map<std::string, ScribbleCore::NamespaceType>& all) {

    ScribbleCore::NamespaceType wiring;

    std::vector<ScribbleCore::TypeReference> args;

    std::vector<SafeFunction> setup;

     setup.push_back(
         SmartPointer < API::APIFunction
         > (new API::APIFunction("Setup", "libWiring",
                                 ScribbleCore::FunctionSignature(args,
                                         ScribbleCore::makeTypeReference(
                                             ScribbleCore::getVoidType())),
                                 Setup)));

     wiring["Setup"] = ScribbleCore::NamespaceEntry(setup);

    args.push_back(ScribbleCore::makeTypeReference(ScribbleCore::getIntType()));
    args.push_back(ScribbleCore::makeTypeReference(ScribbleCore::getBooleanType()));

    std::vector<SafeFunction> setmode;

    setmode.push_back(
        SmartPointer < API::APIFunction
        > (new API::APIFunction("SetMode", "libWiring",
                                ScribbleCore::FunctionSignature(args,
                                        ScribbleCore::makeTypeReference(
                                            ScribbleCore::getVoidType())),
                                SetMode)));

    wiring["SetMode"] = ScribbleCore::NamespaceEntry(setmode);

    std::vector<SafeFunction> writeio;

    writeio.push_back(
        SmartPointer < API::APIFunction
        > (new API::APIFunction("Write", "libWiring",
                                ScribbleCore::FunctionSignature(args,
                                        ScribbleCore::makeTypeReference(
                                            ScribbleCore::getVoidType())),
                                Write)));

    wiring["Write"] = ScribbleCore::NamespaceEntry(writeio);

    args.clear();
    args.push_back(ScribbleCore::makeTypeReference(ScribbleCore::getIntType()));

    std::vector<SafeFunction> read;

    read.push_back(
        SmartPointer < API::APIFunction
        > (new API::APIFunction("Read", "libWiring",
                                ScribbleCore::FunctionSignature(args,
                                        ScribbleCore::makeTypeReference(
                                            ScribbleCore::getBooleanType())),
                                Read)));

    wiring["Read"] = ScribbleCore::NamespaceEntry(read);

    all["libWiring"] = wiring;
}
