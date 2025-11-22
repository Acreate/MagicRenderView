#ifndef INFOSTACKGENERATE_H_H_HEAD__FILE__
#define INFOSTACKGENERATE_H_H_HEAD__FILE__
#pragma once
#include <qstring.h>

class InfoStack;
class InfoStackGenerate {
	friend class VarGenerate;
	static InfoStack * generateInfoStack( const QString &type_name, const std::vector< QString > &alias_type_name_s, const std::function< void*( ) > &create_function, const std::function< void ( void * ) > &delete_function );
};

#endif // INFOSTACKGENERATE_H_H_HEAD__FILE__
