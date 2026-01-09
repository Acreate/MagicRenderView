#ifndef GENERATECOLOROUTPUTPORT_H_H_HEAD__FILE__
#define GENERATECOLOROUTPUTPORT_H_H_HEAD__FILE__

#include "../generateTypeOutputPort.h"

class GenerateColorOutputPort : public GenerateTypeOutputPort{
	Q_OBJECT;
public:
	GenerateColorOutputPort( const QString &name )
		: GenerateTypeOutputPort( name ) { }
	bool init(Node *parent) override;
};
#endif // GENERATECOLOROUTPUTPORT_H_H_HEAD__FILE__
