#ifndef BINCACHEINPUTPORT_H_H_HEAD__FILE__
#define BINCACHEINPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeInputPort.h"

class BinCacheInputPort : public CacheTypeInputPort {
	Q_OBJECT;
public:
	BinCacheInputPort( const QString &name )
		: CacheTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // BINCACHEINPUTPORT_H_H_HEAD__FILE__
