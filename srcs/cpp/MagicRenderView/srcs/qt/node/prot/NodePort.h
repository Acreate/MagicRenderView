#ifndef NODEPORT_H_H_HEAD__FILE__
#define NODEPORT_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <qimage.h>

#include <alias/type_alias.h>

#include <qt/varType/varType.h>

class NodeItem;
class NodePort : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( );
protected:
	/// @brief 绑定变量
	VarType *var;
	/// @brief 绑定渲染
	QImage nodePortRender;
	/// @brief 相对节点的位置
	QPoint nodePos;
	/// @brief 节点大小
	QSize nodeSize;
	/// @brief 标题
	QString title;
	/// @brief 父节点
	NodeItem *parent;
public:
	NodePort( NodeItem *parent );
	virtual const QImage & getNodePortRender( ) const { return nodePortRender; }
	virtual void move( const QPoint &new_pos ) {
		nodePos = new_pos;
	}
	virtual void move( const int &x, const int &y ) {
		nodePos = QPoint( x, y );
	}
	virtual void moveX( const int &x ) {
		nodePos.setX( x );
	}
	virtual void moveY( const int &y ) {
		nodePos.setY( y );
	}
	virtual const QPoint & getPos( ) const { return nodePos; }
	virtual const QSize & getSize( ) const { return nodeSize; }
	virtual QRect geometry( ) const { return QRect( getPos( ), getSize( ) ); }
	virtual const VarType * getVar( ) const {
		return var;
	}
	virtual void bindVar( VarType *bind_var ) {
		auto old = var;
		var = bind_var;
		if( old )
			old->disconnect( this );
		if( bind_var )
			connect( var, &VarType::deleteObjBefore, this, &NodePort::releaseVarType );
		emit replaceVar( old, var );
	}
	virtual void updateProtLayout( ) = 0;
	virtual QPoint converToNodeItemWidgetPos( ) const;
	virtual QRect converToNodeItemWidgetGeometry( ) const;
protected Q_SLOTS:
	virtual void releaseVarType( VarType *release_var_type ) {
		if( release_var_type == var )
			bindVar( nullptr );
	}
Q_SIGNALS:
	void replaceVar( VarType *old_var, VarType *new_var );
};
#endif // NODEPORT_H_H_HEAD__FILE__
