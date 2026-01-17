#ifndef CONFIGPATHINFONODE_H_H_HEAD__FILE__
#define CONFIGPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回一个目录位置，用于存放用户特定的配置文件。
/// 该位置可以是通用值，也可以是应用程序特定的，返回的路径永远不会为空。
class ConfigPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	ConfigPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/用户特定的配置文件目录" ) );
};
#endif // CONFIGPATHINFONODE_H_H_HEAD__FILE__
