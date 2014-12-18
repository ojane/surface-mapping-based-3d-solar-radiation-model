

#include "CWainwindow.h"
//------------------------------------------------------------------
#include "GeometryWrapper.h"
#include "Utils.h"
#include "ViewerWidget2.h"
#include "osgEarth\Map"
#include "osgEarth\MapNode"
#include "osg\Node"
#include "osgDB\ReadFile"
#include "osgViewer\ViewerEventHandlers"
#include "osgEarthUtil\EarthManipulator"
#include "osgGA\StateSetManipulator"
#include "osg\Switch"
#include "ViewerWidget2.h"

int
main(int argc, char** argv)
{

    QApplication app(argc, argv);
    osgViewer::Viewer viewer;
    viewer.setCameraManipulator( new osgEarth::Util::EarthManipulator() );
	//viewer.getCamera()->setNearFarRatio(0.00002);
    viewer.getDatabasePager()->setDoPreCompile( true );
	viewer.addEventHandler(new osgViewer::StatsHandler());
	viewer.addEventHandler(new osgViewer::WindowSizeHandler());
	viewer.addEventHandler(new osgViewer::ThreadingHandler());
	viewer.addEventHandler(new osgViewer::LODScaleHandler());
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));


	osg::Switch* root = new osg::Switch();

	// set up a style to use for labels:

	osg::Node* node = osgDB::readNodeFile( "./SURSUN3D.earth" );
	if ( node )
		root->addChild( node );
	osgEarth::MapNode* mapNode = osgEarth::MapNode::findMapNode(node);

	osgEarth::Map* map = mapNode->getMap();


	viewer.setSceneData( root );


    QWidget* viewerWidget = new ViewerWidget2( &viewer);
    CMainWindow win(mapNode,&viewer,root);

    win.setCentralWidget( viewerWidget );
    //win.setGeometry(100, 100, 1024, 800);
    win.statusBar()->showMessage(QString::fromLocal8Bit("Interactive Application for Urban Solar Radiation"));
	app.setWindowIcon(QIcon("./images/logo.png"));
 //   win.showFullScreen();
	win.showMaximized();
    app.exec();
}
