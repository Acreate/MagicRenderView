#ifndef BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class ScrollValueChangeWidget;
class DecTitleLineEdit;
class OctTitleLineEdit;
class HexTitleLineEdit;
class BinTitleLineEdit;
class NumberVarLineEdit;
class NumberVarTitleLineEdit;
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
	using UCompomentWidget = NumberVarTitleLineEdit;
protected:
	DecTitleLineEdit *decTitleLineEdit;
	HexTitleLineEdit *hexTitleLineEdit;
	OctTitleLineEdit *octTitleLineEdit;
	BinTitleLineEdit *binTitleLineEdit;
	ScrollValueChangeWidget *scrollValueChangeWidget;
	QVBoxLayout *mainLayout;
	uint8_t currentVar;
	std::vector< UCompomentWidget * > compomentWidgetVector;
	UCompomentWidget *currentCom;
	QWidget *mainWidget;
protected Q_SLOTS:
	void textChanged_Slot( NumberVarTitleLineEdit *sender_obj, NumberVarLineEdit *edite_event, const QString &text );
	void valueChange_Slot( int curren_scroll_bar_point );
protected:
	BinCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, uint8_t current_var );
	void releaseResource( ) override;
protected:
	virtual bool appendCompoment( UCompomentWidget *append_widget );
public:
	bool initNode( Node *init_node ) override;
	~BinCreateUnityNodeEditorScrollArea( ) override;
Q_SIGNALS:
	void value_change_signal( uint8_t new_value );
protected:
	template< typename TCreateComponemtWidget, typename ...Args >
		requires requires ( UCompomentWidget *change_ptr, TCreateComponemtWidget *imp_type_widget ) {
			change_ptr = imp_type_widget;
		}
	TCreateComponemtWidget * addWigetToWidget( Args ...args ) {
		auto result = new TCreateComponemtWidget( args ... );
		if( appendCompoment( result ) == true )
			return result;
		delete result;
		return nullptr;
	}

};

#endif // BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
