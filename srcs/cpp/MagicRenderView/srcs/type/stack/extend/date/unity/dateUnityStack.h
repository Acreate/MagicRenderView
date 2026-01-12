#ifndef DATEUNITYSTACK_H_H_HEAD__FILE__
#define DATEUNITYSTACK_H_H_HEAD__FILE__

#include <type/infoStack.h>

class DateUnityStack : public InfoStack {
	Q_OBJECT;
protected:
	QString *dateTimeFormat;
public:
	DateUnityStack( );
	~DateUnityStack( ) override;
protected:
	bool init( VarDirector *var_director ) override;
public:
	bool toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) override;
	TypeEnum::Type getType( ) override;
protected:
	bool toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
};

#endif // DATEUNITYSTACK_H_H_HEAD__FILE__
