#ifndef CACHEPATHINFONODE_H_H_HEAD__FILE__
#define CACHEPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回一个目录位置，用于存放用户特定的非关键（缓存）数据。
/// 这是一个应用程序特定的目录。返回的路径永远不会为空。
class CachePathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	CachePathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/用户特定的非关键缓存数据目录" ) );
};
#endif // CACHEPATHINFONODE_H_H_HEAD__FILE__
