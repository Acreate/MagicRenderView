#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QDateTime>
#include <QObject>

#include <alias/type_alias.h>

#include <qt/enums/nodeItemEnum.h>

#include "nodeItemErrorInfo.h"
#include "nodeItemFinishInfo.h"

class NodeItemBuilderObj;
class QPainter;
class NodePort;
class VarGenerate;
class Application;
class QMenu;
class MainWidget;
class NodeItemInfo;
class NodeItemGenerateInfo;
class NodePortLinkInfo;
class I_Type;
class NodeItemInfoScrollAreaWidget;
class NodeItem;
class NodeOutputPort;
class NodeInputPort;
class NodeDirector : public QObject {
	Q_OBJECT;
public:

private:
	friend class NodeDirectorStack;
protected:
	/// @brief 绑定的主窗口
	MainWidget *mainWidget = nullptr;
	/// @brief 已经创建的实例
	std_vector< NodeItemInfo * > nodeItemInfoVector;
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
	/// @brief 选择节点列表
	std_vector< NodeItemInfo * > selectNodeItemVector;
	/// @brief 错误节点列表
	NodeItemErrorInfo errorNodeItemInfo;
	/// @brief 运行完成节点
	NodeItemFinishInfo finishNodeItemInfo;
protected:
	virtual bool createMenu( );
	virtual bool resetMenu( QObject *del_ptr );
	virtual bool rleaseNodeItem( NodeItem *release );
	virtual bool sortNodeItemInfo( );
	virtual void updateNodeItemInfo( );
	virtual bool connectLink( const size_t &input_nodeitem_code, const size_t &input_prot_code, const size_t &output_nodeitem_code, const size_t &outut_prot_code );
public:
	NodeDirector( QObject *parent = nullptr );
	~NodeDirector( ) override;
	virtual const NodeItemErrorInfo & getErrorNodeItemInfo( ) const { return errorNodeItemInfo; }
	virtual const NodeItemFinishInfo & getFinishNodeItemInfo( ) const { return finishNodeItemInfo; }
	virtual const std_vector< NodeItemInfo * > & getSelectNodeItemVector( ) const { return selectNodeItemVector; }
	virtual void setSelectNodeItemVector( const std_vector< const NodeItem * > &select_node_item_vector );
	virtual void setSelectNodeItem( const NodeItem *select_node_item );
	virtual void appendSelectNodeItem( const NodeItem *select_node_item );
	virtual void setSelectNodeItemVector( const std_vector< NodeItemInfo * > &select_node_item_info_vector );
	virtual void setSelectNodeItem( const NodeItemInfo *select_node_item );
	virtual void appendSelectNodeItem( const NodeItemInfo *select_node_item );
	virtual void clearSelect( );
	virtual void clearHighight( );
	virtual NodeItemBuilderObj * builderNodeItem( );
	virtual bool getNodeItemInfo( const NodeItem *get_nodeitem_ptr, NodeItemInfo *&result_link );
	virtual bool nodeItemInfoLeftConverVar( NodeItemInfo *input_node_item_ptr );
	virtual bool nodeItemInfRightConverVar( NodeItemInfo *output_node_item_ptr );
	virtual nodeItemEnum::Click_Type getClickNodeItem( NodeItem * &result_node_item, NodePort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItem( const QPoint &click_pos, NodeItem * &result_node_item, NodePort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItemInputPort( NodeItem * &result_node_item, NodeInputPort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItemInputPort( const QPoint &click_pos, NodeItem * &result_node_item, NodeInputPort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItemOutputPort( NodeItem * &result_node_item, NodeOutputPort * &result_node_port );
	virtual nodeItemEnum::Click_Type getClickNodeItemOutputPort( const QPoint &click_pos, NodeItem * &result_node_item, NodeOutputPort * &result_node_port );
	virtual QMenu * getNodeItemCraeteMenu( ) const {
		return nodeItemCreateMenu;
	}
	virtual bool linkInstallPort( NodePort *first_port, NodePort *scond_port );
	virtual bool linkUnInstallPort( NodePort *first_port, NodePort *scond_port );
	virtual bool linkInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port );
	virtual bool linkUnInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port );
	virtual bool setRaise( const NodeItem *raise_node_item );
	virtual bool setRaise( const NodePort *raise_node_port );
	virtual NodeItem * getLastNodeItem( );
	virtual std_vector< NodeItem * > getNodeItems( ) const;
	virtual std_vector< QImage * > getNodeItemRenders( ) const;

	//virtual bool release( const NodeItem *remove_node_item );
	virtual bool setContentWidget( MainWidget *main_widget );
	NodeItem * createNodeItem( const QString &dir_name, const QString &node_name, const std_shared_ptr< I_Type > &itype_ptr );
	NodeItem * createNodeItem( const QString &dir_name, const QString &node_name );
	size_t appendNodeItem( NodeItem *new_node_item );
	virtual MainWidget * getContentWidget( ) const {
		return mainWidget;
	}
	virtual const std_vector< NodePortLinkInfo * > & getLinkVectorPairt( ) const { return linkVectorPairt; }

	virtual bool getLinkOutPorts( const NodeInputPort *input_port, std_vector< NodeOutputPort * > &result_vector ) const;
	virtual bool getLinkOutPorts( const NodePort *input_port, std_vector< NodeOutputPort * > &result_vector ) const;
	virtual bool getLinkInputPorts( const NodeOutputPort *output_port, std_vector< NodeInputPort * > &result_vector ) const;
	virtual bool getLinkInputPorts( const NodePort *output_port, std_vector< NodeInputPort * > &result_vector ) const;

	virtual bool getLinkOutPorts( const NodeItem *input_port_node_item, std_vector_pairt< NodeInputPort *, std_vector< NodeOutputPort * > > &result_vector ) const;
	virtual bool getLinkInputPorts( const NodeItem *output_port_node_item, std_vector_pairt< NodeOutputPort *, std_vector< NodeInputPort * > > &result_vector ) const;

	virtual bool getLinkControlMenu( const NodePort *input_port, QMenu * &result_menu_ptr ) const;
	virtual bool getLinkControlMenu( const NodeInputPort *input_port, QMenu * &result_menu_ptr ) const;
	virtual bool getItemManageMenu( const NodeItem *node_item_ptr, QMenu * &result_menu_ptr );
	virtual bool renderLinkListHasNodeItem( const NodeInputPort *input_port, const NodeItem *node_item_ptr );
	virtual size_t toDataBin( std_vector< uint8_t > &result_data_vector );
	virtual size_t loadDataBin( const uint8_t *source_data_ptr, const size_t &source_data_count );
protected:
	virtual void updateNodeItemSort( );
protected:
	virtual void drawNodeItemLine( QPainter &painter_target ) const;
	virtual void drawNodeItemError( QPainter &painter_target ) const;
	virtual void drawNodeItemFinish( QPainter &painter_target ) const;
	virtual void drawNodeItemSelector( QPainter &painter_target ) const;
	virtual void drawNodeItemSelectorAndError( QPainter &painter_target ) const;
	virtual void drawNodeItemSelectorAndFinish( QPainter &painter_target ) const;
	virtual void drawNodeItemNormal( QPainter &painter_target ) const;
public:
	virtual void draw( QPainter &painter_target ) const;
protected:
	virtual void errorNodeItem( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_index, const NodeItemInfo *error_node_item_ptr, nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &msg, nodeItemEnum::Node_Item_Builder_Type info_type );
	virtual void finishNodeItem( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_index, const NodeItemInfo *finish_node_item_ptr );
Q_SIGNALS:
	void linkNodePortSignal( NodeDirector *sender_director_ptr, NodePortLinkInfo *control_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
	void unlinkNodePortSignal( NodeDirector *sender_director_ptr, NodePortLinkInfo *control_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
	void releaseThisSignal( NodeDirector *release_ptr );
	void releaseNodeItemInfoSignal( NodeItemInfo *release_ptr );
	void generateNodeItemSignal( NodeItem *create_ptr );
	void nodeItemInfoRefChangeInputNodeItem( NodeItemInfo *node_item_info );
	void nodeItemInfoRefChangeOutputNodeItem( NodeItemInfo *node_item_info );
	void error_node_item_signal( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_index, const NodeItemInfo *error_node_item_ptr, nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &msg, nodeItemEnum::Node_Item_Builder_Type info_type );
	void finish_node_item_signal( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_index, const NodeItemInfo *finish_node_item_ptr );
	void nodeItemFocusSignal( NodeItem *node_item_select );
	void reset_builder_node_item_signal( NodeItemBuilderObj *sender_sig_obj_ptr );
};

#endif // NODEDIRECTOR_H_H_HEAD__FILE__
