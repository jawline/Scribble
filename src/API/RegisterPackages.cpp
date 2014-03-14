/*
 * RegisterPackages.cpp
 *
 *  Created on: 26 Dec 2013
 *      Author: blake
 */

#include "RegisterPackages.hpp"
#include <Scribble/Value/StructureInfo.hpp>
#include <SASM/Parser.hpp>

std::string outputCode(ScribbleCore::NamespaceType names,
		VM::VirtualMachine& vm) {

	std::stringstream packageCode;

	for (auto iterator = names.begin(); iterator != names.end(); iterator++) {

		if (iterator->second.type() == ScribbleCore::FunctionSetEntry) {

			ScribbleCore::FunctionSet functionSet =
					iterator->second.getFunctionSet();

			for (unsigned int i = 0; i < functionSet.size(); i++) {
				SmartPointer<Function> function = functionSet[i];

				if (!function->isNativeFunction()) {
					packageCode << function->getName() << " {\n";
					function->debugCode(packageCode);
					packageCode << "}\n\n";
				}

			}

		}

	}

	return packageCode.str();
}

void registerPackages(
		std::map<std::string, ScribbleCore::NamespaceType>& allNames,
		VM::VirtualMachine& vm) {

	std::vector<std::pair<std::string, SmartPointer<VM::VMStructureField>>>postResolveList;

	for (auto selectedNamespaceIter = allNames.begin();
			selectedNamespaceIter != allNames.end(); selectedNamespaceIter++) {

		std::string packageCode = outputCode(selectedNamespaceIter->second, vm);

		vm.logMessage(VM::Log, std::string("----BEGIN NAMESPACE ") + selectedNamespaceIter->first + "----\n" + packageCode + "\n----END NAMESPACE----\n\n");

		VM::VMNamespace newSpace = SimpleASM::Parser::parse(packageCode);

		ScribbleCore::NamespaceType names = selectedNamespaceIter->second;

		for (auto iterator = names.begin(); iterator != names.end();
				iterator++) {

			if (iterator->second.type() == ScribbleCore::FunctionSetEntry) {

				ScribbleCore::FunctionSet functionSet = iterator->second.getFunctionSet();

				for (unsigned int i = 0; i < functionSet.size(); i++) {

					SmartPointer<Function> function = functionSet[i];

					if (function->isNativeFunction()) {
						newSpace.insert(function->getName(), VM::NamespaceEntry(API::Function::getNativeFunction(function)));
					}

				}

			} else if (iterator->second.type() == ScribbleCore::TypeEntry) {

				if (iterator->second.getType()->type->getType() == ScribbleCore::StructureType) {
					vm.logMessage(VM::Log, std::string("Registering Type ") + selectedNamespaceIter->first + VM::vmNamespaceSeperator + iterator->first + " {\n");

					ScribbleCore::TypeReference type = iterator->second.getType();
					ScribbleCore::StructureInfo* info = (ScribbleCore::StructureInfo*) iterator->second.getType()->type;

					std::vector<SmartPointer<VM::VMStructureField>> fields;

					for (unsigned int i = 0; i < info->getNumIndexs(); i++) {

						ScribbleCore::Type* fieldType = info->getIndex(i).second->type;

						std::string fullTypeName = fieldType->getTypeName();

						vm.logMessage(VM::Log, info->getIndex(i).first + " : " + fullTypeName + "\n");

						SmartPointer<VM::VMStructureField> newField = SmartPointer<VM::VMStructureField>(new VM::VMStructureField(info->getIndex(i).first, nullptr));
						postResolveList.push_back(std::pair<std::string, SmartPointer<VM::VMStructureField>>(fullTypeName, newField));
						fields.push_back( newField );
					}

					newSpace.insert(info->getName(), VM::NamespaceEntry(SmartPointer<VM::VMEntryType>(new VM::VMEntryType(info->getName(), fields))));

					vm.logMessage(VM::Log, "}\n");
					vm.logMessage(VM::Log, std::string("Registered type ") + info->getName() + " inside " + selectedNamespaceIter->first + "\n");
				}

			}

		}

		vm.registerEntry(selectedNamespaceIter->first,
				VM::NamespaceEntry(newSpace));

	}

	for (auto iter = postResolveList.begin(); iter != postResolveList.end(); iter++) {

		auto resolvedType = vm.findType(iter->first);

		if (resolvedType.get() != nullptr) {
			vm.logMessage(VM::Log, std::string("Resolved type ") + resolvedType->typeName() + "\n");
			iter->second->setType(vm.findType(iter->first));
		} else {
			printf("FATAL ERROR: Type could not be resolved ( %s not registered )", iter->first.c_str());
			exit(-1);
		}

	}

}

