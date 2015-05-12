

#include "CWainwindow.h"

int
main(int argc, char** argv)
{

    QApplication app(argc, argv);


 //   osgViewer::Viewer viewer;
 //   viewer.setCameraManipulator( new osgEarth::Util::EarthManipulator() );
	////viewer.getCamera()->setNearFarRatio(0.00002);
 //   viewer.getDatabasePager()->setDoPreCompile( true );
	//viewer.addEventHandler(new osgViewer::StatsHandler());
	//viewer.addEventHandler(new osgViewer::WindowSizeHandler());
	//viewer.addEventHandler(new osgViewer::ThreadingHandler());
	//viewer.addEventHandler(new osgViewer::LODScaleHandler());
	//viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));


	


    CMainWindow win;
	
    //win.setGeometry(100, 100, 1024, 800);
    win.statusBar()->showMessage(QString::fromLocal8Bit("Interactive Application for Urban Solar Radiation"));
	app.setWindowIcon(QIcon("./images/logo.png"));
 //   win.showFullScreen();
	win.showMaximized();
    app.exec();
}
