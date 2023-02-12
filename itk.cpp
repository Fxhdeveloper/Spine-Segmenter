#include "itk.h"
#include <itkGDCMImageIO.h>
#include "itkGDCMSeriesFileNames.h"

typedef itk::GDCMSeriesFileNames                NamesGeneratorType;
typedef itk::GDCMImageIO                        ImageIOType;

ITK::ITK()
{

}

void ITK::readDicom(std::string folder)
{
    NamesGeneratorType::Pointer namesGenerator = NamesGeneratorType::New();
    namesGenerator->SetInputDirectory(folder.c_str());
    const itk::ImageSeriesReader< InputImageType >
            ::FileNamesContainer & filenames = namesGenerator->GetInputFileNames();
    ImageIOType::Pointer gdcmIO= ImageIOType::New();
    reader->SetImageIO(gdcmIO);
    reader->SetFileNames(filenames);
    try
    {
        reader->Update();
        std::cout << "ITK reader succedded" << std::endl;
    }
    catch (itk::ExceptionObject &excp)
    {
        std::cerr << "Exception thrown while writing the image" << std::endl;
        std::cerr << excp << std::endl;
        // return EXIT_FAILURE;
    }
}

ImageSeriesReader::Pointer ITK::getReader()
{
    return reader;
}


void ITK::BinaryThreshold(BinaryThresholdFilter::Pointer filter, double lowerThreshold, double upperThreshold) {

    filter->SetInput(smoothing->GetOutput());
    filter->SetLowerThreshold(lowerThreshold);
    filter->SetUpperThreshold(upperThreshold);
    filter->Update();
}

CurvatureFlowImageFilterType::Pointer ITK::getSmoothedData()
{
    return smoothing;
}

void ITK::calculateRegionToCrop(double *x, double *y) {

    // magic, due to image viewer being shifted
    InputImageType::IndexType cropStart;
    cropStart[0] = x[0]-120;
    cropStart[1] = 590 - y[1]- 35;//-88
    cropStart[2] = MinSlice; //x[2];

    InputImageType::IndexType cropEnd;
    cropEnd[0] = y[0]-88;//
    cropEnd[1] = 590 - x[1]-15 ;//-44
    cropEnd[2] = MaxSlice;  // x[2];

    InputImageType::SizeType cropSize;
    cropSize[0] = cropEnd[0] - cropStart[0] ;
    cropSize[1] = cropEnd[1] - cropStart[1] ;
    cropSize[2] = cropEnd[2] - cropStart[2];

    InputImageType::RegionType regionToCrop;
    regionToCrop.SetSize(cropSize);
    regionToCrop.SetIndex(cropStart);
    ROIFilter->SetRegionOfInterest(regionToCrop);
}


void ITK::crop(){
    ROIFilter->SetInput(reader->GetOutput());
    ROIFilter->Update();
}

void ITK::smooth()
{
    smoothing->SetInput(ROIFilter->GetOutput());
    smoothing->SetNumberOfIterations(10);
    smoothing->SetTimeStep(0.05);
    smoothing->Update();
}
