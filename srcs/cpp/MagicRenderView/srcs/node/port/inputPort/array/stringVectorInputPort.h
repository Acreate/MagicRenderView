#ifndef STRINGVECTORINPUTPORT_H_H_HEAD__FILE__
#define STRINGVECTORINPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeInputPort.h"

class StringVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	StringVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }

	bool init( Node *parent ) override;
};

#endif // STRINGVECTORINPUTPORT_H_H_HEAD__FILE__
