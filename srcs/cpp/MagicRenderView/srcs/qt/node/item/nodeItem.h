#ifndef NODEITEM_H_H_HEAD__FILE__
#define NODEITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QWidget>
#include <qimage.h>

#include <alias/type_alias.h>

#include <qt/tools/tools.h>

#include "../prot/NodePort.h"

#define Def_NodeItem_StaticMetaInfo( ) \
	Def_Last_StaticMetaInfo( );\
	friend class NodeItemGenerate

#define Def_NodeItem_Last_StaticMetaInfo( ) \
	Def_Last_Firend_StaticMetaInfo( NodeItem );\
	friend class NodeItemGenerate

class Application;
class NodeOutputPort;
class NodeInputPort;
class NodeItem : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_NodeItem_StaticMetaInfo( );
public:
	using NodeItem_ParentPtr_Type = QWidget;
	using NodeItemString_Type = QString;
private:
	/// @brief 节点标题名称
	NodeItemString_Type nodeTitleName;
	/// @brief 绑定渲染
	QImage *nodeItemRender;
	/// @brief 相对节点的位置
	QPoint nodePos;
	/// @brief 节点宽度
	int nodeItemWidth;
	/// @brief 节点高度
	int nodeItemHeith;
	/// @brief 输出接口序列
	std_vector< NodeInputPort * > nodeInputProtVector;
	/// @brief 输出接口序列
	std_vector< NodeOutputPort * > nodeOutputProtVector;
	/// @brief 输入组件缓存
	QImage *inputBuff;
	/// @brief 输出组件缓存
	QImage *outputBuff;
	/// @brief 标题缓存
	QImage *titleBuff;

	/// @brief 输入面板高度
	int inputBuffHeight;
	/// @brief 输入面板宽度
	int inputBuffWidth;
	/// @brief 输出面板高度
	int outputBuffHeight;
	/// @brief 输出面板宽度
	int outputBuffWidth;
	/// @brief 标题高度
	int titleHeight;
	/// @brief 标题宽度
	int titleWidth;
	/// @brief 上下端口之间的空间大小
	int portSpace;
	/// @brief 标题到端口的空间大小
	int titleToPortSpace;
	/// @brief 输入输入端口之间的空间大小
	int midPortSpace;
	/// @brief 边缘底部空间大小
	int borderBoomSpace;
	/// @brief 边缘空间左侧空间大小
	int borderLeftSpace;
	/// @brief 边缘右侧空间大小
	int borderRightSpace;
	/// @brief 边缘顶端空间大小
	int borderTopSpace;
protected:
	/// @brief 应用类指针
	Application *applicationInstancePtr;
protected:
	NodeItem( NodeItem_ParentPtr_Type *parent );
public:
	~NodeItem( ) override;
	/// @brief 初始化接口选项
	/// @return 成功返回 true
	virtual bool intPortItems( );
	virtual const NodeItemString_Type & getNodeTitleName( ) const { return nodeTitleName; }
	virtual void setNodeTitleName( const NodeItemString_Type &node_title_name );

	virtual void move( const QPoint &point ) {
		nodePos = point;
	}
	virtual const QPoint & getPos( ) const { return nodePos; }
	virtual QSize getSize( ) const { return { nodeItemWidth, nodeItemHeith }; }
	virtual QRect geometry( ) const { return QRect( nodePos, QSize { nodeItemWidth, nodeItemHeith } ); }
	virtual QImage * getNodeItemRender( ) const { return nodeItemRender; }
	/// @brief 从父节点坐标转换到输入输出端口对象偏移坐标
	/// @param src_pos 父窗口坐标
	/// @return 输入输出端口对象的局部偏移坐标
	virtual QPoint formParentWidgetPosToPortPos( const QPoint &src_pos ) {
		return src_pos - nodePos;
	}
	/// @brief 测试指定坐标是否存在当前节点内
	/// @param point 测试坐标
	/// @return 在当前节点范围内，返回 true
	virtual bool contains( const QPoint &point ) {
		auto leftTop = point - nodePos;
		int x = leftTop.x( );
		if( x < 0 )
			return false;
		int y = leftTop.x( );
		if( y < 0 )
			return false;
		if( x > nodeItemWidth )
			return false;
		if( y > nodeItemHeith )
			return false;
		return true;
	}
protected:
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
	virtual bool updateProtLayout( );
	/// @brief 更新输入端布局
	/// @return 成功返回 true
	virtual bool updateInputLayout( );
	/// @brief 更新输出端布局
	/// @return 成功返回 true
	virtual bool updateOutputLayout( );
	/// @brief 更新标题布局
	/// @return 成功返回 true
	virtual bool updateTitleLayout( );
public:
	/// @brief 从指定位置获取输出端口对象指针
	/// @param pos 基于 NodeItem::getPos( ) 所偏移的位置
	/// @return 成功返回输出端口，失败返回 nullptr
	virtual NodeOutputPort * formPosNodeOutputPort( const QPoint &pos );
	/// @brief 从布局存储序列获取输出端口对象指针
	/// @param index 布局序列下标
	/// @return 成功返回输出端口，失败返回 nullptr
	virtual NodeOutputPort * formIndexNodeOutputPort( const size_t &index );
	/// @brief 从指定位置获取输入端口对象指针
	/// @param pos 基于 NodeItem::getPos( ) 所偏移的位置
	/// @return 成功返回输入端口，失败返回 nullptr
	virtual NodeInputPort * formPosNodeInputPort( const QPoint &pos );
	/// @brief 从布局存储序列获取输入端口对象指针
	/// @param index 布局序列下标
	/// @return 成功返回输入端口，失败返回 nullptr
	virtual NodeInputPort * formIndexNodeInputPort( const size_t &index );

};

#endif // NODEITEM_H_H_HEAD__FILE__
