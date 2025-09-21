#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QPainterPath>
#include <QWidget>

#include <alias/type_alias.h>

#include "../node/item/nodeItem.h"

class QScrollArea;
class QVBoxLayout;
class Application;
class MainWidget : public QWidget {

	Q_OBJECT;
private:
	friend class NodeWidgetSerialization;
	friend class NodeItemSerialization;
protected:
	/// @brief 数据化的支持对象（节点与数据类型）
	std_vector< uint8_t > supportBin;
	/// @brief 数据化支持的节点内容
	std_vector< uint8_t > supportNodeBin;
	/// @brief 数据化支持的类型内容
	std_vector< uint8_t > supportVarTypeBin;
	/// @brief 支持节点
	std_vector_pairt< QMenu *, std_vector_pairt< QAction *, QString > > supportNode;
	/// @brief 支持节点的名称
	std_vector< QString > supportNodeName;
	/// @brief 支持类型
	std_vector< QString > supporVarType;
	/// @brief 当前窗口的滚动页面
	QScrollArea *scrollArea;
	/// @brief 应用实例
	Application *appInstance;
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 用于创建节点的菜单-鼠标右键对应空白即可弹出
	QMenu *rightMouseBtnCreateNodeItemMenu;
	/// @brief 按下时全局位置
	QPoint globalPressPos;
	/// @brief 按下时当前窗口位置
	QPoint fromGlobalPressPoint;
	/// @brief 多用途位置信息
	QPoint modPoint;
	/// @brief 按下时全局位置
	QPoint globalReleasePos;
	/// @brief 按下时当前窗口位置
	QPoint fromGlobalReleasePoint;
	/// @brief 鼠标移动时的坐标位置
	QPoint mouseMovePoint;
	/// @brief 节点链表
	std_list< NodeItem * > nodeItemList;
	/// @brief 鼠标左键选中的输入端口
	NodeInputPort *leftMouseBtnSelectInputPort;
	/// @brief 鼠标左键选中的输出端口
	NodeOutputPort *leftMouseBtnSelectOutputPort;
	/// @brief 鼠标左键选中的节点
	NodeItem *leftMouseBtnSelectItem;
	/// @brief 窗口当时激活的节点
	NodeItem *renderWidgetActiveItem;
	/// @brief 鼠标左键拖拽项
	NodeItem *leftMouseBtnDragItem;
	/// @brief 鼠标右键选中项
	NodeItem *rightMouseBtnSelectItem;
	/// @brief 鼠标右键选中节点
	NodeInputPort *rightMouseBtnSelectPort;
	/// @brief 用于操作删除输出接口的菜单-鼠标右键命中输入接口是弹出
	QMenu *rightMouseBtnRemoveOutPortMenu;
	/// @brief 对象是否在序列化
	bool isSerialization;
public:
	MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWidget( ) override;
	/// @brief 窗口滚动到指定节点位置-大小不足时进行窗口扩充
	/// @param targetItemNode 目标节点
	virtual void ensureVisibleToItemNode( const NodeItem *targetItemNode );
	/// @brief 更新支持内容
	virtual void updateSupport( );
	/// @brief 获取经过二进制化的支持数据
	/// @return 经过二进制化的支持是数据
	virtual const std_vector< uint8_t > & getSupportBin( ) const {
		return supportBin;
	}
	/// @brief 获取支持节点名称的二进制数据
	/// @return 节点支持的二进制数据
	virtual const std_vector< uint8_t > & getSupportNodeNmaeBin( ) const {
		return supportNodeBin;
	}
	/// @brief 获取支持类型名称的二进制数据
	/// @return 类型名称的二进制数据
	virtual const std_vector< uint8_t > & getSupportVarTypeNameBin( ) const {
		return supportVarTypeBin;
	}
	/// @brief 对象序列化到二进制
	/// @param result_vector 返回的二进制
	/// @return 二进制数量
	virtual size_t objToBin( std_vector< uint8_t > &result_vector ) const;
	/// @brief 加载二进制
	/// @param bin_data_ptr 数据起始位置
	/// @param bin_data_count 数据个数
	/// @return 使用数量
	virtual size_t loadBin( const uint8_t *bin_data_ptr, const size_t &bin_data_count );
	/// @brief 加载二进制
	/// @param bin_data_ptr 数据起始位置
	/// @param bin_data_count 数据个数
	/// @return 使用数量
	virtual size_t loadBin( const char *bin_data_ptr, const size_t &bin_data_count ) {
		return loadBin( ( const uint8_t * ) bin_data_ptr, bin_data_count );
	}
	/// @brief 加载二进制
	/// @param bin_vector 二进制列表
	/// @return 返回使用数据个数
	virtual size_t loadBin( const std_vector< uint8_t > &bin_vector ) {
		return loadBin( bin_vector.data( ), bin_vector.size( ) );
	}
	/// @brief 加载二进制
	/// @param bin_vector 二进制列表
	/// @return 返回使用数据个数
	virtual size_t loadBin( const QByteArray &bin_vector ) {
		return loadBin( bin_vector.data( ), bin_vector.size( ) );
	}
	/// @brief 根据节点目录与节点名称创建节点
	/// @param dir_name 目录名称
	/// @param node_name 节点名称
	/// @return 失败返回 nullptr
	virtual NodeItem* createNodeItem(const QString& dir_name, const QString& node_name);
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
protected:
	virtual size_t supportInfoToBin( );
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
