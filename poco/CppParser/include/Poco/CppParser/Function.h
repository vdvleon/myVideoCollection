//
// Function.h
//
// $Id: //poco/1.4/CppParser/include/Poco/CppParser/Function.h#1 $
//
// Library: CppParser
// Package: SymbolTable
// Module:  Function
//
// Definition of the Function class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef CppParser_Function_INCLUDED
#define CppParser_Function_INCLUDED


#include "Poco/CppParser/CppParser.h"
#include "Poco/CppParser/Decl.h"
#include <vector>


namespace Poco {
namespace CppParser {


class Parameter;


class CppParser_API Function: public Decl
	/// This class represents a (member) function declaration.
{
public:
	enum Flags
	{
		FN_STATIC       = 1,  /// The function is static.
		FN_VIRTUAL      = 2,  /// The function is virtual.
		FN_INLINE       = 4,  /// The function is inline.
		FN_CONST        = 8,  /// The function is const.
		FN_TEMPLATE     = 16, /// The function is a template.
		FN_PURE_VIRTUAL = 32  /// The function is pure virtual.
	};
	
	typedef std::vector<Parameter*> Parameters;
	typedef Parameters::const_iterator Iterator;

	Function(const std::string& decl, NameSpace* pNameSpace);
		/// Creates the Function.

	~Function();
		/// Destroys the Function.

	void addParameter(Parameter* pParam);
		/// Adds a parameter to the function.

	const std::string& getReturnParameter() const;

	Iterator begin() const;
		/// Returns an iterator for iterating over the Function's Parameter's.

	Iterator end() const;
		/// Returns an iterator for iterating over the Function's Parameter's.
	
	void makeInline();
		/// Sets the FN_INLINE flag.
	
	void makeConst();
		/// Sets the FN_CONST flag.
		
	void makePureVirtual();
		/// Sets the FN_PURE_VIRTUAL flag.
	
	int flags() const;
		/// Returns the function's flags.
		
	bool isConstructor() const;
		/// Returns true iff the function is a constructor.
		
	bool isDestructor() const;
		/// Returns true iff the function is a destructor.

	bool isMethod() const;
		/// Returns true iff the function is a method (it's part of
		/// a Struct and it's neither a constructor nor a destructor).
		
	bool isFunction() const;
		/// Returns true iff the function is not a member of a class
		/// (a freestanding function).

	bool isConst() const;
		/// Returns true iff the method is const.
		
	int countParameters() const;
		/// Returns the number of parameters.
	
	std::string signature() const;
		/// Returns the signature of the function.
		
	bool isVirtual() const;
		/// Returns true if the method is virtual. Also examines base
		/// classes to check for a virtual function with the same
		/// signature.
		
	Function* getOverridden() const;
		/// If the function is virtual and overrides a function in a
		/// base class, the base class function is returned.
		/// Otherwise, null is returned.
		
	Symbol::Kind kind() const;
	std::string toString() const;

private:
	Parameters  _params;
	int         _flags;
	std::string _retParam;
};


//
// inlines
//
inline int Function::flags() const
{
	return _flags;
}


inline const std::string& Function::getReturnParameter() const
{
	return _retParam;
}


inline bool Function::isConst() const
{
	return (flags() & FN_CONST) != 0;
}


} } // namespace Poco::CppParser


#endif // CppParser_Function_INCLUDED
