#ifndef TYPEENUM_H_H_HEAD__FILE__
#define TYPEENUM_H_H_HEAD__FILE__
#pragma once
#include <QObject>
namespace TypeEnum {
	enum class Type {
		Unity,
		Array,
		Struct,
		Pair
	};
	bool converEnum( const QString &enum_string, Type &result_enum_type_var );
	bool converQString( const Type &enum_type_var, QString &result_enum_string );
	Q_NAMESPACE;
	Q_ENUM_NS( Type );
}

#endif // TYPEENUM_H_H_HEAD__FILE__
