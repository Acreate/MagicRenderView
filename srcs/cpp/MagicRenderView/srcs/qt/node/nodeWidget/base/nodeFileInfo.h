#ifndef NODEFILEINFO_H_H_HEAD__FILE__
#define NODEFILEINFO_H_H_HEAD__FILE__
#pragma once
#include "qt/node/nodeWidget/INodeWidget.h"

class NodePanel;
class NodeFileInfo : public INodeWidget {
	Q_OBJECT;
protected: // ui
	/// @brief 选项面板
	NodePanel *subPlan;
	
	/// @brief 输入路径
	NodeInputLineText *inputPath;
	/// @brief 输出路径
	NodeInputLineText *outAbsPath;
	/// @brief 输出大小
	NodeInputLineText *outSize;
	/// @brief 输出使用大小
	NodeInputLineText *outUserSize;
	/// @brief 输出创建文件时间
	NodeInputLineText *outCreateFileTimeData;
	/// @brief 输出最后更新事件
	NodeInputLineText *outLastChangeFileTimeData;
	/// @brief 输出文件拥有者
	NodeInputLineText *outFileOwner;
	/// @brief 输出文件内容
	NodeInputLineText *outFileContent;
public:
	NodeFileInfo( const std_function< std_shared_ptr< INodeStack >( ) > &get_stack_function, const std_vector< QString > &node_widget_name_s, QWidget *parent, Qt::WindowFlags f );
	void connectNodeGraphWidget( NodeGraph *node_graph ) override;
	std_shared_ptr< ITypeObject > getResult( ) const override;
	std_vector_unity_shared< ITypeObject > getParams( ) const override;
	std_vector_unity_shared< ITypeObject > setParams( const std_vector_unity_shared< ITypeObject > &params ) const override;
	bool setParam( const std_shared_ptr< ITypeObject > &param, size_t param_index ) const override;
	bool getComponentLinkPos( const INodeComponent *component, QPoint &resulut_pos ) const override;
private:
	void updateSize( );
protected:
	void showEvent( QShowEvent *event ) override;
};

#endif // NODEFILEINFO_H_H_HEAD__FILE__
