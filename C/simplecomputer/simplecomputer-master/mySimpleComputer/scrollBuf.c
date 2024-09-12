#include "mSC.h"
#include <print.h>
#include <stdio.h>

void
scrollBuf ()
{
  sprintf (_SCROLL_BUFFER[4], "%s", _SCROLL_BUFFER[3]);
  sprintf (_SCROLL_BUFFER[3], "%s", _SCROLL_BUFFER[2]);
  sprintf (_SCROLL_BUFFER[2], "%s", _SCROLL_BUFFER[1]);
  sprintf (_SCROLL_BUFFER[1], "%s", _SCROLL_BUFFER[0]);
}