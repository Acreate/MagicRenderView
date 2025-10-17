#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QDateTime>
#include <QObject>

#include "../../../alias/type_alias.h"

#include "../item/nodeItem.h"

class NodeItemInfo;
class NodeItemGenerateInfo;
class NodePortLinkInfo;
class I_Type;
class NodeItemInfoScrollAreaWidget;
class NodeItem;
class NodeEditorWidget;
class NodeOutputPort;
class NodeInputPort;
class NodeDirector : public QObject {
	Q_OBJECT;
protected:
	/// @brief 绑定的主窗口
	MainWidget *mainWidget = nullptr;
	/// @brief 节点实例编辑窗口
	std_vector< NodeItemInfoScrollAreaWidget * > nodeItemInfoScrollAreaWidgets;
	/// @brief 已经创建的实例
	std_vector< NodeItemInfo * > generateNodeItems;
	/// @brief 节点生成实例对象列表
	std_vector< std_shared_ptr< NodeItemGenerateInfo > > generateNodeItemInfos;
	/// @brief 连接列表
	std_vector< NodePortLinkInfo * > linkVectorPairt;
	/// @brief 节点创建菜单
	QMenu *nodeItemCreateMenu = nullptr;
	/// @brief 当前进程实例
	Application *applicationInstancePtr = nullptr;
	/// @brief 对象生成实例
	VarGenerate *varGenerate = nullptr;
	/// @brief 节点编译运行对象指针
	NodeItemBuilderLink* nodeItemBuilderLink;
protected:
	virtual bool addManagementWidget( NodeItemInfoScrollAreaWidget *add_widget );
	virtual bool removeManagementWidget( NodeItemInfoScrollAreaWidget *del_widget );
	virtual bool createMenu( );
	virtual bool resetMenu( QObject *del_ptr );
	virtual bool rleaseNodeItem( NodeItem *release );
	//virtual bool releaseNodeItemInfo( NodeItemInfo *del_ptr );
	virtual bool getNodeItemInputLink( const NodeItem *get_nodeitem_ptr, std_vector< NodePortLinkInfo * > &result_link );
	virtual bool getNodeItemInfo( const NodeItem *get_nodeitem_ptr, NodeItemInfo *&result_link );
public:
	NodeDirector( QObject *parent = nullptr );
	~NodeDirector( ) override;

	virtual bool getNodeItemRender( QImage &result_render_image, const QPoint &offset = QPoint( 0, 0 ) ) const;
	virtual bool getNodeItemRender( QImage &result_render_image ) const {
		return getNodeItemRender( result_render_image, QPoint( 0, 0 ) );
	}
	virtual nodeItemEnum::Click_Type getClickNodeItem( NodeItem * &result_node_item, NodePort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItem( const QPoint &click_pos, NodeItem * &result_node_item, NodePort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItemInputPort( NodeItem * &result_node_item, NodeInputPort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItemInputPort( const QPoint &click_pos, NodeItem * &result_node_item, NodeInputPort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItemOutputPort( NodeItem * &result_node_item, NodeOutputPort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItemOutputPort( const QPoint &click_pos, NodeItem * &result_node_item, NodeOutputPort * &result_node_port );
	virtual QMenu * getNodeItemCraeteMenu( ) const {
		return nodeItemCreateMenu;
	}
	virtual NodeItemInfoScrollAreaWidget * requestGetNodeEditorWidget( const type_info &request_type, NodeItem *request_node_item_ptr );
	virtual bool linkInstallPort( NodePort *first_port, NodePort *scond_port );
	virtual bool linkUnInstallPort( NodePort *first_port, NodePort *scond_port );
	virtual bool linkInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port );
	virtual bool linkUnInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port );
	virtual size_t run( );
	virtual bool setRaise( const NodeItem *raise_node_item );
	virtual bool setRaise( const NodePort *raise_node_port );
	virtual NodeItem * getLastNodeItem( );
	virtual void draw( QPainter &painter_target ) const;
	virtual std_vector< NodeItem * > getNodeItems( ) const;
	virtual std_vector< QImage * > getNodeItemRenders( ) const;

	//virtual bool release( const NodeItem *remove_node_item );
	virtual bool setContentWidget( MainWidget *main_widget );
	NodeItem * createNodeItem( const QString &dir_name, const QString &node_name, const std_shared_ptr< I_Type > &itype_ptr );
	NodeItem * createNodeItem( const QString &dir_name, const QString &node_name);
	size_t appendNodeItem( NodeItem *new_node_item );
	virtual MainWidget * getContentWidget( ) const {
		return mainWidget;
	}
	virtual const std_vector< NodePortLinkInfo * > & getLinkVectorPairt( ) const { return linkVectorPairt; }
	virtual bool getLinkOutPorts( const NodeInputPort *input_port, std_vector< NodeOutputPort * > &result_vector ) const;
	virtual bool getLinkOutPorts( const NodePort *input_port, std_vector< NodeOutputPort * > &result_vector ) const;
	virtual bool getLinkControlMenu( const NodePort *input_port, QMenu * &result_menu_ptr ) const;
	virtual bool getLinkControlMenu( const NodeInputPort *input_port, QMenu * &result_menu_ptr ) const;
	virtual bool getItemManageMenu( const NodeItem *node_item_ptr, QMenu * &result_menu_ptr );
	virtual bool renderLinkListHasNodeItem( const NodeInputPort *input_port, const NodeItem *node_item_ptr );
Q_SIGNALS:
	void linkNodePortSignal( NodeDirector *sender_director_ptr, NodePortLinkInfo *control_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
	void unlinkNodePortSignal( NodeDirector *sender_director_ptr, NodePortLinkInfo *control_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
	void releaseThisSignal( NodeDirector *release_ptr );
	void releaseNodeItemInfoSignal( NodeItemInfo *release_ptr );
	void generateNodeItemSignal( NodeItem *create_ptr );
};

#endif // NODEDIRECTOR_H_H_HEAD__FILE__
