#ifndef IMAGEGENERATENODEEDITOR_H_H_HEAD__FILE__
#define IMAGEGENERATENODEEDITOR_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class ImageGenerateTool;
class ImageGenerateRenderWidget;
class ImageGenerateRenderScrollArea;
class ImageGenerateNode;
class UQVBoxLayout;
class ImageGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	ImageGenerateRenderScrollArea *generateRenderScrollArea;
	ImageGenerateTool *addGenerateTool;
	std::vector< QImage > *generateVector;
	ImageGenerateRenderWidget *generateRenderWidget;
protected:
	void releaseResource( ) override;
protected:
	virtual void addItem( ImageGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant );
	virtual void requesPopItemMenu( QMenu *pop_menu );
public:
	ImageGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< QImage > * getBindGenerateVector( ) const { return generateVector; }
	virtual void setBindGenerateVector( std::vector< QImage > *bind_generate_vector ) { generateVector = bind_generate_vector; }
	virtual void syncVarVector( );
	virtual bool updateGenerateItemInfo( );
	virtual void updateEditorNodeInfoLayout( );
protected:
	void resizeEvent( QResizeEvent * ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // IMAGEGENERATENODEEDITOR_H_H_HEAD__FILE__
