#ifndef FUNCTIONOUTPUTPORT_H_H_HEAD__FILE__
#define FUNCTIONOUTPUTPORT_H_H_HEAD__FILE__
#include "../functionTypeOutputPort.h"

class FunctionOutputPort : public FunctionTypeOutputPort {
	Q_OBJECT;
public:
	FunctionOutputPort( const QString &name )
		: FunctionTypeOutputPort( name ) { }
};

#endif // FUNCTIONOUTPUTPORT_H_H_HEAD__FILE__
