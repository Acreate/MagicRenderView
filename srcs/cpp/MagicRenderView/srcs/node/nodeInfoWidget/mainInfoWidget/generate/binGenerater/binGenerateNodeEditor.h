#ifndef BINGENERATENODEEDITOR_H_H_HEAD__FILE__
#define BINGENERATENODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class BinGenerateTool;
class BinGenerateRenderWidget;
class BinGenerateRenderScrollArea;
class BinGenerateNode;
class UQVBoxLayout;
class BinGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	BinGenerateRenderScrollArea *generateRenderScrollArea;
	BinGenerateTool *addGenerateTool;
	std::vector< uint8_t > *bindGenerateVector;
	BinGenerateRenderWidget *generateRenderWidget;
protected:
	void releaseResource( ) override;
protected:
	virtual void addItem( BinGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant );
	virtual void requesPopItemMenu( QMenu *pop_menu );
public:
	BinGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< uint8_t > * getBindGenerateVector( ) const { return bindGenerateVector; }
	virtual void setBindGenerateVector( std::vector< uint8_t > *bind_generate_vector ) { bindGenerateVector = bind_generate_vector; }
	virtual void syncVarVector( );
	virtual bool updateGenerateItemInfo( );
	virtual void updateEditorNodeInfoLayout( );
protected:
	void resizeEvent( QResizeEvent * ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // BINGENERATENODEEDITOR_H_H_HEAD__FILE__
