#ifndef COLORCACHEOUTPUTPORT_H_H_HEAD__FILE__
#define COLORCACHEOUTPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeOutputPort.h"

class ColorCacheOutputPort : public CacheTypeOutputPort {
	Q_OBJECT;
public:
	ColorCacheOutputPort( const QString &name )
		: CacheTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // COLORCACHEOUTPUTPORT_H_H_HEAD__FILE__
