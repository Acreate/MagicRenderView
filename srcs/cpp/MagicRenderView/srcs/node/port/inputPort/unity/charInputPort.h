#ifndef CHARINPUTPORT_H_H_HEAD__FILE__
#define CHARINPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeInputPort.h"

class CharInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	CharInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // CHARINPUTPORT_H_H_HEAD__FILE__
