#ifndef CHARARRAYCONVERTOSTRINGNODE_H_H_HEAD__FILE__
#define CHARARRAYCONVERTOSTRINGNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
class CharVectorInputPort;
class CharArrayConverToStringNode : public ProcessNode {
	Q_OBJECT;
protected:
	CharVectorInputPort *charVectorInputPortPtr;
	StringOutputPort *stringOutputPortPtr;
	QString *outVarPtr;
public:
	CharArrayConverToStringNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // CHARARRAYCONVERTOSTRINGNODE_H_H_HEAD__FILE__
