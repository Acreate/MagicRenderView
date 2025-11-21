#ifndef INFOSTACK_H_H_HEAD__FILE__
#define INFOSTACK_H_H_HEAD__FILE__
#pragma once
#include <vector>
#include <functional>
#include <qstring.h>
class InfoStack {
	QString typeName;
	std::function< void*( ) > createFunction;
	std::function< void ( void *p ) > deleteFunction;
	std::vector< void * > stackVarPtr;
public:
	virtual const void * createTypePtr( );
	virtual bool deleteTypePtr( const void *delete_obj_ptr );
};

#endif // INFOSTACK_H_H_HEAD__FILE__
