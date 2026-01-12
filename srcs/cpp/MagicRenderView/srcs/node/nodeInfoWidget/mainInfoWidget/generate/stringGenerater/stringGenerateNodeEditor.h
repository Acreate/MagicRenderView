#ifndef STRINGGENERATENODEEDITOR_H_H_HEAD__FILE__
#define STRINGGENERATENODEEDITOR_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class StringGenerateTool;
class StringGenerateRenderWidget;
class StringGenerateRenderScrollArea;
class StringGenerateNode;
class UQVBoxLayout;
class StringGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	StringGenerateRenderScrollArea *generateRenderScrollArea;
	StringGenerateTool *addGenerateTool;
	std::vector< QString > *stringGenerateVector;
	StringGenerateRenderWidget *generateRenderWidget;
protected:
	void releaseResource( ) override;
protected:
	virtual void addItem( StringGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant );
	virtual void requesPopItemMenu( QMenu *pop_menu );
public:
	StringGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< QString > * getBindGenerateVector( ) const { return stringGenerateVector; }
	virtual void setBindGenerateVector( std::vector< QString > *bind_generate_vector ) { stringGenerateVector = bind_generate_vector; }
	virtual void syncVarVector( );
	virtual bool updateGenerateItemInfo( );
	virtual void updateEditorNodeInfoLayout( );
protected:
	void resizeEvent( QResizeEvent * ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // STRINGGENERATENODEEDITOR_H_H_HEAD__FILE__
