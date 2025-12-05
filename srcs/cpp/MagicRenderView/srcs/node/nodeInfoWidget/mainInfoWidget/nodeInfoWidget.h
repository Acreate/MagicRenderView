#ifndef NODEINFOWIDGET_H_H_HEAD__FILE__
#define NODEINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class BottomNodeInfoTool;
class NodeInfoTitle;
class EditorNodeInfoScrollArea;
class QLabel;
class Node;
class MainWindow;
class NodeInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	MainWindow *parentMainWindow;
	Node *node;
	NodeInfoTitle *titile;
	BottomNodeInfoTool *buttonWidget;
	QScrollArea *infoScrollArea;
	EditorNodeInfoScrollArea *editorNodeInfoScrollArea;
public:
	NodeInfoWidget( MainWindow *parent );
	~NodeInfoWidget( ) override;
	virtual bool isNodeTypeInfoWidget( Node *check_node_ptr ) const;
	virtual bool isNodeInfo( Node *check_node_ptr ) =0;
protected:
	virtual void okButtonEvent( ) = 0;
	virtual void cancelButtonEvent( ) = 0;
protected:
	bool eventFilter( QObject *event_obj_ptr, QEvent *event_type ) override;
	bool event( QEvent * ) override;
Q_SIGNALS:
	void release_signal( NodeInfoWidget *release_ptr );
	void hide_signal( NodeInfoWidget *hide_ptr );
	void show_signal( NodeInfoWidget *show_ptr );
	void ok_signal( );
	void cancel_signal( );
};

#endif // NODEINFOWIDGET_H_H_HEAD__FILE__
