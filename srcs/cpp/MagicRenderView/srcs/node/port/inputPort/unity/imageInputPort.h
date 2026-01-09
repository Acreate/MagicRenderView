#ifndef IMAGEINPUTPORT_H_H_HEAD__FILE__
#define IMAGEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../unityTypeInputPort.h"

class ImageInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	ImageInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // IMAGEINPUTPORT_H_H_HEAD__FILE__
