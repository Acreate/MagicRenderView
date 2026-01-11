#ifndef IMAGEVECTORINPUTPORT_H_H_HEAD__FILE__
#define IMAGEVECTORINPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeInputPort.h"

class ImageVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	ImageVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // IMAGEVECTORINPUTPORT_H_H_HEAD__FILE__
