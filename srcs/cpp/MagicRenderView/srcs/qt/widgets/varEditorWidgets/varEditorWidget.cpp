#include "varEditorWidget.h"
#include <QLineEdit>
#include <qboxlayout.h>

#include "../../application/application.h"

#include "../../generate/varGenerate.h"

#include "../../varType/I_Type.h"
#include "../../varType/I_Var.h"
VarEditorWidget::VarEditorWidget( QWidget *parent, I_Var *new_var_ptr ) : QWidget( parent ), var( new_var_ptr ) {
	varGenerate = Application::getApplicationInstancePtr( )->getVarGenerate( );
	varNameEdit = new QLineEdit( this );
	varValueEdit = new QLineEdit( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( varNameEdit );
	mainLayout->addWidget( varValueEdit );
}
VarEditorWidget::~VarEditorWidget( ) {

}
bool VarEditorWidget::getVar( I_Var *result_var ) const {
	bool result = false;
	if( var == nullptr )
		return result;
	auto &thisTypeInfo = var->getTypeInfo( )->getTypeInfo( );
	if( thisTypeInfo != result_var->getTypeInfo( )->getTypeInfo( ) )
		return result;
	auto varSourcePtr = var->getP( );
	if( varSourcePtr == nullptr )
		return result;
	auto varTargetPtr = result_var->getP( );
	result = varGenerate->conver( thisTypeInfo, varTargetPtr, thisTypeInfo, varSourcePtr );
	return result;
}
bool VarEditorWidget::setValue( const type_info &var_type_info, const void *set_var_ptr ) {
	if( var == nullptr )
		return false;
	const auto &typeInfo = var->getTypeInfo( )->getTypeInfo( );
	if( var_type_info != typeInfo )
		return false;
	auto targetPtr = var->getP( );
	if( targetPtr == nullptr )
		return false;
	bool conver = varGenerate->conver( typeInfo, targetPtr, var_type_info, set_var_ptr );
	if( conver == false )
		return false;
	return updateEditorContent( );
}
bool VarEditorWidget::updateEditorContent( ) {

	if( var == nullptr )
		return false;
	auto varPtr = var->getP( );
	auto &typeInfo = var->getTypeInfo( )->getTypeInfo( );
	QString buff;
	if( varGenerate->conver( typeid( QString ), &buff, typeInfo, varPtr ) == false )
		return false;
	varValueEdit->setText( buff );
	varNameEdit->setText( var->getVarName( ) );
	return true;
}
bool VarEditorWidget::getVarName( QString &result_name ) const {
	if( var == nullptr )
		return false;
	result_name = var->getVarName( );
	return true;
}
void VarEditorWidget::setVarName( const QString &new_var_name ) {
	if( var == nullptr )
		return;
	var->setVarName( new_var_name );
}
const type_info & VarEditorWidget::getTypeInfo( ) const {
	if( var == nullptr )
		return typeid( nullptr );
	return var->getTypeInfo( )->getTypeInfo( );
}
bool VarEditorWidget::isNullPtr( ) const {
	if( var == nullptr || var->getP( ) == nullptr )
		return true;
	return false;
}
