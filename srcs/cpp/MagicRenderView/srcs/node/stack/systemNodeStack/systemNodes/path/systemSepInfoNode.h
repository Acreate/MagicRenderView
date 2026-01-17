#ifndef SYSTEMSEPINFONODE_H_H_HEAD__FILE__
#define SYSTEMSEPINFONODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>


class StringOutputPort;
/// @brief 返回系统路径分隔符
class SystemSepInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	SystemSepInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/系统路径分隔符" ) );
};
#endif // SYSTEMSEPINFONODE_H_H_HEAD__FILE__
