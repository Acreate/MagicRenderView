#ifndef APPDATAPATHINFONODE_H_H_HEAD__FILE__
#define APPDATAPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>


class StringOutputPort;
/// @brief 返回一个可用于存储持久性应用程序数据的目录位置。
/// 这是一个应用程序特定的目录。
/// 若要获取用于存储需与其他应用程序共享的数据的路径，请使用 QStandardPaths::GenericDataLocation 。
/// 返回的路径永远不会为空。
/// 在 Windows 操作系统中，此方法返回的是 roaming 路径
class AppDataPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	AppDataPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/持久性应用程序数据的目录" ) );
};
#endif // APPDATAPATHINFONODE_H_H_HEAD__FILE__
