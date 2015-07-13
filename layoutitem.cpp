/* 
 * File:   layoutitem.h
 * Author: madtreat
 *
 * Created on July 13, 2015, 2:37 PM
 */

#include "layoutitem.h"


LayoutItem::LayoutItem(QObject* _parent)
: QObject(_parent),
  row(0),
  col(0),
  rowSpan(1),
  colSpan(1),
  visible(false)
{
   widget = NULL;
}

LayoutItem::LayoutItem(QWidget* _widget, QString _name, int _row, int _col, int _rowSpan, int _colSpan, bool _visible, QObject* _parent) 
: QObject(_parent),
  row(_row),
  col(_col),
  rowSpan(_rowSpan),
  colSpan(_colSpan),
  visible(_visible),
  name(_name),
  widget(_widget)
{
}

LayoutItem::LayoutItem(const LayoutItem& other)
: QObject(other.parent())
{
   row = other.row;
   col = other.col;
   rowSpan = other.rowSpan;
   colSpan = other.colSpan;
   visible = other.visible;
   name = other.name;
   widget = other.widget;
}

QDebug operator<<(QDebug os, const LayoutItem& item) {
   os << "LayoutItem [" << item.name << "] (visible =" << item.visible << "):\n";
   os << "  row, col:" << item.row << "," << item.col << "\n";
   os << "  rowSpan, colSpan:" << item.rowSpan << "," << item.colSpan << "\n";
   return os;
}