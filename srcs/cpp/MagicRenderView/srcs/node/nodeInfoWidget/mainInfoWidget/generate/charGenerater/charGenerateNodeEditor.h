#ifndef CHARGENERATENODEEDITOR_H_H_HEAD__FILE__
#define CHARGENERATENODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class CharGenerateTool;
class CharGenerateRenderWidget;
class CharGenerateRenderScrollArea;
class CharGenerateNode;
class UQVBoxLayout;
class CharGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	CharGenerateRenderScrollArea *generateRenderScrollArea;
	CharGenerateTool *addGenerateTool;
	std::vector< QChar > *charGenerateVector;
	CharGenerateRenderWidget *generateRenderWidget;
protected:
	void releaseResource( ) override;
protected:
	virtual void addItem( CharGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant );
	virtual void requesPopItemMenu( QMenu *pop_menu );
public:
	CharGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< QChar > * getBindGenerateVector( ) const { return charGenerateVector; }
	virtual void setBindGenerateVector( std::vector< QChar > *bind_generate_vector ) { charGenerateVector = bind_generate_vector; }
	virtual void syncVarVector( );
	virtual bool updateGenerateItemInfo( );
	virtual void updateEditorNodeInfoLayout( );
protected:
	void resizeEvent( QResizeEvent * ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // CHARGENERATENODEEDITOR_H_H_HEAD__FILE__
