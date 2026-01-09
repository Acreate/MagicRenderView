#ifndef GENERATEFLOATINPUTPORT_H_H_HEAD__FILE__
#define GENERATEFLOATINPUTPORT_H_H_HEAD__FILE__

#include "../generateTypeInputPort.h"

class GenerateFloatInputPort : public GenerateTypeInputPort {
	Q_OBJECT;
public:
	GenerateFloatInputPort( const QString &name )
		: GenerateTypeInputPort( name ) { }
};

#endif // GENERATEFLOATINPUTPORT_H_H_HEAD__FILE__
