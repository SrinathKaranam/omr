/*******************************************************************************
 *
 * (c) Copyright IBM Corp. 2016
 *
 *  This program and the accompanying materials are made available
 *  under the terms of the Eclipse Public License v1.0 and
 *  Apache License v2.0 which accompanies this distribution.
 *
 *      The Eclipse Public License is available at
 *      http://www.eclipse.org/legal/epl-v10.html
 *
 *      The Apache License v2.0 is available at
 *      http://www.opensource.org/licenses/apache2.0.php
 *
 * Contributors:
 *    Multiple authors (IBM Corp.) - initial implementation and documentation
 *******************************************************************************/

#include "ddr/ir/Type.hpp"

Type::Type(SymbolKind symbolKind, size_t size)
	: _symbolKind(symbolKind), _sizeOf(size), _isDuplicate(false)
{
}

Type::~Type() {}

SymbolKind
Type::getSymbolKind()
{
	return _symbolKind;
}

bool
Type::isAnonymousType()
{
	return false;
}

bool
operator==(Type const& lhs, Type const& rhs)
{
	set <Type const*> checked;
	return lhs.equal(rhs, &checked);
}

bool
Type::equal(Type const& type, set<Type const*> *checked) const
{
	return checked->find(this) != checked->end()
		|| ((_name == (type._name))
		&& (_sizeOf == type._sizeOf)
		&& (_symbolKind == type._symbolKind));
}

void
Type::replaceType(Type *typeToReplace, Type *replaceWith)
{
	/* Nothing to replace in base types. */
}

string
Type::getFullName()
{
	return _name;
}

string
Type::getSymbolKindName()
{
	return "";
}

DDR_RC
Type::scanChildInfo(Scanner *scanner, void *data)
{
	return scanner->dispatchScanChildInfo(this, data);
}

DDR_RC
Type::enumerateType(BlobGenerator *blobGenerator, bool addFieldsOnly)
{
	return blobGenerator->dispatchEnumerateType(this, addFieldsOnly);
}

DDR_RC
Type::buildBlob(BlobGenerator *blobGenerator, bool addFieldsOnly, string prefix)
{
	return blobGenerator->dispatchBuildBlob(this, addFieldsOnly, prefix);
}

DDR_RC
Type::printToSuperset(SupersetGenerator *supersetGenerator, bool addFieldsOnly, string prefix = "")
{
	return supersetGenerator->dispatchPrintToSuperset(this, addFieldsOnly, prefix);
}

DDR_RC
Type::checkDuplicate(Symbol_IR *ir)
{
	/* No-op: since Types aren't printed, there's no need to check if they're duplicates either */
	return DDR_RC_OK;
}