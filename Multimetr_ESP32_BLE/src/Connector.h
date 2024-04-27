 #pragma once

#include <Arduino.h>

/*
  message receive type
  <mesBle>
    <no>3</no>
    <red>100</red>
    <gre>10</gre>
    <blu>255</blu>
  </mesBle>
*/

String findText(String str, String findContext,int mesNumbers=1, bool debug = false);
int findTextEnd(String str, String findContext="mesBle");
int findTextCount(String str, String findContext="mesBle");
