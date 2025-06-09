#ifndef NODEFILEINFO_H_H_HEAD__FILE__
#define NODEFILEINFO_H_H_HEAD__FILE__
#pragma once
#include "qt/node/nodeWidget/INodeWidget.h"

class NodeFileInfo : public INodeWidget {
	Q_OBJECT;
protected: // ui
	/// @brief 输入路径
	NodeInputLineText *path;
public:
	NodeFileInfo( QWidget *parent, Qt::WindowFlags f );
	NodeFileInfo( ) : NodeFileInfo( nullptr, Qt::WindowFlags( ) ) { }
	void connectNodeGraphWidget( NodeGraph *node_graph ) override;
	std_shared_ptr< ITypeObject > getResult( ) const override;
	std_vector_unity_shared< ITypeObject > getParams( ) const override;
	std_vector_unity_shared< ITypeObject > setParams( const std_vector_unity_shared< ITypeObject > &params ) const override;
	bool setParam( const std_shared_ptr< ITypeObject > &param, size_t param_index ) const override;
private:
	void updateSize( );
protected:
	void showEvent( QShowEvent *event ) override;
};

#endif // NODEFILEINFO_H_H_HEAD__FILE__
