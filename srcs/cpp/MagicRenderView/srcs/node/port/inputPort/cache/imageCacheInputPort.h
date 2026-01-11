#ifndef IMAGECACHEINPUTPORT_H_H_HEAD__FILE__
#define IMAGECACHEINPUTPORT_H_H_HEAD__FILE__

#include "../cacheTypeInputPort.h"

class ImageCacheInputPort : public CacheTypeInputPort {
	Q_OBJECT;
public:
	ImageCacheInputPort( const QString &name )
		: CacheTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // IMAGECACHEINPUTPORT_H_H_HEAD__FILE__
