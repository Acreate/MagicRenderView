#ifndef VARTYPEGENERATE_H_H_HEAD__FILE__
#define VARTYPEGENERATE_H_H_HEAD__FILE__
#pragma once

class QString;
class QObject;
class VarType;
class VarTypeGenerate {
public:
	static VarType * templateVarType( QObject *parent, const QString &type_name );
	template< typename TType_Name >
	static VarType * templateVarType( QObject *parent ) {
		return templateVarType( parent, typeid( TType_Name ).name( ) );
	}
};

#endif // VARTYPEGENERATE_H_H_HEAD__FILE__
