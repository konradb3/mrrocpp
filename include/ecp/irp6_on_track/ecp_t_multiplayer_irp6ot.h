#if !defined(_ECP_T_MULTIPLAYER_IRP6OT_H)
#define _ECP_T_MULTIPLAYER_IRP6OT_H

#include "ecp/common/ecp_task.h"
#include "ecp/common/ecp_t_rcsc.h"
#include "ecp/common/ecp_generator_t.h"

class ecp_task_multiplayer_irp6ot : public ecp_task
{
private:
    ecp_generator_t* gt;
    ecp_smooth_generator* sg;
    bias_edp_force_generator* befg;
    weight_meassure_generator* wmg;

public:
    ecp_task_multiplayer_irp6ot(configurator &_config);
    ~ecp_task_multiplayer_irp6ot();

    // methods for ECP template to redefine in concrete classes
    void task_initialization(void);
    void main_task_algorithm(void);
};

#endif
