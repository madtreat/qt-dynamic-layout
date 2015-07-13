/* 
 * File:   layoutprofile.h
 * Author: madtreat
 *
 * Created on July 13, 2015, 1:39 PM
 */

#ifndef LAYOUTPROFILE_H
#define LAYOUTPROFILE_H

#include <QObject>
#include <QString>

#include "layoutitem.h"

class QSettings;


class LayoutProfile : public QObject {
   Q_OBJECT;
   
public:
   LayoutProfile(QString _filepath, QObject* _parent=0);
   LayoutProfile(const LayoutProfile& orig) = delete;
   virtual ~LayoutProfile();
   
   int getGridWidth() const { return width; }
   int getGridHeight() const { return height; }
   
   int numItems() const { return itemList.size(); }
   ItemList getItemlist() const { return itemList; }
   LayoutItem* itemAt(int i) const { return itemList.at(i); }
   LayoutItem* getItemByName(QString name) const;
   
private:
   QString filepath; // filename including full path
   QSettings* settings;
   
   int width; // layout grid width
   int height; // layout grid height
   
   ItemList itemList;
   
   void loadLayoutProfile();
};

#endif	/* LAYOUTPROFILE_H */

