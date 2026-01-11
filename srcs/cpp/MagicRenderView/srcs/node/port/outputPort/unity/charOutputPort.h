#ifndef CHAROUTPUTPORT_H_H_HEAD__FILE__
#define CHAROUTPUTPORT_H_H_HEAD__FILE__


#include "../unityTypeOutputPort.h"

class CharOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	CharOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // CHAROUTPUTPORT_H_H_HEAD__FILE__
