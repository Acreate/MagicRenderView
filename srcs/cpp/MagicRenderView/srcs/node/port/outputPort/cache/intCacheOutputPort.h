#ifndef INTCACHEOUTPUTPORT_H_H_HEAD__FILE__
#define INTCACHEOUTPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeOutputPort.h"

class IntCacheOutputPort : public CacheTypeOutputPort {
	Q_OBJECT;
public:
	IntCacheOutputPort( const QString &name )
		: CacheTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // INTCACHEOUTPUTPORT_H_H_HEAD__FILE__
