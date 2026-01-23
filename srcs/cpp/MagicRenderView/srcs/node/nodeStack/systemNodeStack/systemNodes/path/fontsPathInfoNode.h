#ifndef FONTSPATHINFONODE_H_H_HEAD__FILE__
#define FONTSPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回包含用户字体的目录。
/// 这是一个通用值。
/// 请注意，安装字体可能需要额外的、针对特定平台的操作。
class FontsPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	FontsPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // FONTSPATHINFONODE_H_H_HEAD__FILE__
