#ifndef NODEFILEINFO_H_H_HEAD__FILE__
#define NODEFILEINFO_H_H_HEAD__FILE__
#pragma once
#include "qt/node/nodeWidget/INodeWidget.h"

class NodePanel;
class NodeFileInfo : public INodeWidget {
	Q_OBJECT;
protected: // ui
	/// @brief 输入路径
	NodeInputLineText *path;
	/// @brief 选项面板
	NodePanel *subPlan;
public:
	NodeFileInfo( const std_function< std_shared_ptr< INodeStack >( ) > &get_stack_function, const QString &node_widget_name, QWidget *parent, Qt::WindowFlags f );
	void connectNodeGraphWidget( NodeGraph *node_graph ) override;
	std_shared_ptr< ITypeObject > getResult( ) const override;
	std_vector_unity_shared< ITypeObject > getParams( ) const override;
	std_vector_unity_shared< ITypeObject > setParams( const std_vector_unity_shared< ITypeObject > &params ) const override;
	bool setParam( const std_shared_ptr< ITypeObject > &param, size_t param_index ) const override;
	void setNodeWidgetName( const QString &node_widget_name ) override;
	bool getComponentLinkPos( const INodeComponent *component, QPoint &resulut_pos ) const override;
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;
private:
	void updateSize( );
protected:
	void showEvent( QShowEvent *event ) override;
};

#endif // NODEFILEINFO_H_H_HEAD__FILE__
