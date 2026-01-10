#ifndef UINTGENERATENODEEDITOR_H_H_HEAD__FILE__
#define UINTGENERATENODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class UIntGenerateTool;
class UIntGenerateRenderWidget;
class UIntGenerateRenderScrollArea;
class UIntGenerateNode;
class UQVBoxLayout;
class UIntGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	UIntGenerateRenderScrollArea *generateRenderScrollArea;
	UIntGenerateTool *addGenerateTool;
	std::vector< uint64_t > *bindGenerateVector;
	UIntGenerateRenderWidget *generateRenderWidget;
protected:
	void releaseResource( ) override;
protected:
	virtual void addItem( UIntGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant );
	virtual void requesPopItemMenu( QMenu *pop_menu );
public:
	UIntGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< uint64_t > * getBindGenerateVector( ) const { return bindGenerateVector; }
	virtual void setBindGenerateVector( std::vector< uint64_t > *bind_generate_vector ) { bindGenerateVector = bind_generate_vector; }
	virtual void syncVarVector( );
	virtual bool updateGenerateItemInfo( );
	virtual void updateEditorNodeInfoLayout( );
protected:
	void resizeEvent( QResizeEvent * ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // UINTGENERATENODEEDITOR_H_H_HEAD__FILE__
