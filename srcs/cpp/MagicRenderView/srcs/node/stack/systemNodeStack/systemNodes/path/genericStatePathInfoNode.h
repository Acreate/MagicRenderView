#ifndef GENERICSTATEPATHINFONODE_H_H_HEAD__FILE__
#define GENERICSTATEPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>


class StringOutputPort;
/// @brief 返回一个目录位置，用于存放跨应用程序共享的状态数据文件。
/// 此值可能是通用的，也可能是特定于应用程序的，但返回的路径永远不会为空。
class GenericStatePathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	GenericStatePathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/跨应用共享状态数据文件目录" ) );
};
#endif // GENERICSTATEPATHINFONODE_H_H_HEAD__FILE__
