//#define DEBUG 1

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#ifndef _CLUE_AREA_MANAGER_H
#include "ClueAreaManager.h"
#endif

static const char* g_AreaName = "Clue Data Exchange";


/***************************************************************
***************************************************************/
ClueAreaManager :: ClueAreaManager
(
	void
)
	:	m_data(NULL)
	,	m_area_id(0)
{
	PRINT(("CAM : do find_area.\n"));
	area_id source_area_id(find_area(g_AreaName));
	if (B_OK > source_area_id) {
		PRINT(("CAM : area was NOT found, create it using '%s'\n", g_AreaName));
		//doesn't exist yet, so we must create it!
		m_area_id = create_area(g_AreaName, (void**) &m_data, B_ANY_ADDRESS,
								B_PAGE_SIZE, B_NO_LOCK, B_READ_AREA | B_WRITE_AREA);
		if (B_OK >= m_area_id) {
			PRINT(("CAM : HUGE ERROR!, create_area failed, %i.\n", m_area_id));
			//yes, greater than AND equal to!
		}
		m_data->m_port = B_ERROR;
		memset(m_data->m_mask, 0, sizeof(uint32) * 1000);  //should be able to go to 1024 with B_PAGE_SIZE!
		//m_data->m_mask = 0L;
		m_data->m_refcount = 1;
		PRINT(("CAM : Created area.\n"));
	} else {
		PRINT(("CAM : area was found, clone it using '%s'.\n", g_AreaName));
		m_area_id = clone_area(g_AreaName, (void**) &m_data, B_ANY_ADDRESS,
							   B_READ_AREA | B_WRITE_AREA, source_area_id);
		if (B_OK >= m_area_id) {
			PRINT(("CAM : HUGE ERROR!, clone_area failed, %i.\n", m_area_id));
			//serious error, what should we do?!!!
		}
		atomic_add(&(m_data->m_refcount), 1);
		PRINT(("CAM : Cloned area.\n"));
	}
}


/***************************************************************
***************************************************************/
ClueAreaManager :: ~ClueAreaManager
(
	void
)
{
	delete_area(m_area_id);
//	atomic_add (&(m_data->refcount), -1);
//	PRINT (("CAM : refcount = %i.\n", m_data->refcount));
//	if (m_data->refcount <= 0)
//	{
//		//delete the area, as we were the last ones referencing it!!!
//		delete_area (m_area_id);
//		PRINT (("CAM : Deleted area.\n"));
//	}
//	else
//	{
//		PRINT (("CAM : reference count was > 0.\n"));
//	}
}

