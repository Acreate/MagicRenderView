#ifndef FLOATCACHEINPUTPORT_H_H_HEAD__FILE__
#define FLOATCACHEINPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeInputPort.h"

class FloatCacheInputPort : public CacheTypeInputPort {
	Q_OBJECT;
public:
	FloatCacheInputPort( const QString &name )
		: CacheTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // FLOATCACHEINPUTPORT_H_H_HEAD__FILE__
