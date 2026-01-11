#ifndef UINTCACHEINPUTPORT_H_H_HEAD__FILE__
#define UINTCACHEINPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeInputPort.h"

class UIntCacheInputPort : public CacheTypeInputPort {
	Q_OBJECT;
public:
	UIntCacheInputPort( const QString &name )
		: CacheTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // UINTCACHEINPUTPORT_H_H_HEAD__FILE__
