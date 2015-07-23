/* 
 * File:   layoutmanager.cpp
 * Author: madtreat
 * 
 * Created on July 13, 2015, 11:23 AM
 */

#include "layoutmanager.h"
#include <QGridLayout>


LayoutManager::LayoutManager(QWidget* _parent)
: QWidget(_parent)
{
   layout = new QGridLayout(this);
   layout->setContentsMargins(0, 0, 0, 0);
}

//LayoutGrid::LayoutGrid(const LayoutGrid& orig) {
//}

LayoutManager::~LayoutManager() {
}

void LayoutManager::addWidget(QWidget* widget, int row, int col, int rowSpan, int colSpan, bool visible)
{
   LayoutItem* item = new LayoutItem(this);
   item->widget = widget;
   item->row = row;
   item->col = col;
   item->rowSpan = rowSpan;
   item->colSpan = colSpan;
   item->visible = visible;
   addWidget(item);
}

void LayoutManager::addWidget(LayoutItem* item)
{
   if (item->visible) {
      items.append(item);
      layout->addWidget(item->widget, item->row, item->col, item->rowSpan, item->colSpan);
      item->widget->setVisible(true);
   }
   else {
      invisibleItems.append(item);
      item->widget->setVisible(false);
   }
}

/*
 * Replaces item1 with widget using the same layout dimensions.
 */
void LayoutManager::replaceItem(LayoutItem* item, QWidget* widget)
{
   
   LayoutItem* item2 = new LayoutItem(*item);
   item2->widget = widget;
   replaceItem(item, item2);
}

/*
 * Replaces item1 with item2 using item2's layout dimensions.  Be careful with 
 * this as it does not ensure the items are the same dimensions.  This function
 *  can lead to unintended overlapping of widgets if used incorrectly.
 */
void LayoutManager::replaceItem(LayoutItem* item1, LayoutItem* item2)
{
   layout->removeWidget(item1->widget);
   item1->visible = false;
   item2->visible = true;
   items.removeOne(item1);
   if (invisibleItems.contains(item2)) {
      invisibleItems.removeOne(item2);
   }
   items.append(item2);
   invisibleItems.append(item1);
   item1->widget->setVisible(item1->visible);
   item2->widget->setVisible(item2->visible);
   addWidget(item2);
}

/*
 * Swaps the two LayoutItems' positions on the grid.  This function modifies the
 * items' rows and columns instead of the simpler method of switching the
 * widgets and names so that the items can be used in a QMap or similar data
 * structure without causing problems.
 */
void LayoutManager::swapItems(LayoutItem* item1, LayoutItem* item2)
{
   layout->removeWidget(item1->widget);
   layout->removeWidget(item2->widget);
   
   LayoutItem* item1copy = new LayoutItem(*item1);
   
   item1->row     = item2->row;
   item1->col     = item2->col;
   item1->rowSpan = item2->rowSpan;
   item1->colSpan = item2->colSpan;
   item1->visible = item2->visible;
   
   item2->row     = item1copy->row;
   item2->col     = item1copy->col;
   item2->rowSpan = item1copy->rowSpan;
   item2->colSpan = item1copy->colSpan;
   item2->visible = item1copy->visible;
   
   delete item1copy;
   
   addWidget(item1);
   addWidget(item2);
}