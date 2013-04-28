/*
 * models.h
 *
 * header file for the equipment models of Subsurface
 *
 */
#ifndef MODELS_H
#define MODELS_H

#include <QAbstractTableModel>
#include "../dive.h"
#include "../divelist.h"
/* Encapsulates the tank_info global variable
 * to show on Qt`s Model View System.*/
class TankInfoModel : public QAbstractTableModel {
Q_OBJECT
public:
	enum Column { DESCRIPTION, ML, BAR};
	TankInfoModel();

	/*reimp*/ QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	/*reimp*/ int columnCount(const QModelIndex& parent = QModelIndex()) const;
	/*reimp*/ QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	/*reimp*/ int rowCount(const QModelIndex& parent = QModelIndex()) const;

	void add(const QString& description);
	void clear();
	void update();
private:
	int rows;
};

/* Encapsulation of the Cylinder Model, that presents the
 * Current cylinders that are used on a dive. */
class CylindersModel : public QAbstractTableModel {
Q_OBJECT
public:
	enum Column {TYPE, SIZE, MAXPRESS, START, END, O2, HE};

	explicit CylindersModel(QObject* parent = 0);
	/*reimp*/ QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	/*reimp*/ int columnCount(const QModelIndex& parent = QModelIndex()) const;
	/*reimp*/ QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	/*reimp*/ int rowCount(const QModelIndex& parent = QModelIndex()) const;

	void add(cylinder_t *cyl);
	void clear();
	void update();
private:
	dive *currentDive;

	/* Since the dive doesn`t stores the number of cylinders that
	 * it has ( max 8 ) and since I don`t want to make a
	 * model-for-each-dive, let`s hack this here instead. */
	QMap<dive*, int> usedRows;
};

/* Encapsulation of the Weight Model, that represents
 * the current weights on a dive. */
class WeightModel : public QAbstractTableModel {
	enum Column {TYPE, WEIGHT};
	/*reimp*/ QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	/*reimp*/ int columnCount(const QModelIndex& parent = QModelIndex()) const;
	/*reimp*/ QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	/*reimp*/ int rowCount(const QModelIndex& parent = QModelIndex()) const;

	void add(weight_t *weight);
	void clear();
	void update();
private:
	int rows;
};

/*! An AbstractItemModel for recording dive trip information such as a list of dives.
*
*/
class DiveItem;
class DiveTripModel : public QAbstractItemModel
{
public:
	enum Column {NR, DATE, RATING, DEPTH, DURATION, TEMPERATURE, TOTALWEIGHT, SUIT, CYLINDER, NITROX, SAC, OTU, MAXCNS, LOCATION, COLUMNS };

	DiveTripModel(QObject *parent = 0);

	/*reimp*/ Qt::ItemFlags flags(const QModelIndex &index) const;
	/*reimp*/ QVariant data(const QModelIndex &index, int role) const;
	/*reimp*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	/*reimp*/ int rowCount(const QModelIndex &parent) const;
	/*reimp*/ int columnCount(const QModelIndex &parent = QModelIndex()) const;
	/*reimp*/ QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	/*reimp*/ QModelIndex parent(const QModelIndex &child) const;

private:
	DiveItem *itemForIndex(const QModelIndex& index) const;
	DiveItem *rootItem;
};

#endif