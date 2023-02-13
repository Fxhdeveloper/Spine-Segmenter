#ifndef ITK_H
#define ITK_H

//#include "itkImageFileReader.h"
#include "itkImageSeriesReader.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"

using InputPixelType = double;
const unsigned int InputDimension3 = 3;
using InputImageType = itk::Image<InputPixelType, InputDimension3>;
using ImageSeriesReader = itk::ImageSeriesReader<InputImageType>;
using BinaryThresholdFilter= itk::BinaryThresholdImageFilter<InputImageType, InputImageType>;
using CurvatureFlowImageFilterType = itk::CurvatureFlowImageFilter< InputImageType, InputImageType>;

static itk::RegionOfInterestImageFilter <InputImageType, InputImageType>::Pointer    ROIFilter
= itk::RegionOfInterestImageFilter <InputImageType, InputImageType>::New();

class ITK
{
public:
    ITK();

    void readDicom(std::string folder);
    void smooth();
    void crop();
    ImageSeriesReader::Pointer getReader();
    void BinaryThreshold(BinaryThresholdFilter::Pointer filter,
                         double lowerThreshold, double upperThreshold);
    CurvatureFlowImageFilterType::Pointer getSmoothedData();


    int MinSlice{};
    int MaxSlice{};
    void calculateRegionToCrop(std::shared_ptr<double[]> x,std::shared_ptr<double[]> y);
private:
    ImageSeriesReader::Pointer reader = ImageSeriesReader::New();
    BinaryThresholdFilter::Pointer thresholdFilterIntervertebrae= BinaryThresholdFilter::New();
    CurvatureFlowImageFilterType::Pointer smoothing = CurvatureFlowImageFilterType::New();


    InputImageType::IndexType calculateCropStartPoint(std::shared_ptr<double[]> x, std::shared_ptr<double[]> y);
    InputImageType::IndexType calculateCropEndPoint(std::shared_ptr<double[]> x, std::shared_ptr<double[]> y);
    InputImageType::SizeType calculateCropSize(InputImageType::IndexType cropStart, InputImageType::IndexType cropEnd);
};

#endif // ITK_H
