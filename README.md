qt-layout
=========

Qt5 Dynamic Layout Management using CMake and C++


Description
===========

This project provides dynamic widget layout management for Qt5 applications, dynamic meaning the layouts can be swapped out or modified at *run-time* instead of *compile-time*.

I designed this to plug directly into another cmake project, so the CMakeLists.txt file is not complete by itself (because it would not make sense for a layout manager to be built standalone).

Most of the description of how to use this code can be found in the INI file [profile.ini](profile.ini), but I will provide a brief overview here as well.  Basically, the INI file describes a list of widgets that can be displayed on the screen in a grid defined by the user (which could be anything from a 1x1 grid to 16x9 grid of squares on a widescreen monitor, or whatever else you want, as long as it is supported by QGridLayout).  All widgets that are initially visible, when loaded into the LayoutManager class, will be displayed on the screen, while the invisible widgets will not be (obviously).  But the INI file allows for describing the invisible widgets so an application can dynamically show/hide/swap out widgets very easily.

The LayoutProfile class is a wrapper for the QSettings class, and will read the INI file provided as an argument to the constructor and parse the widgets, storing them in a LayoutItem list.  The LayoutItem struct very closely resembles the INI file's "layout-items" objects, as expected.

The LayoutManager class is the real meat of this project.  It is itself a QWidget subclass with a QGridLayout, and provides convenience functions that resemble the QGridLayout `addWidget()` function so they are familiar to the user.


Example Usage
=============

Examples of how to use this code:

First off, set up one (or more) profiles for your application by creating an INI file for each, based on [profile.ini](profile.ini).  If you are already using an INI file and QSettings for application configuration, you can also add the layout settings in that file.  The LayoutProfile class will not modify or even read any values that are not described in the example profile.ini file.  The [QSettings documentation](http://doc.qt.io/qt-5/qsettings.html#accessing-settings-from-multiple-threads-or-processes-simultaneously) guarantees that having the same settings file opened by multiple QSettings objects (as will happen if you choose to add the layout profile to an existing INI file) will always work as expected, even across threads and processes.  All changes will be reflected on all QSettings objects tied to the same file instantly.

Next, in your application code, create a LayoutProfile object with the full path to the layout profile you just created.

```C
QString filepath = "/path/to/your/profile.ini";
LayoutProfile* profile = new LayoutProfile(filepath);
```

Now that the profile has been read in and all initial widgets have a location on the grid, the QWidgets must be associated with the LayoutItems (which have a QString name for easy reference).

```C
// squareWidget, verticalButtons, etc. are subclasses of QWidget
for (int i = 0; i < profile->numItems(); i++) {
   LayoutItem* item = profile->itemAt(i);
   if (item->name == "SquareWidget") {
      item->widget = squareWidget;
   }
   else if (item->name == "VerticalButtons") {
      item->widget = verticalButtons;
   }
   // ...
}
```

Unless your application has a small number of widgets, that approach could get really gross, thus a much cleaner method is also suggested for large applications.

Note that the widgets are also indexed by number in the profile file, so you could have some fancy QMap logic to avoid all the string comparisons.  Just make sure the int keys of the widgets correspond to the profile.ini you created.  You might also want to insert the LayoutItems into their own QMap for easy access in your application code.  Example:

```C
// squareWidget, verticalButtons, etc. are subclasses of QWidget
QMap<int, QWidget*> widgetMap;
map.insert(1, squareWidget); // SquareWidget is index 1 in profile.ini
map.insert(2, verticalButtons); // VerticalButtons is index 2 in profile.ini
// ...

QMap<int, LayoutItem*> layoutMap;
for (int i = 0; i < profile->numItems(); i++) {
   LayoutItem* item = profile->itemAt(i);
   item = widgetMap.value(i+1); // be careful of the indexing: widgetMap is 1-based, profile->itemAt() is 0-based
   layoutMap.insert(i+1, item); // see previous line comment
}
```

License
=======

Qt5 is distributed under a (dual-licensing)[http://www.qt.io/qt-licensing-terms/] plan, of which this project is specifically subject to its open-source license, which is the LGPL v. 3.  This project thus includes a copy of the LGPL v. 3 in the (LICENSE)[LICENSE] file.
