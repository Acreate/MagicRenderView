#ifndef NODERUNFUNCTIONTYPEINFO_H_H_HEAD__FILE__
#define NODERUNFUNCTIONTYPEINFO_H_H_HEAD__FILE__
#pragma once
#include <qstring.h>

class NodeRunFunctionTypeInfo {
	QString typeName;
	std::function< void( void * ) > release;
	void *ptr;
public:
	NodeRunFunctionTypeInfo( void *const ptr, const QString &type_name, const std::function< void( void * ) > &release )
		: typeName( type_name ),
		release( release ),
		ptr( ptr ) { }
	virtual ~NodeRunFunctionTypeInfo( ) {
		if( release )
			release( ptr );
	}
	virtual const QString & getTypeName( ) const { return typeName; }
	virtual const std::function< void( void * ) > & getRelease( ) const { return release; }
	virtual void * getPtr( ) const { return ptr; }
};

#endif // NODERUNFUNCTIONTYPEINFO_H_H_HEAD__FILE__
