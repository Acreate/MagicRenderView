#ifndef NODEINFOEDITORDIRECTOR_H_H_HEAD__FILE__
#define NODEINFOEDITORDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

namespace NodeEnum {
	enum class NodeType;
}
class Node;
class NodeInfoWidget;
class Application;
class MainWidget;
class MainWindow;
class MainWidgetScrollArea;
class NodeInfoEditorDirector : public QObject {
	Q_OBJECT;
protected:
	Application *instancePtr;
	MainWidget *mainWidget;
	MainWindow *mainWindow;
	MainWidgetScrollArea *mainWidgetScrollArea;
protected:
	using MTKey = NodeEnum::NodeType;
	using MTCreateFunction = std::function< NodeInfoWidget *( Node * ) >;
	template< typename V >
	using MTValue = std::vector< V >;
	template< typename K, typename V >
	using MTVector = std::vector< std::pair< K, V > >;
	MTVector< MTKey, MTValue< MTCreateFunction > > generaterNodeInfoEditorWidgetMap;
	std::vector< NodeInfoWidget * > editorWidgetPackage;
public:
	NodeInfoEditorDirector( );
	~NodeInfoEditorDirector( ) override;
	virtual bool init( );
	virtual bool getNodeInfoEditorWidget( Node *node_ptr, NodeInfoWidget *&result_node_info_editor_widget );

	/// @brief 清理资源（清理隐藏与空指针窗口）
	virtual void clearNodeEditorResources( );
	/// @brief 释放所有节点
	virtual void releaseNodeEditor( );
protected:
	virtual void appendEditorWidgetPackage( NodeInfoWidget *node_info_widget );
	virtual bool appendCreateWidget( MTKey key, const MTCreateFunction &create_function );
	virtual bool checkCreateWidget( Node *node_ptr, NodeInfoWidget *create_widget );
protected Q_SLOTS:
	virtual void hide_NodeInfoWidget_signal( NodeInfoWidget *hide_ptr );
protected:
	template< typename TNodeInfoEditorWidget, typename = std::enable_if_t< std::is_base_of_v< NodeInfoWidget, TNodeInfoEditorWidget > > >
	bool appendCreateWidget( MTKey key ) {
		MTCreateFunction appendCreateFunction = [this] ( Node *node )->NodeInfoWidget * {
			auto *result = new TNodeInfoEditorWidget;
			if( checkCreateWidget( node, result ) == true )
				return result;
			delete result;
			return nullptr;
		};
		return appendCreateWidget( key, appendCreateFunction );
	}
};

#endif // NODEINFOEDITORDIRECTOR_H_H_HEAD__FILE__
