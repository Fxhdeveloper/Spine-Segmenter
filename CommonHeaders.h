#ifndef COMMONHEADERS_H
#define COMMONHEADERS_H
#include <itkImage.h>

typedef double InputPixelType;
typedef double OutputPixelType;
const unsigned int InputDimension = 3;
using OutputImageType = itk::Image<OutputPixelType, InputDimension>;
using InputImageType = itk::Image<InputPixelType, InputDimension>;

#endif // COMMONHEADERS_H
