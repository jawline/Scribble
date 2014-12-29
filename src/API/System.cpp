/*
 * System.cpp
 *
 *  Created on: 26 Dec 2013
 *      Author: blake
 */

#include <API/APIFunction.hpp>
#include <API/StringFunction.hpp>
#include <API/Modulo.hpp>
#include <API/RandomInt.hpp>
#include <API/Concat.hpp>
#include <API/Int.hpp>
#include <API/Float.hpp>
#include <API/Pow.hpp>
#include <API/SquareRoot.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Parser/Parser.hpp>

void generateSystemPackage(
    std::map<std::string, ScribbleCore::NamespaceType>& builtin) {

    ScribbleCore::NamespaceType builtinFunctions;

    std::vector<SafeFunction> sqrt;
    std::vector<ScribbleCore::TypeReference> sqrtf32Args;

    sqrtf32Args.push_back(
        ScribbleCore::makeTypeReference(ScribbleCore::getFloat32Type()));

    sqrt.push_back(
        SmartPointer < Function
        > (new APIFunction("Sqrt", "sys",
                           ScribbleCore::FunctionSignature(sqrtf32Args,
                                   ScribbleCore::makeTypeReference(
                                       ScribbleCore::getFloat32Type())),
                           SquareRootFloat32)));

    builtinFunctions["Sqrt"] = ScribbleCore::NamespaceEntry(sqrt);

    std::vector<SafeFunction> concat;
    concat.push_back(SmartPointer < Function > (new Concat("sys")));
    builtinFunctions["Concat"] = ScribbleCore::NamespaceEntry(concat);

    std::vector<SafeFunction> intConvertor;
    intConvertor.push_back(
        SmartPointer < Function > (new IntFromFloat32("sys")));
    builtinFunctions["Int"] = intConvertor;

    std::vector<SafeFunction> floatConvertor;
    floatConvertor.push_back(
        SmartPointer < Function > (new Float32FromInt("sys")));
    builtinFunctions["Float32"] = floatConvertor;

    std::vector<SafeFunction> powInt;
    powInt.push_back(SmartPointer < Function > (new Pow("sys")));
    builtinFunctions["PowInt"] = powInt;

    std::vector<SafeFunction> powFloat;
    powFloat.push_back(SmartPointer < Function > (new PowFloat32("sys")));
    builtinFunctions["PowFloat"] = powFloat;

    std::vector<SafeFunction> string;

    string.push_back(
        SmartPointer < Function > (new IntToStringFunction("sys")));

    string.push_back(
        SmartPointer < Function > (new BoolToStringFunction("sys")));

    string.push_back(
        SmartPointer < Function > (new Float32ToStringFunction("sys")));

    builtinFunctions["String"] = ScribbleCore::NamespaceEntry(string);

    std::vector<SafeFunction> compare;
    compare.push_back(SmartPointer < Function > (new StringCompare("sys")));
    builtinFunctions["Compare"] = ScribbleCore::NamespaceEntry(compare);

    std::vector<SafeFunction> mod;
    mod.push_back(SmartPointer < Function > (new Modulo("sys")));
    builtinFunctions["Mod"] = ScribbleCore::NamespaceEntry(mod);

    std::vector<SafeFunction> randomInt;
    randomInt.push_back(SmartPointer < Function > (new RandomInt("sys")));
    builtinFunctions["RandomInt"] = ScribbleCore::NamespaceEntry(randomInt);

    builtin["sys"] = builtinFunctions;
}
