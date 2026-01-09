#ifndef IMAGEOUTPUTPORT_H_H_HEAD__FILE__
#define IMAGEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../unityTypeOutputPort.h"

class ImageOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	ImageOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // IMAGEOUTPUTPORT_H_H_HEAD__FILE__
