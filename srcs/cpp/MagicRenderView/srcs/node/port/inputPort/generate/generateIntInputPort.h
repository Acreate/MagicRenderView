#ifndef GENERATEINTINPUTPORT_H_H_HEAD__FILE__
#define GENERATEINTINPUTPORT_H_H_HEAD__FILE__

#include "../generateTypeInputPort.h"

class GenerateIntInputPort : public GenerateTypeInputPort {
	Q_OBJECT;
public:
	GenerateIntInputPort( const QString &name )
		: GenerateTypeInputPort( name ) { }
};
#endif // GENERATEINTINPUTPORT_H_H_HEAD__FILE__
