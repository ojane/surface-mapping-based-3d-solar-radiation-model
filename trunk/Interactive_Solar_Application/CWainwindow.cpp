#include "CWainwindow.h"
#include "osgEarth\Registry"

//osg::ref_ptr<osg::MatrixTransform> g_pDynamicNode;

void CMainWindow::createMonthlyPlot(QCustomPlot* customPlot)
{

	SolarAnalysisParams* analysisParam = IGlobalInterfaces::getInstance()->getSolarAnalysisParams();
	int xrang = analysisParam->MonthlySeries.size();
	float miny = FLT_MAX;
	float maxy = -FLT_MAX;
	for(int i=0;i<analysisParam->MonthlySeries.size();i++)
	{
		SolarRadiation& rad = analysisParam->MonthlySeries[i];
		if(miny>rad.global)
			miny = rad.global;
		if(maxy<rad.global)
			maxy=rad.global;
	}
	float yrange = maxy-miny;
	int w = customPlot->width();
	int h = customPlot->height();
	QPainterPath path;

	customPlot->legend->setVisible(true);
	customPlot->legend->setFont(QFont("Arial", 12));
	customPlot->legend->setName("irradiation [kWh/m-2]");
	customPlot->xAxis->setName("irradiation");
	customPlot->xAxis->setLabel("month");	
	customPlot->xAxis->setLabelFont(QFont("Arial", 12));
	customPlot->yAxis->setName("irradiation [kWh/m-2]");
	customPlot->yAxis->setLabel("irradiation [kWh/m-2]");
	customPlot->yAxis->setLabelFont(QFont("Arial", 12));

	QPen pen;
	QStringList lineNames;

	//global radiation
	customPlot->addGraph();
	pen.setColor(QColor(0,0,255));
	customPlot->graph()->setPen(pen);
	customPlot->graph()->setName("Global radiation");
	customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
	customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

	QVector<double> x(analysisParam->MonthlySeries.size()), y(analysisParam->MonthlySeries.size());
	for (int j=0; j<analysisParam->MonthlySeries.size(); ++j)
	{
		SolarRadiation& rad = analysisParam->MonthlySeries[j];
		x[j] = analysisParam->FirstDay+j;
		y[j] = rad.global;
	}


	customPlot->graph()->setData(x, y);
	customPlot->graph()->rescaleAxes(true);



	///direct
	customPlot->addGraph();
	pen.setColor(QColor(0,255,255));
	customPlot->graph()->setPen(pen);
	customPlot->graph()->setName("Direct radiation");
	customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
	customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

	for (int j=0; j<analysisParam->MonthlySeries.size(); ++j)
	{
		SolarRadiation& rad = analysisParam->MonthlySeries[j];
		x[j] = analysisParam->FirstDay+j;
		y[j] = rad.beam;
	}


	customPlot->graph()->setData(x, y);
	customPlot->graph()->rescaleAxes(true);


	//diffuse
	customPlot->addGraph();
	pen.setColor(QColor(255,255,0));
	customPlot->graph()->setPen(pen);
	customPlot->graph()->setName("Diffuse radiation");
	customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
	customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, 2));
	for (int j=0; j<analysisParam->MonthlySeries.size(); ++j)
	{
		SolarRadiation& rad = analysisParam->MonthlySeries[j];
		x[j] = analysisParam->FirstDay+j;
		y[j] = rad.diffuse;
	}


	customPlot->graph()->setData(x, y);
	customPlot->graph()->rescaleAxes(true);
	QVector<double> tickVector(12);
	for (int i=0;i<12;i++)
	{
		tickVector[i]=i+1;
	}

	// zoom out a bit:
	//customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
	//customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());
	customPlot->xAxis->setTickStep(1);
	customPlot->xAxis->setTicks(true);
	customPlot->xAxis->setTickVector(tickVector);
	customPlot->xAxis->setAutoTicks(false);
	customPlot->yAxis->setTicks(true);
	customPlot->xAxis->setTickLabels(true);
	customPlot->yAxis->setTickLabels(true);
	customPlot->xAxis->setRange(1,12);
	// make top right axes clones of bottom left axes:
	customPlot->axisRect()->setupFullAxesBox();
	customPlot->setWindowTitle("monthly solar irridiation [kWh/m-2]");
	customPlot->setCaption("monthly solar irridiation [kWh/m-2]");
}
void CMainWindow::createDailyPlot(QCustomPlot* customPlot)
{

	SolarAnalysisParams* analysisParam = IGlobalInterfaces::getInstance()->getSolarAnalysisParams();
	int xrang = analysisParam->DailySeries.size();
	float miny = FLT_MAX;
	float maxy = -FLT_MAX;
	for(int i=0;i<analysisParam->DailySeries.size();i++)
	{
		SolarRadiation& rad = analysisParam->DailySeries[i];
		if(miny>rad.global)
			miny = rad.global;
		if(maxy<rad.global)
			maxy=rad.global;
	}
	float yrange = maxy-miny;
	int w = customPlot->width();
	int h = customPlot->height();
	QPainterPath path;

	customPlot->legend->setVisible(true);
	customPlot->legend->setFont(QFont("Arial", 12));
	customPlot->legend->setName("irradiation [Wh/m-2]");
	customPlot->xAxis->setName("irradiation");
	customPlot->xAxis->setLabel("day");	
	customPlot->xAxis->setLabelFont(QFont("Arial", 12));
	customPlot->yAxis->setName("irradiation [Wh/m-2]");
	customPlot->yAxis->setLabel("irradiation [Wh/m-2]");
	customPlot->yAxis->setLabelFont(QFont("Arial", 12));

	QPen pen;
	QStringList lineNames;

	//global radiation
	customPlot->addGraph();
	pen.setColor(QColor(0,0,255));
	customPlot->graph()->setPen(pen);
	customPlot->graph()->setName("Global radiation");
	customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
	customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

	QVector<double> x(analysisParam->DailySeries.size()), y(analysisParam->DailySeries.size());
	for (int j=0; j<analysisParam->DailySeries.size(); ++j)
	{
	    SolarRadiation& rad = analysisParam->DailySeries[j];
		x[j] = analysisParam->FirstDay+j;
		y[j] = rad.global;
	}


	customPlot->graph()->setData(x, y);
	customPlot->graph()->rescaleAxes(true);



	///direct
	customPlot->addGraph();
	pen.setColor(QColor(0,255,255));
	customPlot->graph()->setPen(pen);
	customPlot->graph()->setName("Direct radiation");
	customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
	customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

	for (int j=0; j<analysisParam->DailySeries.size(); ++j)
	{
		SolarRadiation& rad = analysisParam->DailySeries[j];
		x[j] = analysisParam->FirstDay+j;
		y[j] = rad.beam;
	}


	customPlot->graph()->setData(x, y);
	customPlot->graph()->rescaleAxes(true);


	//diffuse
	customPlot->addGraph();
	pen.setColor(QColor(255,255,0));
	customPlot->graph()->setPen(pen);
	customPlot->graph()->setName("Diffuse radiation");
	customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
	customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, 2));
	for (int j=0; j<analysisParam->DailySeries.size(); ++j)
	{
		SolarRadiation& rad = analysisParam->DailySeries[j];
		x[j] = analysisParam->FirstDay+j;
		y[j] = rad.diffuse;
	}


	customPlot->graph()->setData(x, y);
	customPlot->graph()->rescaleAxes(true);


	// zoom out a bit:
	//customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
	//customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());
	// set blank axis lines:
	QVector<double> tickVector(analysisParam->DailySeries.size());
	for (int i=0;i<analysisParam->DailySeries.size();i++)
	{
       tickVector[i]=(analysisParam->FirstDay+i);
	}
	 //tickVector[12]=(365);
	customPlot->xAxis->setAutoTicks(true);
	customPlot->xAxis->setRange(1,analysisParam->DailySeries.size());
	//customPlot->xAxis->setTickStep(13);
	customPlot->xAxis->setTickVector(tickVector);
	customPlot->xAxis->setTicks(true);
	customPlot->yAxis->setTicks(true);
	customPlot->xAxis->setTickLabels(true);
	customPlot->yAxis->setTickLabels(true);
	// make top right axes clones of bottom left axes:
	customPlot->axisRect()->setupFullAxesBox();
	customPlot->setWindowTitle("daily solar irridiation [Wh/m-2]");
	customPlot->setCaption("daily solar irridiation [Wh/m-2]");
}

void CMainWindow::createFacadeWidget(QWidget* widget)
{


	//QPixmap pixmap(g_pCity->getFacadeImagePath(0));
	//QPalette   palette;
	//palette.setBrush(widget->backgroundRole(),QBrush(pixmap));
	//widget->setPalette(palette);
	//widget->setMask(pixmap.mask());  //可以将图片中透明部分显示为透明的
	//widget->setAutoFillBackground(true);//width: 100%; height:100%; 

	//widget->setStyleSheet("background-image: url(" + g_pCity->getFacadeImagePath(0) + "); background-repeat: none; border: none");
    widget->setStyleSheet("border-image: url(" + g_pCity->getFacadeImagePath(0) + ") 10 10 10 10 stretch stretch;");

	//:"border-image:url(background.png) 10 10 10 10 stretch stretch;");  ///使用border-image可以实现背景的
	widget->setCaption("Facade irradiation");
}


bool CMainWindow::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{

	SolarAnalysisParams* params = IGlobalInterfaces::getInstance()->getSolarAnalysisParams();

	if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH)
	{
		g_mIsMouseDown = true;
		g_mLastMousePos = osg::Vec2(ea.getX(),ea.getY());
	}

	if (params->QueryMode != SpatialQueryMode::Disabled 
		&& ea.getEventType() == osgGA::GUIEventAdapter::RELEASE 
		&& ea.getEventType() != osgGA::GUIEventAdapter::DOUBLECLICK
		&& ea.getEventType() != osgGA::GUIEventAdapter::DRAG)
	{
		g_mIsMouseDown = false;
		osg::Vec2 curMousePos(ea.getX(),ea.getY());
		if((curMousePos-g_mLastMousePos).length() > 2)
		{
			return false;
		}

		g_mIsMouseDown = false;
		osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);   

		osg::ref_ptr<osgUtil::LineSegmentIntersector> ray = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, ea.getXnormalized(), ea.getYnormalized());
		osgUtil::IntersectionVisitor visitor(ray);
		view->getCamera()->accept(visitor);
		if (ray->containsIntersections())
		{
			osgUtil::LineSegmentIntersector::Intersection intersection = ray->getFirstIntersection();
			params->WorldIntersectionPoint = intersection.getWorldIntersectPoint();
			params->IntersectionNormal = intersection.getWorldIntersectNormal();
			params->IntersectionPoint = intersection.getWorldIntersectPoint()-g_mTranslation;//osg::Vec3d(329542.6607715,4690819.062525,0);
			osg::Vec3d geopos;
			g_pMapNode->getMapSRS()->transform( params->WorldIntersectionPoint,osgEarth::Registry::instance()->getGlobalGeodeticProfile()->getSRS(),geopos);
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << "lonlat: " << geopos.x() << "," << geopos.y();
			QString info = ss.str().data();
			//QString info =QString("coordinates: ") + QString::number(params->IntersectionPoint.x(), 'g', 2) + "," + QString::number(params->IntersectionPoint.y(), 'g', 2);
			setMessage(info);
			//g_pMainWin->setMessage(QString("coordinates: %1, %2, %3 (meters)").arg(params->IntersectionPoint.x()).arg(params->IntersectionPoint.y()).arg(params->IntersectionPoint.z()));  
			g_pCity->setMousePos(params->IntersectionPoint);/*params->QueryMode == SpatialQueryMode::Point &&*/
			g_pMousePoint->setPosition(osgEarth::GeoPoint(g_pMapNode->getMapSRS(),params->WorldIntersectionPoint));

			if(g_pSolarPanelNodes->getNumChildren() > 0)
			{
				g_pSolarPanelNodes->removeChildren(0,g_pSolarPanelNodes->getNumChildren());
			}
			if(params->QueryMode == SpatialQueryMode::Point)
			{			

				if(params->SolarPanelIncluded)
				{			
					Building* building;	
					osg::ref_ptr<osg::Node> panelNode = g_pCity->getPanelNode(params->IntersectionPoint.x(),params->IntersectionPoint.y(),building);
				    g_pDlgBuildingParams->setBuilding(building);
					//g_pSolarPanelNodes->removeChildren(0,g_pSolarPanelNodes->getNumChildren());
					g_pSolarPanelNodes->addChild(panelNode.get());
				}


			}
			return true;
		}
	}

	return false;
}
CMainWindow::CMainWindow(osgEarth::MapNode* mapnode,osgViewer::Viewer* viewer,osg::Switch* root)
	: QMainWindow(NULL),
	g_pTerrain  ( mapnode->getTerrain() ),
	g_pQuery    ( mapnode->getMap() )

{
	
	g_pMap = mapnode->getMap(); 
	g_pMapNode = mapnode;
	g_pViewer = viewer;
    g_pRoot = root;  
	//the boston city models was originally centered at (0,0,0), a translation needs to be applied here
	g_mTranslation =osg::Vec3d(329542.6607715,4690819.062525,0);
	City* city = new City; 
	city->setFileName("./boston/boston.dat","./out_texture_dir");
	city->open();
	g_pCity = city;
	osg::ref_ptr<osg::MatrixTransform> boston = new osg::MatrixTransform;
	boston->setMatrix(osg::Matrix::translate(g_mTranslation));
    boston->addChild(city->toOSG(true,true));

	g_pSolarNodes = new osg::MatrixTransform;
	g_pSolarNodes->setMatrix(osg::Matrix::translate(g_mTranslation));

	g_pSolarPanelNodes = new osg::MatrixTransform;
	g_pSolarPanelNodes->setMatrix(osg::Matrix::translate(g_mTranslation));

	//SceneEventHandler* handler = new SceneEventHandler;

   	viewer->addEventHandler(this);
	g_pRoot = root;
	root->addChild(boston.get());
	root->addChild(g_pSolarNodes);
	root->addChild(g_pSolarPanelNodes);
    root->addChild(createNorthArrow(g_pViewer,"northarrow.png"));
    g_pElevationQuery = new osgEarth::ElevationQuery(g_pMapNode->getMap());
	IGlobalInterfaces::setInstance(this);
	this->setWindowTitle(QString::fromLocal8Bit("Interactive urban solar analysis"));

	QDockWidget *buildingParamsDock = new QDockWidget(QWidget::tr("Building Parameters"));
	buildingParamsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

   DlgParams* dlg = new DlgParams;
   buildingParamsDock->setWidget(dlg);
   addDockWidget(Qt::LeftDockWidgetArea, buildingParamsDock);

   QDockWidget *buildPropDock = new QDockWidget(QWidget::tr("Parameters"));
   buildPropDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
   g_pDlgBuildingParams = new DlgBuildingParams;
   g_pViewer = viewer;
   buildPropDock->setWidget(g_pDlgBuildingParams);

   addDockWidget(Qt::RightDockWidgetArea, buildPropDock);


   osg::ref_ptr<osgEarth::QtGui::DataManager> dataManager = new osgEarth::QtGui::DataManager(mapnode);
   QDockWidget *catalogDock = new QDockWidget(QWidget::tr("MapLayers"));
   catalogDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
   osgEarth::QtGui::MapCatalogWidget* layerCatalog = new osgEarth::QtGui::MapCatalogWidget(dataManager.get(), osgEarth::QtGui::MapCatalogWidget::ALL_LAYERS);
   //layerCatalog->setActiveViews(views);
   layerCatalog->setHideEmptyGroups(true);
   catalogDock->setWidget(layerCatalog);
   addDockWidget(Qt::RightDockWidgetArea, catalogDock);



   IGlobalInterfaces::getInstance()->getSolarAnalysisParams()->Viewer = g_pViewer;
   IGlobalInterfaces::getInstance()->getSolarAnalysisParams()->MainWin = this;
   IGlobalInterfaces::getInstance()->getSolarAnalysisParams()->ModelTranslation = g_mTranslation;




   osgEarth::Symbology::Style style("PlaceNode");

   osg::ref_ptr<osgEarth::Symbology::TextSymbol> textSymbol = new osgEarth::Symbology::TextSymbol;
   textSymbol->alignment() = osgEarth::Symbology::TextSymbol::ALIGN_BASE_LINE;
   textSymbol->encoding() = osgEarth::Symbology::TextSymbol::ENCODING_UTF8;
   textSymbol->font() =  std::string("fonts/simfang.ttf");
   //textSymbol->fill()->color() = osgEarth::Symbology::Color:;
   textSymbol->size() = 15;
   //textSymbol->halo()->width() = priority;
   style.addSymbol(textSymbol.get());

   osg::ref_ptr<osg::Image> image = osgDB::readImageFile("placemark32.png");

   g_pMousePoint = new osgEarth::Annotation::PlaceNode(g_pMapNode,osgEarth::GeoPoint(g_pMapNode->getMapSRS(),g_mTranslation),image.get(),"",style);
   g_pMousePoint->setName("PlaceNode");
   root->addChild(g_pMousePoint);


 //  	QToolBar* fileToolBar = addToolBar(QString::fromLocal8Bit("工具栏"));
	//QAction* actionDachidu = new QAction(QIcon("../data/images/dachidu.png"), QString::fromLocal8Bit("大尺度"), this);
	//actionDachidu->setStatusTip("大尺度效果展示");
	//connect(actionDachidu, SIGNAL(triggered()), this, SLOT(onAction_Dachidu()));
	//fileToolBar->addAction(actionDachidu);
   m_gDailyRadPlot = NULL;
   m_gMonthlyRadPlot = NULL;
   m_gFacadeWidget = NULL;


   g_ProgressBar = new QProgressBar();
   g_ProgressBar->setAlignment(Qt::AlignRight);
   g_ProgressBar->setVisible(true);
   //g_ProgressBar->setMaximumSize(512, 19);
   g_pTextBox = new QLineEdit();
   g_pTextBox->setMinimumWidth(128);
   g_pTextBox->setMaximumWidth(128);
   statusBar()->addWidget(g_pTextBox,0);
   statusBar()->addWidget(g_ProgressBar,1);

}

CMainWindow::~CMainWindow()
{
	UINT ExitCode = 0 ;
	::TerminateProcess(::GetCurrentProcess(), ExitCode);
}

void CMainWindow::save()
{

}

void CMainWindow::execute()
{
	if(getSolarAnalysisParams()->AnalysisMode == Surface_based)
	{
		osg::ref_ptr<osg::Node> solarNodes = g_pCity->createSolarNodes();
		//osgDB::writeNodeFile(*solarNodes,"solar.osg");
		g_pSolarNodes->removeChildren(0,g_pSolarNodes->getNumChildren());
		g_pSolarNodes->addChild(solarNodes.get());
		g_pSolarPanelNodes->removeChildren(0,g_pSolarPanelNodes->getNumChildren());
		if(g_pDlgBuildingParams->getBuilding())
			g_pDlgBuildingParams->getBuilding()->Panel.Node = NULL;
	}
	else
	{
	
		getSolarAnalysisParams()->DailySeries = g_pCity->getDailySolarRadiation(getSolarAnalysisParams()->getDays());
		//getSolarAnalysisParams()->MonthlySeries = g_pCity->getMonthlySolarRadiation(getSolarAnalysisParams()->DailySeries,getSolarAnalysisParams()->FirstDay,getSolarAnalysisParams()->LastDay);
		//if(getSolarAnalysisParams()->DailySeries.size() < 10)
		//{
		//	QMessageBox::critical(this,"ALERT","at least 10 days needed!");
		//	return;
		//}
		//TemporalSolarWidget solarWidget;
		//solarWidget.exec();

		if(m_gDailyRadPlot)
		{
			delete m_gDailyRadPlot;
			m_gDailyRadPlot = NULL;
		}
		m_gDailyRadPlot = new QCustomPlot;
		m_gDailyRadPlot->setMinimumSize(512,256);
		m_gDailyRadPlot->setGeometry(m_gDailyRadPlot->x(),30,512,256);
		createDailyPlot(m_gDailyRadPlot);
		m_gDailyRadPlot->showNormal();


		//if(m_gMonthlyRadPlot)
		//{
		//	delete m_gMonthlyRadPlot;
		//	m_gMonthlyRadPlot = NULL;
		//}
		//m_gMonthlyRadPlot = new QCustomPlot;

		//createMonthlyPlot(m_gMonthlyRadPlot);
		//m_gMonthlyRadPlot->showNormal();
	}

}

void CMainWindow::export()
{
	//QString filters("ive files (*.ive);;osg files (*.osg);;osgb files (*.osgb);;obj files (*.obj);;3ds files (*.3ds);;dae files (*.dae);;fbx files (*.fbx);;all files (*.*)");
	//QString filters("ive files (*.ive);;osg files (*.osg);;osgb files (*.osgb);;obj files (*.obj);;3ds files (*.3ds);;dae files (*.dae);;fbx files (*.fbx);;all files (*.*)");
	QString filters("osgb files (*.osgb);;ive files (*.ive);;osg files (*.osg);;all files (*.*)");
	QString dir = QFileDialog::getSaveFileName(0,QString::fromLocal8Bit("Export"),"./",filters);
	if(dir == "") return;

	std::string fileName = dir.toLatin1().data();
	//osgDB::Options* opt = osgDB::Registry::instance()->getOptions();
	//osg::ref_ptr<osgDB::Options> opt = new osgDB::Options("WriteImageHint=IncludeData");
	//opt->setPluginStringData("WriteImageHint=IncludeFile");
	//osgDB::writeNodeFile(*g_pSolarNodes,fileName,opt);
    g_pCity->exportNodes(fileName);

}

void CMainWindow::setProgress( int min,int max,int val )
{
	if(min == 0 && max == 0)
	{
		g_ProgressBar->setEnabled(false);
		g_ProgressBar->setRange(0,0);
	    g_ProgressBar->setValue(0);
		return;
	}
	else if(!g_ProgressBar->isEnabled())
	{
		g_ProgressBar->setEnabled(true);
	}
	g_ProgressBar->setRange(min,max);
	g_ProgressBar->setValue(val);
}

void CMainWindow::updateSolarPanel()
{
	SolarAnalysisParams* params = IGlobalInterfaces::getInstance()->getSolarAnalysisParams();
	if(g_pSolarPanelNodes->getNumChildren() > 0)
	{
		g_pSolarPanelNodes->removeChildren(0,g_pSolarPanelNodes->getNumChildren());
	}
	if(params->QueryMode == SpatialQueryMode::Point)
	{			

		if(params->SolarPanelIncluded)
		{			
			Building* building;	
			osg::ref_ptr<osg::Node> panelNode = g_pCity->getPanelNode(params->IntersectionPoint.x(),params->IntersectionPoint.y(),building);
			g_pDlgBuildingParams->setBuilding(building);
			//g_pSolarPanelNodes->removeChildren(0,g_pSolarPanelNodes->getNumChildren());
			g_pSolarPanelNodes->addChild(panelNode.get());
		}

	}
}


