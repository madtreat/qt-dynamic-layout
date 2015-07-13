/* 
 * File:   layoutmanager.h
 * Author: madtreat
 *
 * Created on July 13, 2015, 11:23 AM
 */

#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H

#include <QWidget>
#include <QList>
#include <QGridLayout>

#include "layoutitem.h"


class LayoutManager : public QWidget {
   Q_OBJECT;
   
public:
   LayoutManager(QWidget* _parent=0);
   LayoutManager(const LayoutManager& orig) = delete;
   virtual ~LayoutManager();
   
   void addWidget(QWidget* widget, int row, int col, int rowSpan=1, int colSpan=1, bool visible=true);
   void addWidget(LayoutItem* item);
   
   void replaceItem(LayoutItem* item, QWidget* widget);
   void replaceItem(LayoutItem* item1, LayoutItem* item2);
   
   void swapItems(LayoutItem* item1, LayoutItem* item2);
   
   QSize gridSize() const { return QSize(layout->columnCount(), layout->rowCount()); }
   
private:
   QGridLayout* layout;
   ItemList items; // list of visible items
   ItemList invisibleItems; // list of invisible items that can be swapped later
};

#endif	/* LAYOUTGRID_H */

