#ifndef IMAGEVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define IMAGEVECTOROUTPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeOutputPort.h"

class ImageVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	ImageVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // IMAGEVECTOROUTPUTPORT_H_H_HEAD__FILE__
