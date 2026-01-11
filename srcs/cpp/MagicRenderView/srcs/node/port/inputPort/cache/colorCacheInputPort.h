#ifndef COLORCACHEINPUTPORT_H_H_HEAD__FILE__
#define COLORCACHEINPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeInputPort.h"

class ColorCacheInputPort : public CacheTypeInputPort {
	Q_OBJECT;
public:
	ColorCacheInputPort( const QString &name )
		: CacheTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // COLORCACHEINPUTPORT_H_H_HEAD__FILE__
