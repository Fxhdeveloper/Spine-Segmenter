#ifndef ITK_H
#define ITK_H

//#include "itkImageFileReader.h"
#include "postprocessingfilters.h"
#include "itkImageSeriesReader.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"


////// double check headers
///

#include "itkBinaryImageToShapeLabelMapFilter.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkConstNeighborhoodIterator.h"
#include "itkFlipImageFilter.h"
#include "itkImage.h"
#include "itkImageDuplicator.h"
#include "itkImageFileWriter.h"
#include "itkImageSeriesWriter.h"
#include "itkImageSliceIteratorWithIndex.h"
#include "itkLabelMapToBinaryImageFilter.h"
#include "itkLabelToRGBImageFilter.h"
#include "itkMaskImageFilter.h"
#include "itkMaskNegatedImageFilter.h"
#include "itkMergeLabelMapFilter.h"
#include "itkMetaDataObject.h"
#include "itkNumericSeriesFileNames.h"
#include "itkNumericTraits.h"
#include "itkPasteImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkRGBPixel.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkStatisticsImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itksys/SystemTools.hxx"
#include <itkAddImageFilter.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkJPEGImageIO.h>
#include <itkMaskNegatedImageFilter.h>
#include <itkNrrdImageIO.h>
#include <itkOtsuMultipleThresholdsImageFilter.h>
///


using ImageSeriesReader = itk::ImageSeriesReader<InputImageType>;
using BinaryThresholdFilter= itk::BinaryThresholdImageFilter<InputImageType, InputImageType>;
using CurvatureFlowImageFilterType = itk::CurvatureFlowImageFilter< InputImageType, InputImageType>;


static itk::RegionOfInterestImageFilter <InputImageType, InputImageType>::Pointer    ROIFilter
= itk::RegionOfInterestImageFilter <InputImageType, InputImageType>::New();

class ITK
{
public:
    ITK();

    void readDicomData(std::string folder);
    void smooth();
    void crop();
    auto getReader();
    void BinaryThreshold(BinaryThresholdFilter::Pointer filter,
                         double lowerThreshold, double upperThreshold);
    CurvatureFlowImageFilterType::Pointer getSmoothedData();
    void calculateRegionToCrop(std::shared_ptr<double[]> x,std::shared_ptr<double[]> y);
    GSFillHolesFilterType::Pointer getVolume(BinaryThresholdFilter::Pointer inputData);

    int MinSlice{};
    int MaxSlice{};
private:
    auto calculateCropStartPoint(std::shared_ptr<double[]> x, std::shared_ptr<double[]> y);
    auto calculateCropEndPoint(std::shared_ptr<double[]> x, std::shared_ptr<double[]> y);
    auto calculateCropSize(InputImageType::IndexType cropStart, InputImageType::IndexType cropEnd);

    ImageSeriesReader::Pointer reader = ImageSeriesReader::New();
    CurvatureFlowImageFilterType::Pointer smoothing = CurvatureFlowImageFilterType::New();
    PostProcessingFilters postProcess;

};

#endif // ITK_H
