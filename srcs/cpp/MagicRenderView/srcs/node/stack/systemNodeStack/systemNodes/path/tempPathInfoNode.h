#ifndef TEMPPATHINFONODE_H_H_HEAD__FILE__
#define TEMPPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>


class StringOutputPort;
/// @brief 返回一个可用于存储临时文件的目录。
/// 所返回的值可能是特定于某个应用程序的，也可以供该用户在其他应用程序中共享，甚至系统范围内。
/// 返回的路径永远不会为空。
class TempPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	TempPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/存储临时文件目录" ) );
};
#endif // TEMPPATHINFONODE_H_H_HEAD__FILE__
