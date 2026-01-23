#ifndef COLORINPUTPORT_H_H_HEAD__FILE__
#define COLORINPUTPORT_H_H_HEAD__FILE__


#include "../unityTypeInputPort.h"

class ColorInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	ColorInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // COLORINPUTPORT_H_H_HEAD__FILE__
