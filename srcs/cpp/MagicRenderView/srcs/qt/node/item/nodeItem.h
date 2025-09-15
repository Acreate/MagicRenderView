#ifndef NODEITEM_H_H_HEAD__FILE__
#define NODEITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QWidget>
#include <qimage.h>

#include <alias/type_alias.h>

#include <qt/tools/tools.h>

#include "../prot/inputProt/nodeInputPort.h"
#include "../prot/outputProt/nodeOutputPort.h"

#define Def_NodeItem_StaticMetaInfo( ) \
	Def_Last_StaticMetaInfo( );\
	friend class NodeItemGenerate

#define Def_NodeItem_Last_StaticMetaInfo( ) \
	Def_Last_Firend_StaticMetaInfo( NodeItem );\
	friend class NodeItemGenerate

class NodeItem : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_NodeItem_StaticMetaInfo( );
public:
	using NodeItem_ParentPtr_Type = QWidget;
	using NodeItemString_Type = QString;
protected:
	/// @brief 节点标题名称
	NodeItemString_Type nodeTitleName;
	/// @brief 绑定渲染
	QImage nodePortRender;
	/// @brief 相对节点的位置
	QPoint nodePos;
	/// @brief 节点大小
	QSize nodeSize;
	/// @brief 是否渲染
	bool needRender;
	/// @brief 渲染目标
	QWidget *nodeParent;
	/// @brief 输出接口序列
	std_vector< NodeInputPort * > nodeInputProtVector;
	/// @brief 输出接口序列
	std_vector< NodeOutputPort * > nodeOutputProtVector;
protected:
	NodeItem( NodeItem_ParentPtr_Type *parent ) : QObject( parent ), nodeParent( parent ) {
		if( parent == nullptr ) {
			needRender = false;
			tools::debug::printError( QObject::tr( "非法对象。该对象需要一个正确的父类 QWidget 对象" ) );
			return;
		}
		needRender = true;
		nodeTitleName = getMetaObjectName( );
	}
public:
	virtual const NodeItemString_Type & getNodeTitleName( ) const { return nodeTitleName; }
	virtual void setNodeTitleName( const NodeItemString_Type &node_title_name ) { nodeTitleName = node_title_name; }
	virtual void setWidgetParent( NodeItem_ParentPtr_Type *parent ) {
		if( parent == nullptr ) {
			tools::debug::printError( QObject::tr( "不可赋值父 QWidget 对象为 nullptr，该对象需要一个正确的父类 QWidget 对象" ) );
			return;
		}
		if( nodeParent != nullptr ) {
			auto newPos = nodeParent->mapToGlobal( nodePos );
			nodeParent = parent;
			nodePos = nodeParent->mapFromGlobal( newPos );
			return;
		}
		nodeParent = parent;
		nodePos = QPoint( 0, 0 );
	}
	virtual NodeItem_ParentPtr_Type * getWidgetParent( ) const {
		return nodeParent;
	}
	virtual void move( const QPoint &point ) {
		nodePos = point;
		if( nodeParent == nullptr ) {
			tools::debug::printError( QObject::tr( "不属性父 QWidget 对象为 nullptr，该对象需要一个正确的父类 QWidget 对象" ) );
			return;
		}
		renderToWidget( );
	}
	virtual const QPoint & getPos( ) const { return nodePos; }
	virtual const QSize & getSize( ) const { return nodeSize; }
	virtual QRect geometry( ) const { return QRect( nodePos, nodeSize ); }
	virtual void show( ) {
		needRender = true;
		if( nodeParent == nullptr ) {
			tools::debug::printError( QObject::tr( "不属性父 QWidget 对象为 nullptr，该对象需要一个正确的父类 QWidget 对象" ) );
			return;
		}
		renderToWidget( );
	}
	virtual void hide( ) {
		needRender = false;
	}
	virtual bool isNeedRender( ) const {
		if( nodeParent )
			return needRender;
		return false;
	}
	/// @brief 渲染到目标
	/// @return 成功返回 true
	virtual bool renderToWidget( ) {
		return isNeedRender( );
	}
	/// @brief 增加一个输入接口
	/// @param input_prot 输入接口对象指针
	/// @return 成功返回 true
	virtual bool appendInputProt( NodeInputPort *input_prot );
	/// @brief 删除输入接口
	/// @param input_prot 输入接口对象指针 
	/// @return 成功返回 true
	virtual bool removeInputProt( NodeInputPort *input_prot );
	/// @brief 增加一个输出接口
	/// @param output_prot 输出接口对象指针
	/// @return 成功返回 true
	virtual bool appendOutputProt( NodeOutputPort *output_prot );
	/// @brief 删除输出接口
	/// @param output_port 
	/// @return 成功返回 true
	virtual bool removeOutputProt( NodeOutputPort *output_port );
	/// @brief 更新接口布局
	virtual void updateProtLayout( );
};

#endif // NODEITEM_H_H_HEAD__FILE__
