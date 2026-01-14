#ifndef SPLITDATATIMENODE_H_H_HEAD__FILE__
#define SPLITDATATIMENODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class TimeOutputPort;
class DateOutputPort;
class DateTimeInputPort;
class DateTimeOutputPort;
class StringOutputPort;
class AnyVarInputPort;
class SplitDataTimeNode : public ProcessNode {
	Q_OBJECT;
protected:
	DateTimeInputPort *dateTimeInputPortPtr;
	DateOutputPort *dateOutputPortPtr;
	TimeOutputPort *timeOutputPortPtr;
	QDate *outDatePtr;
	QTime *outTimePtr;
public:
	SplitDataTimeNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/日期与时间" ) );
};
#endif // SPLITDATATIMENODE_H_H_HEAD__FILE__
