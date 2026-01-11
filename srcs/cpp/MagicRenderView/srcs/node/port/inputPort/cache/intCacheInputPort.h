#ifndef INTCACHEINPUTPORT_H_H_HEAD__FILE__
#define INTCACHEINPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeInputPort.h"

class IntCacheInputPort : public CacheTypeInputPort {
	Q_OBJECT;
public:
	IntCacheInputPort( const QString &name )
		: CacheTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // INTCACHEINPUTPORT_H_H_HEAD__FILE__
