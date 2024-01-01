#include "init.h"

void	init_nmbrs(t_container **book)
{
	(*book)->eof_sig = FALSE;
	(*book)->exit_status = 0;
	(*book)->in_pipe = FALSE;
	(*book)->nmbr_exec = 0;
}
