#ifndef _CLUE_AREA_MANAGER_H
#define _CLUE_AREA_MANAGER_H

#ifndef _OS_H
#include <OS.h>
#endif

class ClueAreaManager {
public:
	ClueAreaManager(void);
	~ClueAreaManager(void);
private:
	ClueAreaManager(const ClueAreaManager&);
	ClueAreaManager& operator= (ClueAreaManager&);
public:
	struct ClueAreaManagerData {
		int32		m_refcount;
		port_id		m_port;
		uint32		m_mask[100];
	}* m_data;
	area_id		m_area_id;
};

#endif



