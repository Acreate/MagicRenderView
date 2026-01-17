#ifndef GENERICCONFIGPATHINFONODE_H_H_HEAD__FILE__
#define GENERICCONFIGPATHINFONODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>


class StringOutputPort;
/// @brief 返回一个自录位置，用于存放多个应用程序之间共享的用户特定配置文件。
/// 这是一个通用值，返回的路径永远不会为空。
class GenericConfigPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	GenericConfigPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/应用程序共享配置目录" ) );
};
#endif // GENERICCONFIGPATHINFONODE_H_H_HEAD__FILE__
