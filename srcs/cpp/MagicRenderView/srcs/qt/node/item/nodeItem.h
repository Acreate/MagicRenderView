#ifndef NODEITEM_H_H_HEAD__FILE__
#define NODEITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <qimage.h>

#include <alias/type_alias.h>

#define Def_NodeItem_StaticMetaInfo( ) \
	Def_Last_StaticMetaInfo( );\
	friend class NodeItemGenerate

#define Def_NodeItem_Last_StaticMetaInfo( ) \
	Def_Last_Firend_StaticMetaInfo( NodeItem );\
	friend class NodeItemGenerate

class NodeItem : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_NodeItem_StaticMetaInfo( );
protected:
	/// @brief 绑定渲染
	QImage nodePortRender;
	/// @brief 相对节点的位置
	QPoint pos;
protected:
	NodeItem( QObject *parent ) : QObject( parent ) {

	}
public:
	virtual const QPoint & getPos( ) const { return pos; }
	virtual const QSize & getSize( ) const { return nodePortRender.size( ); }
	virtual QRect geometry( ) const { return QRect( getPos( ), getSize( ) ); }
};

#endif // NODEITEM_H_H_HEAD__FILE__
