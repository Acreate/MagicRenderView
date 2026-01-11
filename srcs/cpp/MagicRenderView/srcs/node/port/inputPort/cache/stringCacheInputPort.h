#ifndef STRINGCACHEINPUTPORT_H_H_HEAD__FILE__
#define STRINGCACHEINPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeInputPort.h"

class StringCacheInputPort : public CacheTypeInputPort {
	Q_OBJECT;
public:
	StringCacheInputPort( const QString &name )
		: CacheTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // STRINGCACHEINPUTPORT_H_H_HEAD__FILE__
