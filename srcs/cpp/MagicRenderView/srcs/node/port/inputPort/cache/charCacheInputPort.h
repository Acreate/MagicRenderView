#ifndef CHARCACHEINPUTPORT_H_H_HEAD__FILE__
#define CHARCACHEINPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeInputPort.h"

class CharCacheInputPort : public CacheTypeInputPort {
	Q_OBJECT;
public:
	CharCacheInputPort( const QString &name )
		: CacheTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // CHARCACHEINPUTPORT_H_H_HEAD__FILE__
