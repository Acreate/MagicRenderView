#ifndef NODEPORT_H_H_HEAD__FILE__
#define NODEPORT_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <qimage.h>

#include <alias/type_alias.h>

class VarGenerate;
class NodeOutputPort;
class I_Var;
class I_Type;
class VarType;
class Application;
class NodeItem;
class NodePort : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( );
private:
	friend class MainWidget;
	friend class AppNodeItemType;
protected:
	/// @brief 绑定渲染
	QImage *nodePortRender;
	/// @brief 图标
	QImage *ico;
	/// @brief 端口宽度
	int portItemWidth;
	/// @brief 端口高度
	int portItemHeith;
	/// @brief 图标宽度
	int icoItemWidth;
	/// @brief 图标高度
	int icoItemHeith;
	/// @brief 标题
	QString title;
	/// @brief 父节点
	NodeItem *parentItem;
	/// @brief 引用对象指针
	Application *applicationInstancePtr;
	/// @brief 变量生成实例
	VarGenerate *varGenerate;
	/// @brief 变量类型
	I_Type *typePtr;
	/// @brief 变量指针
	I_Var *varPtr;
	/// @brief 链接的序<节点序号，输出端口名称>
	std_vector_pairt< size_t, QString > linkOutputVector;
public:
	NodePort( NodeItem *parent_item );
	~NodePort( ) override;
	virtual bool getPos( QPoint &result_pos ) const = 0;
	virtual int getIcoWidth( ) const { return icoItemWidth; }
	virtual int getIcoHeith( ) const { return icoItemHeith; }
	virtual const QString & getTitle( ) const { return title; }
	virtual void setTitle( const QString &title );
	virtual QImage * getIco( ) const {
		return ico;
	}
	virtual void setIco( const QImage &new_ico ) {
		*ico = new_ico;
		icoItemHeith = ico->height( );
		icoItemWidth = ico->width( );
	}
	virtual void setIco( const QString &new_ico_path );
	virtual bool renderLayout( bool ico_is_end );
	virtual QImage * getNodePortRender( ) const { return nodePortRender; }
	virtual int height( ) const {
		return portItemHeith;
	}
	virtual int width( ) const {
		return portItemWidth;
	}
	virtual QSize getSize( ) const { return QSize( portItemWidth, portItemHeith ); }
	virtual bool updateProtLayout( ) = 0;
	virtual const I_Var * getVar( ) const {
		return varPtr;
	}
	virtual const I_Type * getVarType( ) const {
		return typePtr;
	}
	virtual bool linkOutputPort( NodePort *output_port ) { return false; }
	virtual bool disLinkOutputPor( NodePort *remove_output_port ) { return false; }
	virtual NodeItem * getParentItem( ) const { return parentItem; }
	virtual std_vector< NodePort * > getLinkOutputVector( ) const;
	virtual bool isOutputPort( ) const {
		return false;
	}
Q_SIGNALS:
	void releaseThiNodeProt( NodePort *release_ptr );
	void outputPorDelete( NodeOutputPort *remove_output_port );
	void inputPorDelete( NodePort *remove_input_port );
	void linkOutputPorOver( NodePort *remove_input_port );
	void disLinkOutputPorOver( NodePort *remove_input_port );
};
#endif // NODEPORT_H_H_HEAD__FILE__
