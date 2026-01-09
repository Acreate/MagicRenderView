#ifndef GENERATESTRINGINPUTPORT_H_H_HEAD__FILE__
#define GENERATESTRINGINPUTPORT_H_H_HEAD__FILE__

#include "../generateTypeInputPort.h"

class GenerateStringInputPort : public GenerateTypeInputPort {
	Q_OBJECT;
public:
	GenerateStringInputPort( const QString &name )
		: GenerateTypeInputPort( name ) { }
};
#endif // GENERATESTRINGINPUTPORT_H_H_HEAD__FILE__
