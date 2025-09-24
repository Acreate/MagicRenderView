#include "./colorType.h"

#include "../I_Type.h"
ColorType::ColorType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) { }
ColorType::ColorType( ) : ColorType( nullptr ) {
}
ColorType::~ColorType( ) {
	delete var;
}
