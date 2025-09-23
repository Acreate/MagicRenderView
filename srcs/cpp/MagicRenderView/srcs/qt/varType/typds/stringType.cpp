#include "./stringType.h"

#include "../I_Type.h"
StringType::StringType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
}
