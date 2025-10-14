#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../../alias/type_alias.h"

#include "../item/nodeItem.h"

class I_Type;
class NodeItemInfoScrollAreaWidget;
class NodeItem;
class NodeEditorWidget;
class NodeOutputPort;
class NodeInputPort;
class NodeDirector : public QObject {
	Q_OBJECT;
protected:
	class NodeItemGenerateInfo {
		QString dirName;
		QString nodeName;
		std_shared_ptr< I_Type > createTypeInstancePtr;
	public:
		virtual ~NodeItemGenerateInfo( ) = default;
		NodeItemGenerateInfo( const QString &dir_name, const QString &node_name, const std_shared_ptr< I_Type > &create_type_instance_ptr )
			: dirName( dir_name ),
			nodeName( node_name ),
			createTypeInstancePtr( create_type_instance_ptr ) { }
		virtual const QString & getDirName( ) const { return dirName; }
		virtual const QString & getNodeName( ) const { return nodeName; }
		virtual const std_shared_ptr< I_Type > & getCreateTypeInstancePtr( ) const { return createTypeInstancePtr; }
		virtual bool isNodeType( const QString &dir_name, const QString &node_name ) {
			return dirName == dir_name && nodeName == node_name;
		}
		virtual NodeItem * createNodeItem( const QString &dir_name, const QString &node_name );
	};
protected:
	/// @brief 绑定的主窗口
	MainWidget *mainWidget = nullptr;
	/// @brief 节点实例编辑窗口
	std_vector< NodeItemInfoScrollAreaWidget * > nodeItemInfoScrollAreaWidgets;
	/// @brief 已经创建的实例
	std_vector< NodeItem * > generateNodeItems;
	/// @brief 节点生成实例对象列表
	std_vector< std_shared_ptr< NodeItemGenerateInfo > > generateNodeItemInfos;
	/// @brief 节点创建菜单
	QMenu *nodeItemCreateMenu = nullptr;
	/// @brief 当前进程实例
	Application *applicationInstancePtr = nullptr;
	/// @brief 对象生成实例
	VarGenerate *varGenerate = nullptr;
protected:
	virtual bool addManagementWidget( NodeItemInfoScrollAreaWidget *add_widget );
	virtual bool removeManagementWidget( NodeItemInfoScrollAreaWidget *del_widget );
	virtual bool remove( NodeItem *remove_node_item );
	virtual bool createMenu();
public:
	NodeDirector( QObject *parent = nullptr );
	~NodeDirector( ) override;

	virtual bool getNodeItemRender( QImage &result_render_image, const QPoint &offset = QPoint( 0, 0 ) ) const;
	virtual bool getNodeItemRender( QImage &result_render_image ) const {
		return getNodeItemRender( result_render_image, QPoint( 0, 0 ) );
	}
	virtual NodeItem::Click_Type getClickNodeItem( NodeItem * &result_node_item, NodePort * &result_node_port );
	virtual NodeItem::Click_Type getClickNodeItem( const QPoint &click_pos, NodeItem * &result_node_item, NodePort * &result_node_port );
	virtual NodeItem::Click_Type getClickNodeItemInputPort( NodeItem * &result_node_item, NodeInputPort * &result_node_port );
	virtual NodeItem::Click_Type getClickNodeItemInputPort( const QPoint &click_pos, NodeItem * &result_node_item, NodeInputPort * &result_node_port );
	virtual NodeItem::Click_Type getClickNodeItemOutputPort( NodeItem * &result_node_item, NodeOutputPort * &result_node_port );
	virtual NodeItem::Click_Type getClickNodeItemOutputPort( const QPoint &click_pos, NodeItem * &result_node_item, NodeOutputPort * &result_node_port );
	virtual QMenu * getNodeItemCraeteMenu( ) const {
		return nodeItemCreateMenu;
	}
	virtual NodeItemInfoScrollAreaWidget * requestGetNodeEditorWidget( const type_info &request_type, NodeItem *request_node_item_ptr );
	virtual bool linkInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port );
	virtual bool linkUnInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port );
	virtual size_t run( );
	virtual bool raise( const NodeItem *raise_node_item );
	virtual bool raise( const NodePort *raise_node_port );
	virtual NodeItem * getLastNodeItem( ) {
		size_t count = generateNodeItems.size( );
		if( count == 0 )
			return nullptr;
		return generateNodeItems.data( )[ count - 1 ];
	}
	virtual void draw( QPainter &painter_target ) const;
	virtual std_vector< NodeItem * > getNodeItems( ) const {
		return generateNodeItems;
	}
	virtual std_vector< QImage * > getNodeItemRenders( ) const;

	virtual bool release( const NodeItem *remove_node_item );
	virtual bool setContentWidget( MainWidget *main_widget );
	NodeItem * createNodeItem( const QString &dir_name, const QString &node_name, const std_shared_ptr< I_Type > &itype_ptr );
	size_t appendNodeItem( NodeItem *new_node_item );
	virtual MainWidget * getContentWidget( ) const {
		return mainWidget;
	}
};

#endif // NODEDIRECTOR_H_H_HEAD__FILE__
