#ifndef FLOATCACHEOUTPUTPORT_H_H_HEAD__FILE__
#define FLOATCACHEOUTPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeOutputPort.h"

class FloatCacheOutputPort : public CacheTypeOutputPort {
	Q_OBJECT;
public:
	FloatCacheOutputPort( const QString &name )
		: CacheTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // FLOATCACHEOUTPUTPORT_H_H_HEAD__FILE__
