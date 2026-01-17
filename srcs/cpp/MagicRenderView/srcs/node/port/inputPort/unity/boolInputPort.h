#ifndef BOOLINPUTPORT_H_H_HEAD__FILE__
#define BOOLINPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeInputPort.h"

class BoolInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	BoolInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // BOOLINPUTPORT_H_H_HEAD__FILE__
