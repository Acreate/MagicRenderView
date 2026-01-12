#ifndef COLORGENERATENODEEDITOR_H_H_HEAD__FILE__
#define COLORGENERATENODEEDITOR_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class ColorGenerateTool;
class ColorGenerateRenderWidget;
class ColorGenerateRenderScrollArea;
class ColorGenerateNode;
class UQVBoxLayout;
class ColorGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	ColorGenerateRenderScrollArea *generateRenderScrollArea;
	ColorGenerateTool *addGenerateTool;
	std::vector< QColor > *colorGenerateVector;
	ColorGenerateRenderWidget *generateRenderWidget;
protected:
	void releaseResource( ) override;
protected:
	virtual void addItem( ColorGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant );
	virtual void requesPopItemMenu( QMenu *pop_menu );
public:
	ColorGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< QColor > * getBindGenerateVector( ) const { return colorGenerateVector; }
	virtual void setBindGenerateVector( std::vector< QColor > *bind_generate_vector ) { colorGenerateVector = bind_generate_vector; }
	virtual void syncVarVector( );
	virtual bool updateGenerateItemInfo( );
	virtual void updateEditorNodeInfoLayout( );
protected:
	void resizeEvent( QResizeEvent * ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // COLORGENERATENODEEDITOR_H_H_HEAD__FILE__
