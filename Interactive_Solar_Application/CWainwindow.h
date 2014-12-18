#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "ui_mymainwindow.h"
//#include "ILayerManager.h"
//#include "ObstacleManager.h"
//#include "FlightBoundManager.h"
//#include "RouteManager.h"
#include "IGlobalInterfaces.h"
#include "DlgBuildingParams.h"
#include "qevent.h"
#include "osgEarth\Map"
#include "osgEarth\ElevationQuery"
#include "osgEarth\Terrain"
#include "osgEarth\MapNode"
#include <osgEarthQt\ViewerWidget>
#include "DlgBuildingParams.h"
#include "DlgParams.h"
#include "City.h"
#include "osgUtil\LineSegmentIntersector"
#include "osgUtil\IntersectionVisitor"
#include "osg\Point"
#include "osg\PointSprite"
#include <osgUtil\LineSegmentIntersector>
#include "NorthArrow.h"
#include "TemporalSolarWidget.h"
#include "Utils.h"
#include "QCustomPlot/QCustomPlot.h"
#include "osgEarthQt/MapCatalogWidget"
#include "osgEarthQt/DataManager"
#include "osgEarthSymbology/Style"
#include "osgEarthAnnotation/PlaceNode"
#include "osgDB/WriteFile"
class CMainWindow : public QMainWindow, public IGlobalInterfaces,public osgGA::GUIEventHandler
{
	Q_OBJECT

public:
	CMainWindow(osgEarth::MapNode* mapnode,osgViewer::Viewer* viewer,osg::Switch* root);
	~CMainWindow();	
	  virtual void setMessage(QString message){g_pTextBox->setText(message);} 
	   void save();
	   virtual void execute();
	   virtual void export();
       virtual void setProgress(int min,int max,int val);
	   virtual void updateSolarPanel();
	   void createMonthlyPlot(QCustomPlot* customPlot);
	   void createDailyPlot(QCustomPlot* customPlot);
	   void createFacadeWidget(QWidget* widget);
	   bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
private:
	//Ui::CMainWindow ui;
	const osgEarth::Map*       g_pMap;
	const osgEarth::Terrain*   g_pTerrain;
	bool             g_pMouseDown;
	osgEarth::ElevationQuery   g_pQuery;
	osgViewer::Viewer* g_pViewer;
	osg::Group* g_pRoot;
	SolarParam g_mSParam;
	osg::MatrixTransform* g_pSolarNodes;
	osg::MatrixTransform* g_pSolarPanelNodes;
	osgEarth::MapNode* g_pMapNode; 
	City* g_pCity;
	osg::Vec3d g_mTranslation;
	DlgBuildingParams* g_pDlgBuildingParams;	
	QCustomPlot* m_gDailyRadPlot;
	QCustomPlot* m_gMonthlyRadPlot;
	QWidget* m_gFacadeWidget;
	osgEarth::Annotation::PlaceNode* g_pMousePoint;
    QProgressBar* g_ProgressBar;
	QLineEdit* g_pTextBox;
	bool g_mIsMouseDown;
	osg::Vec2 g_mLastMousePos;
};

#endif // MYMAINWINDOW_H
