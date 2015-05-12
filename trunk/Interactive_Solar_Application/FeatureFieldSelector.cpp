#include "FeatureFieldSelector.h"
#include "osgEarthDrivers/feature_ogr/OGRFeatureOptions"
#include "osgEarthFeatures/FeatureSource"
using namespace osgEarth;
using namespace osgEarth::Features;
using namespace osgEarth::Drivers;
FeatureFieldSelector::FeatureFieldSelector(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);	
}

FeatureFieldSelector::~FeatureFieldSelector()
{

}
std::string attributeTypeToString( AttributeType type )
{
	switch (type)
	{
	case ATTRTYPE_BOOL: return "Boolean";
	case ATTRTYPE_DOUBLE: return "Double";
	case ATTRTYPE_INT: return "Integer";
	case ATTRTYPE_STRING: return "String";
	default:  return "Unspecified";
	}
}

std::string FeatureFieldSelector::getFieldName()
{

	if(ui.comboBox_Field->count() < 1)
		return "";
	int sel =  ui.comboBox_Field->currentIndex();
	if(sel < 0)
		sel = 0;
	QString text = ui.comboBox_Field->itemText(sel);
	std::string field = text.toLocal8Bit();
	int endIndex = field.find_first_of("(");
	field = field.substr(0,endIndex);
	return field;
	//return "[" + field + "]";
}

void FeatureFieldSelector::setFeatureSource( osgEarth::Features::FeatureSource* featureSource )
{
	if(!featureSource)
		return;
    ui.comboBox_Field->clear();
	const FeatureSchema schema = featureSource->getSchema();
	std::cout << "Schema:" << std::endl;
	for (FeatureSchema::const_iterator itr = schema.begin(); itr != schema.end(); ++itr)
	{
		//std::string line = itr->first + "(" + attributeTypeToString(itr->second) + ")";
		// ui.comboBox_Field->addItem(line.data());

		 if(itr->second == ATTRTYPE_DOUBLE || itr->second == ATTRTYPE_INT)
		 {
			 std::string line = itr->first + "(" + attributeTypeToString(itr->second) + ")";
			 ui.comboBox_Field->addItem(line.data());
		 }
	}
}

void FeatureFieldSelector::setFeatureFile( QString filename )
{
	OGRFeatureOptions feature_opt;
	feature_opt.url() = filename.toLocal8Bit().data();
	osg::ref_ptr< FeatureSource > features = FeatureSourceFactory::create( feature_opt );
	features->initialize();
	features->getFeatureProfile();
	const FeatureSchema schema = features->getSchema();
	std::cout << "Schema:" << std::endl;
	setFeatureSource(features);
	//for (FeatureSchema::const_iterator itr = schema.begin(); itr != schema.end(); ++itr)
	//{
	//	if(itr->second == ATTRTYPE_DOUBLE || itr->second == ATTRTYPE_INT)
	//	{
	//		std::string line = itr->first + "(" + attributeTypeToString(itr->second) + ")";
	//		ui.comboBox_Field->addItem(line.data());
	//	}
	//
	//}
}
