#ifndef ITK_H
#define ITK_H

//#include "itkImageFileReader.h"
#include "itkImageSeriesReader.h"

typedef double InputPixelType;
const unsigned int InputDimension3 = 3;
typedef itk::Image<InputPixelType, InputDimension3> InputImageType;

class ITK
{
public:
    ITK();

    void readDicom(std::string folder);
    itk::ImageSeriesReader<InputImageType>::Pointer getReader();

private:
    itk::ImageSeriesReader< InputImageType >::Pointer reader;
};

#endif // ITK_H
