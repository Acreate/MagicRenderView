#ifndef TODATETIMENODE_H_H_HEAD__FILE__
#define TODATETIMENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class DateTimeOutputPort;
class BinOutputPort;
class AnyVarInputPort;
class UIntOutputPort;
class ToDateTimeNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *anyVarInputPortPtr;
	DateTimeOutputPort *dateTimeOutputPortPtr;
	QDateTime *outVarPtr;
public:
	ToDateTimeNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/单元/日期时间" ) );
};
#endif // TODATETIMENODE_H_H_HEAD__FILE__
