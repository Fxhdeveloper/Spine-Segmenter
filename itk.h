#ifndef ITK_H
#define ITK_H

#include "postprocessingfilters.h"

#include <itkCurvatureFlowImageFilter.h>
#include <itkImageSeriesReader.h>
#include <itkRegionOfInterestImageFilter.h>

using ImageSeriesReader = itk::ImageSeriesReader<InputImageType>;
using BinaryThresholdFilter =
    itk::BinaryThresholdImageFilter<InputImageType, InputImageType>;
using CurvatureFlowImageFilterType =
    itk::CurvatureFlowImageFilter<InputImageType, InputImageType>;

static itk::RegionOfInterestImageFilter<InputImageType, InputImageType>::Pointer
    ROIFilter =
        itk::RegionOfInterestImageFilter<InputImageType, InputImageType>::New();

class ITK {
public:
  ITK();

  void readDicomData(std::string folder);
  void smooth();
  void crop();
  auto getReader();
  void BinaryThreshold(BinaryThresholdFilter::Pointer filter,
                       double lowerThreshold, double upperThreshold);
  CurvatureFlowImageFilterType::Pointer getSmoothedData();
  void calculateRegionToCrop(std::shared_ptr<double[]> x,
                             std::shared_ptr<double[]> y);
  GSFillHolesFilterType::Pointer
  getVolume(BinaryThresholdFilter::Pointer inputData);

  int MinSlice{};
  int MaxSlice{};

private:
  auto calculateCropStartPoint(std::shared_ptr<double[]> x,
                               std::shared_ptr<double[]> y);
  auto calculateCropEndPoint(std::shared_ptr<double[]> x,
                             std::shared_ptr<double[]> y);
  auto calculateCropSize(InputImageType::IndexType cropStart,
                         InputImageType::IndexType cropEnd);

  ImageSeriesReader::Pointer reader = ImageSeriesReader::New();
  CurvatureFlowImageFilterType::Pointer smoothing =
      CurvatureFlowImageFilterType::New();
  PostProcessingFilters postProcess;
};

#endif // ITK_H
