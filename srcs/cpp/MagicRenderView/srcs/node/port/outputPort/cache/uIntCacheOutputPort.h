#ifndef UINTCACHEOUTPUTPORT_H_H_HEAD__FILE__
#define UINTCACHEOUTPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeOutputPort.h"
#include "../unityTypeOutputPort.h"

class UIntCacheOutputPort : public CacheTypeOutputPort {
	Q_OBJECT;
public:
	UIntCacheOutputPort( const QString &name )
		: CacheTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // UINTCACHEOUTPUTPORT_H_H_HEAD__FILE__
