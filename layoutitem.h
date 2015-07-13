/* 
 * File:   layoutitem.h
 * Author: madtreat
 *
 * Created on July 13, 2015, 2:37 PM
 */

#ifndef LAYOUTITEM_H
#define LAYOUTITEM_H

#include <QWidget>
#include <QString>
#include <QDebug>

#ifdef	__cplusplus
extern "C" {
#endif

struct LayoutItem : public QObject {
   int row;
   int col;
   int rowSpan;
   int colSpan;
   bool visible;
   QWidget* widget;
   QString name;
   
   LayoutItem(QObject* _parent=0);
   LayoutItem(QWidget* _widget, QString _name, int _row, int _col, int _rowSpan=1, int _colSpan=1, bool _visible=false, QObject* _parent=0);
   LayoutItem(const LayoutItem& other);
   
   friend QDebug operator<<(QDebug os, const LayoutItem& item);
};
typedef QList<LayoutItem*> ItemList;

#ifdef	__cplusplus
}
#endif

#endif	/* LAYOUTITEM_H */

