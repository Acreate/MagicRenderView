#ifndef APPLOCALDATAPATHINFONODE_H_H_HEAD__FILE__
#define APPLOCALDATAPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回 Windows 操作系统上的本地设置路径。
/// 在其他所有平台上，其返回值与 AppDataLocation 相同
class AppLocalDataPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	AppLocalDataPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/本地设置路径" ) );
};
#endif // APPLOCALDATAPATHINFONODE_H_H_HEAD__FILE__
