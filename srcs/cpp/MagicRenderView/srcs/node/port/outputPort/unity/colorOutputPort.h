#ifndef COLOROUTPUTPORT_H_H_HEAD__FILE__
#define COLOROUTPUTPORT_H_H_HEAD__FILE__



#include "../unityTypeOutputPort.h"

class ColorOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	ColorOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // COLOROUTPUTPORT_H_H_HEAD__FILE__
