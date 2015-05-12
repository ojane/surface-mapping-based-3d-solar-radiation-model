/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
 * Copyright 2008-2013 Pelican Mapping
 * http://osgearth.org
 *
 * osgEarth is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef OSGEARTHFEATURES_EXTRUDE_GEOMETRY_FILTER2_H
#define OSGEARTHFEATURES_EXTRUDE_GEOMETRY_FILTER2_H 1

#include <osgEarthFeatures/Common>
#include <osgEarthFeatures/Feature>
#include <osgEarthFeatures/Filter>
#include <osgEarthSymbology/Expression>
#include <osgEarthSymbology/Style>
#include <osg/Geode>

namespace osgEarth { namespace Features 
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;
    
    class FeatureSourceIndex;


    /**
     * Extrudes footprint geometry into 3D geometry
     */
    class ExtrudeGeometryFilter2 : public FeaturesToNodeFilter
    {
    public:
        struct HeightCallback : public osg::Referenced
        {
            virtual float operator()( Feature* input, const FilterContext& cx ) =0;
        };

    public:

        /** Constructs a new filter that will extrude footprints */
        ExtrudeGeometryFilter2();

        virtual ~ExtrudeGeometryFilter2() { }

        /**
         * Sets the style that will govern the geometry generation.
         */
        void setStyle( const Style& style );

        /**
         * Pushes a list of features through the filter.
         */
        osg::Node* push( FeatureList& input, FilterContext& context );

    public: // properties

        /**
         * Sets the maximum wall angle that doesn't require a new normal vector
         */
        void setWallAngleThreshold( float angle_deg ) { _wallAngleThresh_deg = angle_deg; }

        /**
         * Sets whether to render a bottom top. Useful for creating stencil volumes.
         */
        void setMakeStencilVolume( bool value ) { _makeStencilVolume = value; }
        
        /**
         * Sets the expression to evaluate when setting a feature name.
         * NOTE: setting this forces geometry-merging to OFF
         */
        void setFeatureNameExpr( const StringExpression& expr ) { _featureNameExpr = expr; }
        const StringExpression& getFeatureNameExpr() const { return _featureNameExpr; }

        /**
         * Whether or not to use vertex buffer objects
         */
        optional<bool>& useVertexBufferObjects() { return _useVertexBufferObjects;}
        const optional<bool>& useVertexBufferObjects() const { return _useVertexBufferObjects;}

        /**
         * Whether or not to use TextureArrays for the wall and roof skins
         */
        optional<bool>& useTextureArrays() { return _useTextureArrays;}
        const optional<bool>& useTextureArrays() const { return _useTextureArrays;}


    protected:

        // a set of geodes indexed by stateset pointer, for pre-sorting geodes based on 
        // their texture usage
        typedef std::map<osg::StateSet*, osg::ref_ptr<osg::Geode> > SortedGeodeMap;
        SortedGeodeMap                 _geodes;
        osg::ref_ptr<osg::StateSet>    _noTextureStateSet;

        optional<double>               _maxAngle_deg;
        optional<bool>                 _mergeGeometry;
        float                          _wallAngleThresh_deg;
        float                          _cosWallAngleThresh;
        StringExpression               _featureNameExpr;
        osg::ref_ptr<HeightCallback>   _heightCallback;
        optional<NumericExpression>    _heightOffsetExpr;
        optional<NumericExpression>    _heightExpr;
        bool                           _makeStencilVolume;
        optional<bool>                 _useVertexBufferObjects;

        Style                          _style;
        bool                           _styleDirty;
        optional<bool>                 _useTextureArrays;

        osg::ref_ptr<const ExtrusionSymbol> _extrusionSymbol;
        osg::ref_ptr<const SkinSymbol>      _wallSkinSymbol;
        osg::ref_ptr<const PolygonSymbol>   _wallPolygonSymbol;
        osg::ref_ptr<const SkinSymbol>      _roofSkinSymbol;
        osg::ref_ptr<const PolygonSymbol>   _roofPolygonSymbol;
        osg::ref_ptr<const LineSymbol>      _outlineSymbol;
        osg::ref_ptr<ResourceLibrary>       _wallResLib;
        osg::ref_ptr<ResourceLibrary>       _roofResLib;

        void reset( const FilterContext& context );
        
        void addDrawable( 
            osg::Drawable*      drawable, 
            osg::StateSet*      stateSet, 
            const std::string&  name,
            Feature*            feature,
            FeatureSourceIndex* index);
        
        bool process( 
            FeatureList&     input,
            FilterContext&   context );

        bool extrudeGeometry(
            const Geometry*      input,
            double               height,
            double               offset,
            bool                 uniformHeight,
            osg::Geometry*       walls,
            osg::Geometry*       top_cap,
            osg::Geometry*       bottom_cap,
            osg::Geometry*       outline,
            const osg::Vec4&     wallColor,
            const osg::Vec4&     wallBaseColor,
            const osg::Vec4&     roofColor,
            const osg::Vec4&     outlineColor,
            const SkinResource*  wallSkin,
            int wallLayer,
            const SkinResource*  roofSkin,
            int roofLayer,
            FilterContext&       cx );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_BUILD_GEOMETRY_FILTER_H
