#ifndef GENERICCACHEPATHINFONODE_H_H_HEAD__FILE__
#define GENERICCACHEPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回一个目录位置，用于存放用户特定的非关键（缓存）数据，这些数据在不同应用程序之间可共享使用。
/// 这是一个通用值。
/// 请注意，如果系统没有共享缓存的概念，返回的路径可能会为空。
class GenericCachePathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	GenericCachePathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // GENERICCACHEPATHINFONODE_H_H_HEAD__FILE__
