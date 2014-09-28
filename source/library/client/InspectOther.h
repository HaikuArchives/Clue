#ifndef INSPECT_OTHER_H
#define INSPECT_OTHER_H

#include "ClueBuild.h"

#if defined(CLUE_ON_ZETA_HACK) && defined(CLUE_FOR_ZETA_GL)
#include <OpenGLKit.h>
#endif

void GetStatusTDescription (BString &, status_t, int32, const char *);

#if !defined(CLUE_ON_ZETA_HACK) || defined(CLUE_FOR_ZETA_GL)
void Inspect_BGLView (BString &, BGLView *, int32, const char *);
#endif

#endif //INSPECT_OTHER_H

