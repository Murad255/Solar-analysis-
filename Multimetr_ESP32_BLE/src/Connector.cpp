#include "Connector.h"

String findText(String str, String findContext, int mesNumbers, bool debug)
{
  int end = 0;

  if (mesNumbers > 1)
  {
    for (int i = 0; i < mesNumbers; i++)
    {
      end =str.indexOf("</" + findContext + ">",end );
      if (end > 0)
      {
        end += ("</" + findContext + ">").length();
      }
      end++;
    }
  }
  int find1 = str.indexOf("<" + findContext + ">", end);
  int find2 = str.indexOf("</" + findContext + ">", end);
  if (debug)
    Serial.println("find1:" + String(find1) + " find2:" + String(find2));

  if ((find1 < 1) || (find2 < 1))
    return "";
  String findStr = "";
  for (int i = find1 + ("<" + findContext + ">").length(); i < find2; i++)
  {
    findStr += str[i];
  }

  return findStr;
}

int findTextCount(String str, String findContext)
{

  int find = 0;

  int findCount = 0;

  do
  {
    find = str.indexOf("</" + findContext + ">");
    if (find > 0)
    {
      findCount++;
      find += ("</" + findContext + ">").length();
    }

  } while (find != 0);

  return findCount;
}

int findTextEnd(String str, String findContext)
{

  int find = str.indexOf("</" + findContext + ">");
  if (find > 0)
  {
    find += ("</" + findContext + ">").length();
  }

  return find;
}