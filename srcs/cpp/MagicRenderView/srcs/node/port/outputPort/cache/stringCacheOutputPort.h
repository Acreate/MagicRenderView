#ifndef STRINGCACHEOUTPUTPORT_H_H_HEAD__FILE__
#define STRINGCACHEOUTPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeOutputPort.h"

class StringCacheOutputPort : public CacheTypeOutputPort {
	Q_OBJECT;
public:
	StringCacheOutputPort( const QString &name )
		: CacheTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // STRINGCACHEOUTPUTPORT_H_H_HEAD__FILE__
