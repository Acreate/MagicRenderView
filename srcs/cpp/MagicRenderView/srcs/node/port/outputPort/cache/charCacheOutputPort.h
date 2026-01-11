#ifndef CHARCACHEOUTPUTPORT_H_H_HEAD__FILE__
#define CHARCACHEOUTPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeOutputPort.h"

class CharCacheOutputPort : public CacheTypeOutputPort {
	Q_OBJECT;
public:
	CharCacheOutputPort( const QString &name )
		: CacheTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // CHARCACHEOUTPUTPORT_H_H_HEAD__FILE__
