#ifndef GENERATEUINTINPUTPORT_H_H_HEAD__FILE__
#define GENERATEUINTINPUTPORT_H_H_HEAD__FILE__


#include "../generateTypeInputPort.h"

class GenerateUIntInputPort : public GenerateTypeInputPort {
	Q_OBJECT;
public:
	GenerateUIntInputPort( const QString &name )
		: GenerateTypeInputPort( name ) { }
};
#endif // GENERATEUINTINPUTPORT_H_H_HEAD__FILE__
