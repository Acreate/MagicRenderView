#ifndef GENERATEBINOUTPUTPORT_H_H_HEAD__FILE__
#define GENERATEBINOUTPUTPORT_H_H_HEAD__FILE__


#include "../generateTypeOutputPort.h"

class GenerateBinOutputPort : public GenerateTypeOutputPort{
	Q_OBJECT;
public:
	GenerateBinOutputPort( const QString &name )
		: GenerateTypeOutputPort( name ) { }
	bool init(Node *parent) override;
};

#endif // GENERATEBINOUTPUTPORT_H_H_HEAD__FILE__
