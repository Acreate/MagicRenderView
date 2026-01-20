#ifndef BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class QVBoxLayout;
class BinScrollBarEditorWidget;
class BinBinEditorWidget;
class BinOctEditorWidget;
class BinHexEditorWidget;
class BinDecimalEditorWidget;
class ChangeBinValueWidget;
class BinCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class BinCreateUnityNodeEditorWidget;
protected:
	BinDecimalEditorWidget *binDecimalEditorWidget;
	BinHexEditorWidget *binHexEditorWidget;
	BinOctEditorWidget *binOctEditorWidget;
	BinBinEditorWidget *binBinEditorWidget;
	BinScrollBarEditorWidget *binScrollBarEditorWidget;
	QVBoxLayout *mainLayout;
	 uint8_t currentVar;
	std::vector<ChangeBinValueWidget *> changeBinValueVector;
protected:
	virtual void sycValue( uint8_t new_value );
protected:
	BinCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent , uint8_t current_var);
	void releaseResource( ) override;
	virtual bool appendCompoment( ChangeBinValueWidget *append_widget );
public:
	bool initNode( Node *init_node ) override;
	~BinCreateUnityNodeEditorScrollArea( ) override;
Q_SIGNALS:
	void value_change_signal( uint8_t new_value );
protected:
	template< typename TCreateComponemtWidget >
		requires requires ( ChangeBinValueWidget *change_ptr, TCreateComponemtWidget *imp_type_widget ) {
			change_ptr = imp_type_widget;
		}
	TCreateComponemtWidget * addWigetToWidget( ) {
		auto result = new TCreateComponemtWidget( this );
		if( appendCompoment( result ) == true )
			return result;
		delete result;
		return nullptr;
	}
};

#endif // BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
