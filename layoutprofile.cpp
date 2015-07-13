/* 
 * File:   layoutprofile.cpp
 * Author: madtreat
 * 
 * Created on July 13, 2015, 1:39 PM
 */

#include "layoutprofile.h"
#include <QSettings>
#include <QDebug>

LayoutProfile::LayoutProfile(QString _filepath, QObject* _parent)
: QObject(_parent),
  filepath(_filepath),
  width(0),
  height(0)
{
   qDebug() << "Loading LayoutProfile from file:";
   qDebug() << "  " << filepath;
   settings = new QSettings(filepath, QSettings::IniFormat);
   loadLayoutProfile();
   qDebug() << "   with" << QString::number(itemList.size()) << "layout items";
}

//LayoutProfile::LayoutProfile(const LayoutProfile& orig) {
//}

LayoutProfile::~LayoutProfile() {
}

LayoutItem* LayoutProfile::getItemByName(QString name) const
{
   for (int i = 0; i < itemList.size(); i++) {
      LayoutItem* item = itemList.at(i);
      if (item->name == name) {
         return item;
      }
   }
   return NULL;
}

void LayoutProfile::loadLayoutProfile() {
   settings->beginGroup("layout");
   width = settings->value("width").toInt();
   height = settings->value("height").toInt();
   settings->endGroup(); // "layout"
   qDebug() << "   Grid size:" << width << "x" << height;
   qDebug() << "   Child groups:" << settings->childGroups();
   
   int size = settings->beginReadArray("layout-items");
   for (int i = 0; i < size; i++) {
      settings->setArrayIndex(i);
      LayoutItem* item = new LayoutItem();
      item->name = settings->value("name").toString();
      item->row = settings->value("row").toInt();
      item->col = settings->value("col").toInt();
      item->rowSpan = settings->value("rowSpan").toInt();
      item->colSpan = settings->value("colSpan").toInt();
      item->visible = settings->value("visible").toBool();
      itemList.append(item);
   }
   settings->endArray(); // "layout-items"
}
