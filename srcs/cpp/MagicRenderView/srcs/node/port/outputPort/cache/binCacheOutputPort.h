#ifndef BINCACHEOUTPUTPORT_H_H_HEAD__FILE__
#define BINCACHEOUTPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeOutputPort.h"

class BinCacheOutputPort : public CacheTypeOutputPort {
	Q_OBJECT;
public:
	BinCacheOutputPort( const QString &name )
		: CacheTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // BINCACHEOUTPUTPORT_H_H_HEAD__FILE__
