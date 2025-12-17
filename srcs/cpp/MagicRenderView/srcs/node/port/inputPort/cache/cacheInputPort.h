#ifndef CACHEINPUTPORT_H_H_HEAD__FILE__
#define CACHEINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../cacheTypeInputPort.h"

class CacheInputPort : public  CacheTypeInputPort{
	Q_OBJECT;
public:
	CacheInputPort( const QString &name )
		: CacheTypeInputPort( name ) { }
};

#endif // CACHEINPUTPORT_H_H_HEAD__FILE__
