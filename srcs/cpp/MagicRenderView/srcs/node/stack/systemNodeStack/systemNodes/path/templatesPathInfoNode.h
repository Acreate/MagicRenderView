#ifndef TEMPLATESPATHINFONODE_H_H_HEAD__FILE__
#define TEMPLATESPATHINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
/// @brief 返回一个目录位置，用户特定的模板文件可以存放在该位置。
/// 这是一个通用值。
/// 请注意，如果系统没有模板位置的概念，返回的路径可能会为空。
class TemplatesPathInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *pathOutputPortPtr;
	QString *pathPtr;
public:
	TemplatesPathInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // TEMPLATESPATHINFONODE_H_H_HEAD__FILE__
