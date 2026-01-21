#ifndef PICTURESPATHINFONODE_H_H_HEAD__FILE__
#define PICTURESPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回包含用户图片或照片的目录。
/// 这是一个通用值。
/// 如果不存在专门用于存储图片文件的目录，则会返回一个合理的备用选项，用于存储用户文档。
class PicturesPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	PicturesPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // PICTURESPATHINFONODE_H_H_HEAD__FILE__
