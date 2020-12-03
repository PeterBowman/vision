// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __YARP_CLOUD_UTILS_PCL_TRAITS_HPP__
#define __YARP_CLOUD_UTILS_PCL_TRAITS_HPP__

#include <type_traits>
#include <yarp/sig/PointCloudTypes.h>
#include <pcl/point_types.h>

namespace
{

template <typename T>
struct pcl_type_from_yarp;

template <>
struct pcl_type_from_yarp<yarp::sig::DataXY>
{ typedef pcl::PointXY type; };

template <>
struct pcl_type_from_yarp<yarp::sig::DataXYZ>
{ typedef pcl::PointXYZ type; };

template <>
struct pcl_type_from_yarp<yarp::sig::DataNormal>
{ typedef pcl::Normal type; };

template <>
struct pcl_type_from_yarp<yarp::sig::DataXYZRGBA>
{ typedef pcl::PointXYZRGB type; };

template <>
struct pcl_type_from_yarp<yarp::sig::DataXYZI>
{ typedef pcl::PointXYZI type; };

template <>
struct pcl_type_from_yarp<yarp::sig::DataInterestPointXYZ>
{ typedef pcl::InterestPoint type; };

template <>
struct pcl_type_from_yarp<yarp::sig::DataXYZNormal>
{ typedef pcl::PointNormal type; };

template <>
struct pcl_type_from_yarp<yarp::sig::DataXYZNormalRGBA>
{ typedef pcl::PointXYZRGBNormal type; };

/////////////////////////////////////////////////

template <typename T>
struct pcl_surface_organized
{ typedef T type; };

template <>
struct pcl_surface_organized<pcl::PointXYZI>
{ typedef pcl::PointXYZ type; };

template <>
struct pcl_surface_organized<pcl::InterestPoint>
{ typedef pcl::PointXYZ type; };

template <>
struct pcl_surface_organized<pcl::PointNormal>
{ typedef pcl::PointXYZ type; };

template <>
struct pcl_surface_organized<pcl::PointXYZRGBNormal>
{ typedef pcl::PointXYZRGB type; };

/////////////////////////////////////////////////

template <typename T>
struct pcl_surface_normal
{ typedef T type; };

template <>
struct pcl_surface_normal<pcl::InterestPoint>
{ typedef pcl::PointXYZ type; };

/////////////////////////////////////////////////

template <typename T>
struct pcl_concatenate_normals
{ typedef T type; };

template <>
struct pcl_concatenate_normals<pcl::PointXYZ>
{ typedef pcl::PointNormal type; };

template <>
struct pcl_concatenate_normals<pcl::PointXYZI>
{ typedef pcl::PointXYZINormal type; };

template <>
struct pcl_concatenate_normals<pcl::PointXYZRGB>
{ typedef pcl::PointXYZRGBNormal type; };

/////////////////////////////////////////////////

template <typename T>
constexpr auto is_unsupported_type = std::is_same<T, pcl::PointXY>::value || std::is_same<T, pcl::Normal>::value;

template <typename T>
constexpr auto is_normal_type = std::is_same<T, pcl::PointNormal>::value || std::is_same<T, pcl::PointXYZRGBNormal>::value;

} // namespace

#endif // __YARP_CLOUD_UTILS_PCL_TRAITS_HPP__
