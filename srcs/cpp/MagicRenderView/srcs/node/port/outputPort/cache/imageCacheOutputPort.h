#ifndef IMAGECACHEOUTPUTPORT_H_H_HEAD__FILE__
#define IMAGECACHEOUTPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeOutputPort.h"

class ImageCacheOutputPort : public CacheTypeOutputPort {
	Q_OBJECT;
public:
	ImageCacheOutputPort( const QString &name )
		: CacheTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // IMAGECACHEOUTPUTPORT_H_H_HEAD__FILE__
