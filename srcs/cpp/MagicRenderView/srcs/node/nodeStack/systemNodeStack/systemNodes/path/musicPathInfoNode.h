#ifndef MUSICPATHINFONODE_H_H_HEAD__FILE__
#define MUSICPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回包含用户音乐或其他音频文件的目录。
/// 这是一个通用值。
/// 如果不存在专门用于存储音乐文件的目录，则会返回一个合理的用于存储用户文档的替代目录。
class MusicPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	MusicPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // MUSICPATHINFONODE_H_H_HEAD__FILE__
